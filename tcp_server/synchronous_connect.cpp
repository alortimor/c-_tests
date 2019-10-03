#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <thread>
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

  boost::asio::ip::tcp::socket sk(*ios);


  try {
    boost::asio::ip::tcp::resolver resolver(*ios);

    // Query is an object that defines a network interaction, based on an address and a port, that is to be resolved
    // the port number (80) is required to be in a string format.
    boost::asio::ip::tcp::resolver::query query("www.google.com", boost::lexical_cast<std::string>(80) );
  
    // An iterator is required since many url's are returned from Google, but only one is required
    // for resolution by the resolver.
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

    // Endpoint holds list of ip addresses returned by resolver
    boost::asio::ip::tcp::endpoint endpoint = *iterator;
    mx.lock();
    std::cout << "Connecting to: " << endpoint << std::endl;
    mx.unlock();
    sk.connect(endpoint);
    std::cout << "Connected!\n";
  }
  catch(std::exception &ex) {
    mx.lock();
    std::cout << "Message: " << ex.what() << ".\n";
    mx.unlock();
  }

  std::cin.get();
  boost::system::error_code ec;
  sk.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
  sk.close(ec);
  ios->stop();
  threads.join_all();

  return 0;
}

