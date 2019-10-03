#ifndef SYNCTCPCLIENT_H
#define SYNCTCPCLIENT_H

#include <boost/asio.hpp>
#include <string>

using namespace boost;

class sync_tcp_client {
  private:
    asio::io_service m_ios;
    asio::ip::tcp::endpoint m_ep;
    asio::ip::tcp::socket m_sock;

    void send_request(const std::string& request) {
      asio::write(m_sock, asio::buffer(request));
    }

    std::string receive_response() {
      asio::streambuf buf;
      asio::read_until(m_sock, buf, '\n');
      std::istream input(&buf);
      std::string response;
      std::getline(input, response);
      return response;
    }

public:
    sync_tcp_client(const std::string& ip_addr, int port) : m_ep(asio::ip::address::from_string(ip_addr), port), m_sock(m_ios) {
      m_sock.open(m_ep.protocol());
    }

    void connect() { m_sock.connect(m_ep); }

    void close() {
      m_sock.shutdown(
      boost::asio::ip::tcp::socket::shutdown_both);
      m_sock.close();
    }

    std::string send_to_server(std::string str) {
      send_request(str + "\n");
      return receive_response();
    };

    std::string emulateLongComputationOp(int duration_sec) {
      std::string request = "EMULATE_LONG_COMP_OP " + std::to_string(duration_sec) + "\n";
      send_request(request);
      return receive_response();
    };

};

#endif // SYNCTCPCLIENT_H
