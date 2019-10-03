#ifndef TCP_SERVICE_H
#define TCP_SERVICE_H

#include <boost/asio.hpp>
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>

using namespace boost;

class tcp_service : public std::enable_shared_from_this<tcp_service>{

  private:
    std::shared_ptr<asio::ip::tcp::socket> m_sock;
    std::string m_response;
    asio::streambuf m_request;

    void on_request_received(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void on_response_sent(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void on_finish(); // cleanup

    std::string process_request(asio::streambuf& req);

  public:
    tcp_service(std::shared_ptr<asio::ip::tcp::socket> sock);
    void start_handling();
    void client_response(const std::string& msg);

};

#endif // TCP_SERVICE_H
