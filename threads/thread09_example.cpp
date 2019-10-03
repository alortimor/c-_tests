#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>


class LogFile {
  std::mutex _mu1;
  std::mutex _mu2; // protect resource with 2 resources
  // first mutex, _mu, is for security purposes and the second (_mu2) for file access purposes.

  std::ofstream _f;

  public:
    LogFile() {
      _f.open("log.txt");
    } // Need destructor to close file
    void shared_print1(std::string id, int value) {
      std::lock_guard<std::mutex> locker1(_mu1);
      std::lock_guard<std::mutex> locker2(_mu2);
      std::cout << "From " << id << ": " << value << std::endl;
    }
    void shared_print2(std::string id, int value) {
      std::lock_guard<std::mutex> locker2(_mu2);
      std::lock_guard<std::mutex> locker1(_mu1);
      std::cout << "From " << id << ": " << value << std::endl;
    }
};

void function_1(LogFile& log) {
  for (int i=100 ; i>=0 ; i--)
    log.shared_print1( std::string("t1: "), i); // lower level thread calls print1
}

// this code will hang, reason being a deadlock will occur.
// t1 locks mutex _mu1, and before the t1 thread has a chance to lock _mu2,
// the main thread has locked _mu2, the main thread needs to acquire _m1 and t1 
// needs to acquire _mu1, so a dealock ensues.

int main () {
  LogFile log;
  
  std::thread t1(function_1, std::ref(log));

  for (int i=0 ; i<100 ; i++)
    log.shared_print2( std::string("Main: "), i); // main thread calls print2

  t1.join();
  
  return 0;

}

