#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>


class LogFile {
  std::mutex _mu;

  std::ofstream _f;

  public:
    LogFile() {
      _f.open("log.txt");
    } // Need destructor to close file
    void shared_print(std::string id, int value) {
      // std::lock_guard<std::mutex> locker(_mu);
//      std::unique_lock<std::mutex> locker(_mu); // similar to lock_guard, 
                                                // but it provides greater flexibility
      
      std::unique_lock<std::mutex> locker(_mu, std::defer_lock); // passing std::defer_lock as an argument
                                                                 // results in mutex not locked when unique lock is constructed

      // now you have an opportunity to do something else that does not deal with the critical section
      
      // now deal with the critical section
      
      locker.lock();
      _f << "From " << id << ": " << value << std::endl;
      // for example, 1 of the fexibilities provided is the ability to unlock, after a critical section
      locker.unlock(); // this gives you the ability to implement a finer grained lock
      
      //..
      // you can now lock again
      // lockeer.lock(); // so you can lock and unlock at any point, which cannot be done with lock_guard


      // VERY IMPORTANT!!!
      // niether std::lock_guard nor std::unique_lock can be copied, but std::unique_lock can be moved
      
      // when moving a std::unique_lock ownership of the mutex is transferred from one
      // unique lock to another, for example
      std::unique_lock<std::mutex> locker2 = std::move(locker);
      
      // performance of std::lock_guard is however much better than std::unique_lock
      // so if performance is a concern, then consider std::lock_guard instead of std::unique_lock
    }
};


void function_1(LogFile& log) {
  for (int i=100 ; i>=0 ; i--)
    log.shared_print( std::string("t1: "), i); // lower level thread calls print1
}

// No hanging this time round, since mutex's are locked in the same order.

int main () {
  LogFile log;
  
  std::thread t1(function_1, std::ref(log));

  for (int i=0 ; i<100 ; i++)
    log.shared_print( std::string("Main: "), i); // main thread calls print2

  t1.join();
  
  return 0;

}

