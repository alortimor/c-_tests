#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "logger.h"

#include <iostream>
#include </home/bluefrog/SQLAPI/include/SQLAPI.h>

SAConnection con; // connection object
using boost::asio::ip::tcp;

int rows_affected(std::string & sql) {
  int rows{-1};

  try {
    con.Connect("localhost,5432@ft_node", "bluefrog", "bluefrog", SA_PostgreSQL_Client);
    con.setAutoCommit(SA_AutoCommitOff);
    con.setIsolationLevel(SA_RepeatableRead);
    SACommand cmd1(&con);
    cmd1.setCommandText(sql.c_str());
    cmd1.Execute();
    rows = cmd1.RowsAffected();
    con.Commit();
  }
  catch(SAException &x) {
    excep_log( (const char*)x.ErrText() );
  }
  return rows;
}

class session  {
public:
  session(tcp::socket socket) : sk(std::move(socket)) { }
  void start() { do_read(); }

private:
  void do_read() {
    excep_log( "Start reading");
    boost::asio::async_read_until(sk, receive_data, '\n',
        [this](const boost::system::error_code& ec, std::size_t bytes_transferred) {
              if (!ec) {
                excep_log( "Before buffer copy " + std::to_string(bytes_transferred));
                boost::asio::streambuf::const_buffers_type bufs = receive_data.data();
                std::string str(boost::asio::buffers_begin(bufs), boost::asio::buffers_begin(bufs) + bytes_transferred);
                receive_data.consume(bytes_transferred);
                excep_log( "SQL Statement  - : " + str);
                do_write(bytes_transferred, rows_affected(str) );
              }
            });
  }

  void do_write(std::size_t length, int rows) {
    std::string str {std::to_string(rows) + "\n"};
    strcpy(send_data, str.c_str());
    excep_log( "Before write");
    boost::asio::async_write(sk, boost::asio::buffer(send_data)
                        , [this] (const boost::system::error_code& ec, std::size_t bytes_transferred) {
                            if (!ec) {
                              excep_log( "After write");
                              do_read();
                            };
                        });
  }

  tcp::socket sk;
  enum { max_length = 1024 };
  char send_data[max_length];
  boost::asio::streambuf receive_data;
  //char receive_data[max_length];
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
      std::cerr << "Usage: async_db_server <port>\n";
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
