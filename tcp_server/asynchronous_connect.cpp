#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>

std::mutex mx;

void work_thread(boost::shared_ptr<boost::asio::io_service> ios, int cnt) {

  // Ensure iostream is locked each time a cout is performed
  mx.lock();
  std::cout << "Thread " << cnt << " Start.\n";
  mx.unlock();

  while(true) {
    try {
      boost::system::error_code ec;
      ios->run(ec);
      if (ec) {
        mx.lock();
        std::cout << "Error EC: " << ec << ".\n";
        mx.unlock();
      }
      break;
    }
    catch(std::exception &ex) {
      mx.lock();
      std::cout << "Error catch: " << ex.what() << ".\n";
      mx.unlock();
    }
  }

  mx.lock();
  std::cout << "Thread " << cnt << " End.\n";
  mx.unlock();
}

void upon_connect(const boost::system::error_code &ec) {
  if(ec) {
    mx.lock();
    std::cout << "Connect Error: " << ec << ".\n";
    mx.unlock();
  }
  else {
    mx.lock();
    std::cout << "Connected!.\n";
    mx.unlock();
  }
}

int main() {
  // io_service provides a service for operating on asynchronous functions. Once a async operation is ready, it uses one of io_service's running threads to call you back. If no such thread exists it uses its own internal thread to call you.
  boost::shared_ptr<boost::asio::io_service> ios (new boost::asio::io_service);
  boost::shared_ptr<boost::asio::io_service::work> worker (new boost::asio::io_service::work(*ios));

  boost::asio::io_service::strand strand(*ios);

  mx.lock();
  std::cout << "Enter to exit.\n";
  mx.unlock();

  boost::thread_group threads;
  for(int i=1; i<=6; i++)
    threads.create_thread(boost::bind(&work_thread, ios, i));

  // socket object is noncopyable, so always wrap it in a smart pointer. Boost offers the smart_ptr.
  boost::shared_ptr<boost::asio::ip::tcp::socket> sk(new boost::asio::ip::tcp::socket(*ios));

  try {


    // resolvers map hostnames and services to IP addresses
    boost::asio::ip::tcp::resolver resolver(*ios);

    // Query is an object that defines a network interaction, based on an address and a port, that is to be resolved
    // the port number (80) is required to be in a string format. A query, once setup, is passed onto a resolver.
    boost::asio::ip::tcp::resolver::query query("www.google.com", boost::lexical_cast<std::string>(80) );
  
    // An iterator is required since many addresses are returned from Google, therefore an iterator
    // is required to ietrate through the list of addresses.
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    // Endpoint holds list of ip addresses returned by resolver
    boost::asio::ip::tcp::endpoint endpoint = *iterator;
    mx.lock();
    std::cout << "Connecting to: " << endpoint << std::endl;
    mx.unlock();
    sk->async_connect(endpoint, boost::bind(upon_connect, _1)); // ASYNCHRONOUS CONNECT
    // sk.connect(endpoint); // SYNCHRONOUS CONNECT
  }
  catch(std::exception &ex) {
    mx.lock();
    std::cout << "Message: " << ex.what() << ".\n";
    mx.unlock();
  }

  std::cin.get();
  boost::system::error_code ec;

  // shutdown_both disables both the sending and receiving on the socket
  sk->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
  sk->close(ec);
  ios->stop();
  threads.join_all();

  return 0;
}

