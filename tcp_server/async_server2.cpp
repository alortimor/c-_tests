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


void on_accept(const boost::system::error_code &ec) {
  if(ec) {
    mx.lock();
    std::cout << "Accept Error: " << ec << ".\n";
    mx.unlock();
  }
  else {
    mx.lock();
    std::cout << "Accepted.\n";
    mx.unlock();
  }
}

// https://stackoverflow.com/questions/22191725/how-to-support-mutiple-connections-in-the-tcp-server-via-boost-asio
int main() {
  boost::shared_ptr<boost::asio::io_service> ios (new boost::asio::io_service);
  boost::shared_ptr<boost::asio::io_service::work> worker (new boost::asio::io_service::work(*ios));

  boost::asio::io_service::strand strand(*ios);

  mx.lock();
  std::cout << "Enter to exit.\n";
  mx.unlock();

  boost::thread_group threads;
  for(int i=1; i<=6; i++)
    threads.create_thread(boost::bind(&work_thread, ios, i));

  // Only a single acceptor is allowed for a specific port number, but multiple io_service objects
  // can be bound to the single acceptor. acceptor object is used for accepting new socket connections.
  boost::shared_ptr< boost::asio::ip::tcp::acceptor > acceptor(new boost::asio::ip::tcp::acceptor(*ios));

  // socket object is noncopyable, so always wrap it in a smart pointer. Boost offers the smart_ptr.
  boost::shared_ptr<boost::asio::ip::tcp::socket> sk(new boost::asio::ip::tcp::socket(*ios));

  try {
    boost::asio::ip::tcp::resolver resolver(*ios);
    boost::asio::ip::tcp::resolver::query query("127.0.0.1", boost::lexical_cast<std::string>(3333));
    // An iterator is required since many addresses are returned from Google, therefore an iterator
    // is required to ietrate through the list of addresses.
    // 1.  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    // Endpoint holds list of ip addresses returned by resolver
    // 2.  boost::asio::ip::tcp::endpoint endpoint = *iterator;

    

    /* The following represents some pesudocode that highlights the relationship between an iterator and an endpoint:
      ip::tcp::resolver::iterator iter = resolver.resolve(query);
      ip::tcp::resolver::iterator endpoint; // End marker.
      while (iter != endpoint) {
        ip::tcp::endpoint endpoint = *iter++;
      }
    */

    // The above 2 steps can be done in a single step.
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    acceptor->open(endpoint.protocol()); // open for accepting, based on the protocol retrieved from the endpoint variable
    
    acceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(false)); // do not reuse address
    acceptor->bind(endpoint);
    acceptor->listen(boost::asio::socket_base::max_connections);
    acceptor->async_accept(*sk, boost::bind(on_accept, _1));

    mx.lock();
    std::cout << "Acceptor setup for listening on : " << endpoint << std::endl;
    mx.unlock();
  }
  catch(std::exception &ex) {
    mx.lock();
    std::cout << "Message: " << ex.what() << ".\n";
    mx.unlock();
  }

  std::cin.get();
  boost::system::error_code ec;
  acceptor->close(ec);
  sk->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

  ios->stop();
  threads.join_all();

  return 0;
}









