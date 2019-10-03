#include <iostream>
#include <thread>
#include <string>

void function_1() {
  std::cout << "Hello World" << std::endl;
};


int main () {
  
  // stdout is now a shared resource, which is owned by main thread
  std::thread t1(function_1);
  
  // if a thread is destroyed before the thread is joined or detached 
  // then the programme will terminate

  // if main thread throws an exception, then t1 is destroyed as well
  
  // for example, if the following were to be coded as
  /*
   * for (int i= 0; i<100; i++) {
    std::cout << "from main: " << std::to_string(i) << "\n";
  }
  * */
  // something like this instead:
  //for (int i= 0; i<100; i++) {
  //  std::cout << "from main: " + i + << "\n";
  //} 
  
  // so main will throw an exception and  t1 will be destroyed as a result
  
  // You can however  wrap main's workload in a try and then join t1, so
  // if main has any exception, t1 will still be joined
  
  // for example:
  try {
    for (int i= 0; i<100; i++) {
      std::cout << "from main: " << i << "\n";
    }
  }
  catch (...) {
    std::cout << "About to join " << std::endl;
    t1.join();
    throw;
  }


  if (t1.joinable()) {
    std::cout << "About to join: " << std::endl;
    t1.join();
  }
  return 0;

}
