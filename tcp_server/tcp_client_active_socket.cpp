#include <boost/asio.hpp>
#include <iostream>
using namespace boost;
int main() {
  // Step 1. An instance of 'io_service' class is required by
  // socket constructor.
  asio::io_service ios;
  
  // Step 2. Creating an object of 'tcp' class representing
  // a TCP protocol with IPv4 as underlying protocol.
  
  // asio::ip::tcp class represents a TCP protocol. 
  // Provides no functionality, rather acts like a data structure that contains a
  // set of values that describe the protocol.

  // The asio::ip::tcp class doesn't have a public constructor. Instead, it provides two static
  // methods, asio::ip::tcp::v4() and asio::ip::tcp::v6(), that return an object of
  // the asio::ip::tcp class representing the TCP protocol with the underlying IPv4 or IPv6
  // protocol correspondingly.
  asio::ip::tcp protocol = asio::ip::tcp::v4();

  // Step 3. Instantiating an active TCP socket object.
  asio::ip::tcp::socket sock(ios);

  // Used to store information about error that happens
  // while opening the socket.
  boost::system::error_code ec;

  // Step 4. Opening the socket.
  sock.open(protocol, ec); // protocol required when opening socket, whereas io_service required for the socket constructor
  
 //Steps 3 & 4 can be combined as follows:
  /* try {
   // Step 3 + 4 in single call. May throw.
   asio::ip::tcp::socket sock(ios, protocol);
  } 
  catch (boost::system::system_error & e) {
    std::cout << "Error occured! Error code = " << e.code() << ". Message: "<< e.what();
  }
  */

  if (ec.value() != 0) {
    // Failed to open the socket.
    std::cout << "Failed to open the socket! Error code = " << ec.value() << ". Message: " << ec.message();
   return ec.value();
  }
  return 0;
}
