#include "tcp_acceptor.h"
#include "logger.h"

extern logger exception_log;

tcp_acceptor::tcp_acceptor(asio::io_service& ios, unsigned short port) :
                   m_ios(ios)
                  ,acc(m_ios
                      ,asio::ip::tcp::endpoint(asio::ip::address_v4::any()
                                              ,port)
                       )
                  ,inactive(false)  { }

void tcp_acceptor::start() {
  acc.listen();
  init_accept();
}

void tcp_acceptor::stop() {
  inactive.store(true);
}

void tcp_acceptor::init_accept() {
    std::shared_ptr<asio::ip::tcp::socket> sock(new asio::ip::tcp::socket(m_ios));
    acc.async_accept(*sock.get(),
                    [this, sock](const boost::system::error_code& ec)
                                   { on_accept(ec, sock); }
                     );
}

void tcp_acceptor::on_accept(const boost::system::error_code& ec
                            ,std::shared_ptr<asio::ip::tcp::socket> sock) {
  if (ec == 0)
    (new tcp_service(sock))->start_handling();
  else
      excep_log("Error code = " + std::to_string(ec.value()) + ": "
                                + ec.message());
  if (!inactive.load())
    init_accept();
  else
    acc.close();
}
