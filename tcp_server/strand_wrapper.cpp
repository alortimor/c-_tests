#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <mutex>
#include <thread>
#include <iostream>

std::mutex mx;

void work_thread(boost::shared_ptr<boost::asio::io_service> ios, int cnt) {

  // Ensure iostream is locked each time a cout is performed
  mx.lock();
  std::cout << "Thread " << cnt << " Start.\n";
  mx.unlock();

  ios->run();
  
  mx.lock();
  std::cout << "Thread " << cnt << " End.\n";
  mx.unlock();
}

void print_number(int number) {
  std::cout << "Number: " << number << std::endl;
}

int main(void) {
  
  boost::shared_ptr<boost::asio::io_service> ios (new boost::asio::io_service);
  boost::shared_ptr<boost::asio::io_service::work> worker (new boost::asio::io_service::work(*ios));

  boost::asio::io_service::strand strand(*ios);

  mx.lock();
  std::cout << "Exit when all work has completed.\n";
  mx.unlock();
  boost::thread_group threads;

  for(int i=1; i<=6; i++)
    threads.create_thread(boost::bind(&work_thread, ios, i));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ios->post(strand.wrap(boost::bind(&print_number, 1)));
  ios->post(strand.wrap(boost::bind(&print_number, 2)));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ios->post(strand.wrap(boost::bind(&print_number, 3)));
  ios->post(strand.wrap(boost::bind(&print_number, 4)));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ios->post(strand.wrap(boost::bind(&print_number, 5)));
  ios->post(strand.wrap(boost::bind(&print_number, 6)));

  worker.reset();
  threads.join_all();

  return 0;
}

