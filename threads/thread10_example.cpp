#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>


// Refer to explanation of deadlock in thread9_example.cpp, before reading this eample.
// To avoid deadlock, lock mutex's in the same order in both print functions
/*
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
      std::lock_guard<std::mutex> locker2(_mu2);
      std::lock_guard<std::mutex> locker1(_mu1);
      std::cout << "From " << id << ": " << value << std::endl;
    }
    void shared_print2(std::string id, int value) {
      std::lock_guard<std::mutex> locker2(_mu2);
      std::lock_guard<std::mutex> locker1(_mu1);
      std::cout << "From " << id << ": " << value << std::endl;
    }
};
*/

// The above will not results in a deadlock, but a better solution is
// to use std::lock, which locks multiple mutex's for you in the right order.
// There is however an additional parameter that is required for lock_guard (std::adopt_lock),
// which informs the lock_guard that the mutex's are already locked and that lock_guard simply
// has to adopt the existing lock sequence.
// std::lock uses deadlock avoidance algorithms.
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
      std::lock(_mu1, _mu2);
      std::lock_guard<std::mutex> locker1(_mu1, std::adopt_lock);
      std::lock_guard<std::mutex> locker2(_mu2, std::adopt_lock);
      std::cout << "From " << id << ": " << value << std::endl;
    }
    void shared_print2(std::string id, int value) {
      std::lock(_mu1, _mu2);
      std::lock_guard<std::mutex> locker2(_mu2, std::adopt_lock);
      std::lock_guard<std::mutex> locker1(_mu1, std::adopt_lock);
      std::cout << "From " << id << ": " << value << std::endl;
    }
};

// However, be cautious not to use too many mutex's though.
// Decide whether two mutex's.
// Another way to solve a deadlock is to use one mutex at a time, for example:

/*
void  shared_print2(std::string id, int value) {
  {
    std::lock_guard<mutex> locker1(_mu1);
  }
  {
    std::lock_guard<mutex> locker2(_mu2);
    std::cout << "From " << id << ": " << value << std::endl;
  }
}
*/

// AVOID !!! calling a user function after a lock_guard<mutex> lock,
// the user function might perform a lock, which you may not know about, which
// will cause problems and may lead to deadlock.

// Therefore only place you own code within a lock scope.

// AVOID !!! the case where a lower level mutex locks a higher level mutex

// Generally
/*
- Fine-grained lock: protects small amount of data
- Course-grained lock: protects big amount of data
* 
If you make your code too fine-grained then you increase the possibility of deadlock, on
the other hand, if your code is to course-grained then you diminish the opportunities for
parallelism and thus impact performance.
*/


void function_1(LogFile& log) {
  for (int i=100 ; i>=0 ; i--)
    log.shared_print1( std::string("t1: "), i); // lower level thread calls print1
}

// No hanging this time round, since mutex's are locked in the same order.

int main () {
  LogFile log;
  
  std::thread t1(function_1, std::ref(log));

  for (int i=0 ; i<100 ; i++)
    log.shared_print2( std::string("Main: "), i); // main thread calls print2

  t1.join();
  
  return 0;

}

