#include <boost/asio.hpp>
#include <iostream>

using namespace boost;
int main() {
  // Step 1. Here we assume that the server application has
  // already obtained the protocol port number.
  unsigned short port_num = 3333;
  // Step 2. Create special object of asio::ip::address class
  // that specifies all IP-addresses available on the host. Note
  // that here we assume that server works over IPv4 protocol.
  asio::ip::address ip_address = asio::ip::address_v4::any(); 
  
  // Step 3. Instantiate an object of the asio::ip::tcp::endpoint class from the address
  // object created in step 2 and a port number.
  asio::ip::tcp::endpoint ep(ip_address, port_num);

  //   Step 4. The endpoint is created and can be used to
  // specify the IP addresses and a port number on which
  // the server application wants to listen for incoming
  // connections.
  
  return 0;
}

