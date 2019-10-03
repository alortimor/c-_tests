#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <mutex>
#include <thread>
#include <iostream>

std::mutex mx;

void work_thread(boost::shared_ptr<boost::asio::io_service> ios, int cnt) {

  // Ensure lock each time a cout is performed
  mx.lock();
  std::cout << "Thread " << cnt << " Start.\n";
  mx.unlock();

  while(true) {
    try {
      boost::system::error_code ec;
      ios->run(ec);
      if (ec) {
        mx.lock();
        std::cout << "Error Message: " << ec << ".\n";
        mx.unlock();
      }
      break;
    }
    catch(std::exception &ex) {
      mx.lock();
      std::cout << "Exception Message: " << ex.what() << ".\n";
      mx.unlock();
    }
  }

  mx.lock();
  std::cout << "Thread " << cnt << " End.\n";
  mx.unlock();
}

void throw_exception(boost::shared_ptr<boost::asio::io_service> ios) {
  mx.lock();
  std::cout << "Throw Error\n" ;
  mx.unlock();
  ios->post(boost::bind(&throw_exception, ios));
  throw(std::runtime_error("ERROR"));
}

void better_late_than_never(const boost::system::error_code & ec) {
  if(ec) {
    mx.lock();
    std::cout << "Error Message: " << ec << ".\n";
    mx.unlock();
  }
  else {
    mx.lock();
    std::cout << "Text appears after 10 seconds.\n";
    std::cout << "Enter to exit.\n";
    mx.unlock();
  }
}

void print_number(int number) {
  std::cout << "Number: " << number << std::endl;
}

int main(void) {
  
  boost::shared_ptr<boost::asio::io_service> ios (new boost::asio::io_service);
  boost::shared_ptr<boost::asio::io_service::work> worker (new boost::asio::io_service::work(*ios));

  mx.lock();
  std::cout << "Program will exit once all work has completed.\n";
  mx.unlock();

  boost::thread_group threads;
  for(int i=1; i<=3; i++)
    threads.create_thread(boost::bind(&work_thread, ios, i));

  boost::asio::deadline_timer timer(*ios);
  timer.expires_from_now(boost::posix_time::seconds(10));
  timer.async_wait(better_late_than_never);

  std::cin.get();
  ios->stop();
  
  threads.join_all();

  return 0;
}

