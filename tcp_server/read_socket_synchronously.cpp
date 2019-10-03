#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

void write_to_socket(asio::ip::tcp::socket& sk, const std::string & msg ) {
  std::size_t total_write {0};  // bytes successfully witten
  std::size_t sz {msg.size()};
  
  // write_some returns the number of bytes sucessfully written
  while (total_write != sz ) {
    total_write += sk.write_some(asio::buffer(msg.c_str() + total_write, sz - total_write));
  }
  
}

std::string read_from_socket(asio::ip::tcp::socket& sk) {
  const unsigned char msg_size {12};
  char buf[msg_size];
  std::size_t total_read {0};

  while (total_read != msg_size) {
    total_read += sk.read_some(asio::buffer(buf + total_read, msg_size - total_read));
  }

  // the above can also be codedwith a single function call:
  // asio::read(sock, asio::buffer(buf, MESSAGE_SIZE));

  return std::string(buf, total_read);
}

std::string read_until_delim(asio::ip::tcp::socket& sk) {
  asio::streambuf buf;
  // Synchronously read until '\n' symbol
  asio::read_until(sk, buf, '\n');

  std::string msg;

  std::istream input_stream(&buf);

  // Read characters only up until delimited "\n"
  std::getline(input_stream, msg);
  return msg;
}

int main() {

  std::string ip_addr {"127.0.0.1"};
  unsigned short port {3333};

  try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(ip_addr), port);
    asio::io_service ios;
    asio::ip::tcp::socket sk(ios, ep.protocol());    
    sk.connect(ep);

    write_to_socket(sk, "Hello World\n");
    std::cout << read_from_socket(sk) << std::endl;
  }
  catch (system::system_error &e) {
    std::cout << "Error: " << e.code() << " " << e.what();
    return e.code().value();
  }

  return 0;
}
