#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <stdio.h>
#include <string.h>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

class client {
  private:
    tcp::socket sk;
    tcp::resolver _r;
    std::string _ip_addr;
    short _port;
    char receive_data[max_length];
    char request[max_length];
    // boost::asio::streambuf receive_data;
    size_t request_length;

    void split_char_arr(char* arr, char c) {
      if (!arr) return;
      while (*arr != '\0' && *arr != c) arr++;
      *arr = '\0'; // set end character at new location
    }

  public:
    client(boost::asio::io_service& ios, std::string& ip_addr, short port) : sk{ ios }, _r{ ios }, _ip_addr{ ip_addr }, _port{ port } {}

    bool connect() {
      try {
        boost::asio::connect(sk, _r.resolve({ _ip_addr, boost::lexical_cast<std::string>(_port) }));
        return true;
      }
      catch (std::exception& e) {
        return false;
      }
    }

    void set_sql_statement(std::string& sql) {
      strcpy(request, sql.c_str());
      request_length = std::strlen(request);
      std::cout << "SQL Statement after setting length " << request << " " << request_length << "\n";
    }

    void execute_sql() {
      // boost::asio::write(sk, boost::asio::buffer("delete from test1", std::strlen("delete from test1")));
      std::cout <<"SQL statement before write " << request << "\n";
      boost::asio::write(sk, boost::asio::buffer(request, request_length));
    }

    std::string receive_result() {
      std::string str;
      std::size_t buffer_size = boost::asio::read(sk, boost::asio::buffer(receive_data, max_length));
      split_char_arr(receive_data, '\n');
      str = receive_data;

      return str;
    }
};

int main() {
  try {
    boost::asio::io_service ios;
    std::string ip_addr{ "127.0.0.1" };
    short port{ 3333 };
    std::string sql;

    client cl(ios, ip_addr, port);

    if (!cl.connect()) return -1;

    std::cout << "Connected successfully \n";
    sql = "insert into test1 (x,y) values (3,'Green')";
    cl.set_sql_statement(sql);
    cl.execute_sql();
    std::cout << "Number of rows affected: " << cl.receive_result() << "\n";

    sql = "insert into test1 (x,y) values (1,'Blue')\n";
    cl.set_sql_statement(sql);
    cl.execute_sql();
    std::cout << "Number of rows affected: " << cl.receive_result() << "\n";

    sql = "insert into test1 (x,y) values (2,'Blue')\n";
    cl.set_sql_statement(sql);
    cl.execute_sql();
    std::cout << "Number of rows affected: " << cl.receive_result() << "\n";

    sql = "insert into test1 (x,y) values (4,'Black')\n";
    cl.set_sql_statement(sql);
    cl.execute_sql();
    std::cout << "Number of rows affected: " << cl.receive_result() << "\n";


    std::cout << "Number of rows affected: " << cl.receive_result() << "\n";
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
