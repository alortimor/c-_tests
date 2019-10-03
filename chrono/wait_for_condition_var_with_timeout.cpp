#include <condition_variable>
#include <mutex>
#include <chrono>
#include <iostream>

int main () {

  std::condition_variable cv;
  bool done {false}; // done will never be true
  std::mutex m;

  auto const timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000);
  std::unique_lock<std::mutex> lk(m);

  while (!done) {
    if(cv.wait_until(lk,timeout) == std::cv_status::timeout) // done is never true, so timeout will occur
      break;
  }

  std::cout << "Timeout occured\n";
  return 0;

}
