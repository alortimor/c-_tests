#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost;

void write_to_socket(asio::ip::tcp::socket& sk, const std::string & msg ) {
  
  asio::write(sk, asio::buffer(msg));  
}

void read_from_socket(asio::ip::tcp::socket& sk ) {
    /* to be coded */
}

int main() {
  std::string ip_addr {"127.0.0.1"};
  unsigned short port {5555};

  try {
    // initialise end point
    asio::ip::tcp::endpoint ep {asio::ip::address::from_string(ip_addr), port};
    
    std::cout << "End point declared \n";

    asio::io_service ios;

    // Configure socket with ios object and associated end point
    asio::ip::tcp::socket sk{ios, ep.protocol()};

    std::cout << "Socket Declared \n";
    sk.connect(ep); // connect socket to end point
    std::cout << "Socket Connected \n";

    write_to_socket(sk, "Hello World\n");
  }
  catch (system::system_error &e) {
    std::cout << "Error: " << e.code() << " " << e.what();
    return e.code().value();
  }

  return 0;
}
