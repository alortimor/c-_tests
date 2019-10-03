#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

// In order to protect the resource completely, a mutex must be bundled together with
// the resource it is protecting.

class LogFile {
  std::mutex m_mutex;
  std::ofstream f;

  public:
    LogFile() {
      f.open("log.txt");
    } // Need destructor to close file

    void shared_print(std::string id, int value) {
      std::lock_guard<std::mutex> locker(m_mutex);
      f << "From " << id << ": " << value << std::endl;
    }
    ~LogFile() { }
    
    // to protect the guard, NEVER return f to the outside world
    // for example, never have a function like this:

    // ofstream& getStream() { return f; } // this will give another process
                                            // an opportunity to access f without
                                            // going through the mutex
                                            
    // for the same reason, NEVER pass f as an argument to use provided function
    // void processf(void  fun (ostream&)) {
    //    fun(f);
    // }
    
};

void function_1(LogFile& log) {
  for (int i=9 ; i>=0 ; i--)
    log.shared_print( std::string("From t1: "), i);
}

int main () {
  LogFile log;
  
  std::thread t1(function_1, std::ref(log));

  for (int i=0 ; i<10 ; i++)
    log.shared_print( std::string("From main: "), i);

  // Messages appear in muddled order, i.e. sometime 
  // "From main" appears and sometimes "From t1"
  
  // instead of all of "From main", followed by all of "From t1"
  // This is known as a race condition.
  // Both threads are racing for the common resource, which in this case is stdout.
  
  // Typically race conditions are to be avoided.
  
  t1.join();
  
  // Using a mutex to synchronise the access of stdout will prevent the race condition
  // if the code between mu.lock() and mu.unlock() ends up raising an exception
  return 0;

}
