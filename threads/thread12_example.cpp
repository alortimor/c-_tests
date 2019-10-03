#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>


class LogFile {
  std::mutex _mu;
  std::mutex _mu_open
  std::ofstream _f;

  public:
    LogFile() {  } // the open file from the constructor, since it only needs to be opened if a 
                   // print is performed
    void shared_print(std::string id, int value) {

      // use a mutex to protect file open, otherwise multiple opens could occur
      // do not use _mu, since _mu is used for printing and mixing the two operations
      // with a single mutex could cause complications.
      /*
      if (!_f.is_open("log.txt")) {
        std::unique_lock<mutex> locker2(_mu_open);
        _f.open("log.txt"); // known as lazy initialisation
      }
      */
      // the above is not thread safe, since 2 threads can verify "is_open" and discover
      // the file not to be open yet, and then both attempt to lock, 1 will be blocked until
      // the other opens the file and when the function completes, the lock is then released.
      // The thread that was blocked on unique lock will then unblock and proceed to open the file.
      // So the file is opened twice.
        
      // So the solution is to combine is_open with open in a single lock mutex.
      /*
      {
        std::unique_lock<mutex> locker2(_mu_open);
        if (!_f.is_open("log.txt"))
          _f.is_open("log.txt");
      }
      */

      // now the code is thread safe, but now the problem is that each time a print
      // occurs, a lock and an unlock for locker2 will be processed, which will impact performance
      // by consuming valuable computing cycles and it also hinders the system from being
      // generally concurrent.
      
      // Solution is to use std::once_flag _flag;
      std::call_once(_flag, [&](){ _f.open("log.txt"); }); // file will be opened only once by one thread
      std::unique_lock<std::mutex> locker(_mu, std::defer_lock); 
      _f << "From " << id << ": " << value << std::endl;

    }
    ~LogFile();
};


void function_1(LogFile& log) {
  for (int i=100 ; i>=0 ; i--)
    log.shared_print( std::string("t1: "), i);
}

int main () {
  LogFile log;
  
  std::thread t1(function_1, std::ref(log));

  for (int i=0 ; i<100 ; i++)
    log.shared_print( std::string("Main: "), i);

  t1.join();
  
  return 0;

}

