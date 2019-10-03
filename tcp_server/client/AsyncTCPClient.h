#ifndef ASYNCTCPCLIENT_H
#define ASYNCTCPCLIENT_H

#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>

using namespace boost;

// Function pointer type that points to the callback
// function which is called when a request is complete.
typedef void(*Callback) (int request_id, const std::string& response, const system::error_code& ec);

// Structure represents a context of a single request.
struct Session {
    Session(asio::io_service& ios,
        const std::string& ip_addr, short port,
        const std::string& request,
        int id,
        Callback callback) :
            m_sock(ios),
            m_ep(asio::ip::address::from_string(ip_addr), port),
            m_request(request),
            m_id(id),
            m_callback(callback),
            m_was_cancelled(false)
    {
    }
    asio::ip::tcp::socket m_sock; // Socket used for communication
    asio::ip::tcp::endpoint m_ep; // Remote endpoint.
    std::string m_request;
    // Request string.
    // streambuf where the response will be stored.
    asio::streambuf m_response_buf;
    std::string m_response; // Response represented as a string.
    // Contains the description of an error if one occurs during
    // the request life cycle.
    system::error_code m_ec;
    unsigned int m_id; // Unique ID assigned to the request.
    // Pointer to the function to be called when the request
    // completes.
    Callback m_callback;
    bool m_was_cancelled;
    std::mutex m_cancel_guard;
};

class AsyncTCPClient : public boost::noncopyable {
  public:
    AsyncTCPClient() {
      m_work.reset(new boost::asio::io_service::work(m_ios));
      m_thread.reset(new std::thread([this](){ m_ios.run(); }));
    }

    void process_request(int duration_sec, const std::string& ip_addr, short port, Callback callback, int request_id, const std::string& sql_statement) {
    	std::string request = sql_statement + std::string("\n");
      std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(m_ios, ip_addr, port, request, request_id, callback));
      session->m_sock.open(session->m_ep.protocol());

        // Add new session to the list of active sessions so
        // that we can access it if the user decides to cancel
        // the corresponding request before it completes.
        // Because active sessions list can be accessed from
        // multiple threads, we guard it with a mutex to avoid
        // data corruption.
        std::unique_lock<std::mutex> lock(m_active_sessions_guard);
        m_active_sessions[request_id] = session;
        lock.unlock();
        session->m_sock.async_connect(session->m_ep,
            [this, session](const system::error_code& ec) {
                if (ec != 0) {
                    session->m_ec = ec;
                    request_done(session);
                    return;
                }
                std::unique_lock<std::mutex> cancel_lock(session->m_cancel_guard);
                if (session->m_was_cancelled) {
                    request_done(session);
                    return;
                }
                asio::async_write(session->m_sock,
                    asio::buffer(session->m_request),
                    [this, session](const boost::system::error_code& ec,
                    std::size_t bytes_transferred) {
                        if (ec != 0) {
                            session->m_ec = ec;
                            request_done(session);
                            return;
                        }
                        std::unique_lock<std::mutex> cancel_lock(session->m_cancel_guard);
                        if (session->m_was_cancelled) {
                            request_done(session);
                            return;
                        }
                        asio::async_read_until(session->m_sock,
                            session->m_response_buf, '\n',
                            [this, session](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                                if (ec != 0) {
                                    session->m_ec = ec;
                                }
                                else {
                                    std::istream strm(&session->m_response_buf);
                                    std::getline(strm, session->m_response);
                                }
                                request_done(session);
                            }
                                              );
                    }
                );
            }
        );
    };

    // Cancels the request.
    void cancel_request(int request_id) {
      std::unique_lock<std::mutex> lock(m_active_sessions_guard);
      auto it = m_active_sessions.find(request_id);
      if (it != m_active_sessions.end()) {
        std::unique_lock<std::mutex> cancel_lock(it->second->m_cancel_guard);
        it->second->m_was_cancelled = true;
        it->second->m_sock.cancel();
      }
    }

    void close() {
      // allows i/o thread to exits event loop when there are no more pending asynchronous operations.
      m_work.reset(NULL);
      // Wait for the I/O thread to exit.
      m_thread->join();
    }

private:
    void request_done(std::shared_ptr<Session> session)  {
      // Shutting down the connection. This method may
      // fail in case socket is not connected. We don’t care
      // about the error code if this function fails.
      boost::system::error_code ignored_ec;
      session->m_sock.shutdown(
          asio::ip::tcp::socket::shutdown_both,
          ignored_ec);
      // Remove session form the map of active sessions.
      std::unique_lock<std::mutex> lock(m_active_sessions_guard);
      auto it = m_active_sessions.find(session->m_id);
      if (it != m_active_sessions.end())
          m_active_sessions.erase(it);
      lock.unlock();
      boost::system::error_code ec;
      if (session->m_ec == 0 && session->m_was_cancelled)
        ec = asio::error::operation_aborted;
      else
        ec = session->m_ec;

      // Call the callback provided by the user.
      session->m_callback(session->m_id, session->m_response, ec);
    };

private:
    asio::io_service m_ios;
    std::map<int, std::shared_ptr<Session>> m_active_sessions;
    std::mutex m_active_sessions_guard;
    std::unique_ptr<boost::asio::io_service::work> m_work;
    std::unique_ptr<std::thread> m_thread;
};


#endif // ASYNCTCPCLIENT_H
