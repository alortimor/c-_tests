#include<iostream>
#include<chrono>
#include<thread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/thread/future.hpp>

int Task(int x, std::chrono::time_point<std::chrono::high_resolution_clock> start) {
  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  std::cout << std::endl << "Starting : " << x << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(10 * x));
  std::cout << std::endl << "Ending : " << x << std::endl;
  end = std::chrono::high_resolution_clock::now();
  auto elapsed_time = end-start;
  std::cout <<"Expected : " << (10 * x) << "ms, Elapsed time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() << "ms\n";
  return x;
}

int main () {
  const int kThreadCount = 100;
  std::vector<boost::future<int>> futures;
  for (auto i(kThreadCount); i != 0 ; --i) {
    auto fut = boost::async([i]() { return Task(i, std::chrono::high_resolution_clock::now()); });
    futures.push_back(std::move(fut));
  }

  for (auto i(0); i < kThreadCount ; ++i) {
    auto res = boost::wait_for_any(futures.begin(), futures.end());
    std::this_thread::yield();
    std::cout << std::endl << " one out : " << res->get() << std::endl;
  }
}
