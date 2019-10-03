#ifndef SYNCTCPCLIENT_H
#define SYNCTCPCLIENT_H

#include <boost/asio.hpp>
#include <string>

using namespace boost;

class ftn_client {
  private:
    asio::io_service m_ios;
    asio::ip::tcp::endpoint m_ep;
    asio::ip::tcp::socket m_sock;

public:
    ftn_client(const std::string& ip_addr, int port) : m_ep(asio::ip::address::from_string(ip_addr), port), m_sock(m_ios) {
      m_sock.open(m_ep.protocol());
    }

    void connect() { m_sock.connect(m_ep); }
    void close();
    std::string send_to_server(std::string str);
    std::string receive_response();
};

#endif // SYNCTCPCLIENT_H
