#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
  session(tcp::socket socket) : sk(std::move(socket)) { }

  void start() {
    do_read();
  }

private:
  void do_read() {
    auto self(shared_from_this());
    sk.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
          if (!ec)
            do_write(length);
        });
  }

  void do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(sk, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t /*length*/)   {
          if (!ec)
            do_read();
        });
  }

  tcp::socket sk;
  enum { max_length = 1024 };
  char data_[max_length];
};

class server {
public:
  server(boost::asio::io_service& ios, short port) : acc(ios, tcp::endpoint(tcp::v4(), port)), sk(ios) {
    do_accept();
  }

private:
  void do_accept() {
    acc.async_accept(sk,
        [this](boost::system::error_code ec) {
          if (!ec)
            std::make_shared<session>(std::move(sk))->start();

          do_accept();
        });
  }

  tcp::acceptor acc;
  tcp::socket sk;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;
    server s(io_service, std::atoi(argv[1]));

    io_service.run();
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
