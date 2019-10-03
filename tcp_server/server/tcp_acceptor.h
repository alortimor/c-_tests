#ifndef TCP_ACCEPTOR_H
#define TCP_ACCEPTOR_H
#include <boost/asio.hpp>
#include <atomic>
#include <memory>
#include "tcp_service.h"

using namespace boost;

class tcp_acceptor {
public:
  tcp_acceptor(asio::io_service& ios, unsigned short port);
  void start();
  void stop();

private:
  void init_accept();
  void on_accept(const boost::system::error_code& ec
                ,std::shared_ptr<asio::ip::tcp::socket> sock);
private:
  asio::io_service& m_ios;
  asio::ip::tcp::acceptor acc;
  std::atomic<bool> inactive;
};

#endif // TCP_ACCEPTOR_H
