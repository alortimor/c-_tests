#include <iostream>
#include <thread>
#include <string>

void function_1() {
  std::cout << "Hello World" << std::endl;
};

// Functor
class Fctor {
  public:
    void operator()(std::string msg ) {
      std::cout << "t1 says: " << msg << std::endl;
      msg = "Appear";
      // for (int i=0; i > -100; i--)
      //  std::cout <<"from t1 " << i << std::endl;
    }

};


int main () {
  
  
  /* 
   REALLY IMPORTANT
   Parameter to a thread is always passed by value, not by reference
   ` 
   * 
   * 
  */
  std::string s = "Goodbye";
  // Fctor fct;
  // stdout is now a shared resource, which is owned by main thread
  // std::thread t1(fct);
  
  // you can also declare the above as 
  // std::thread t1( (Fctor()) );
  
  std::thread t1( (Fctor()), s );

  // Note!!!, You cannot declare it as 
  // std::thread t1(Fctor()); // since, in this case, a function is passed as an argument
  // this declares a function t1, the function t1 is passed a single parameter, Fctor(), which
  // is a pointer to another function and this function, Fctor(), takes no parameter and returns a
  // Fctor object instead.
  // The function t1 returns a thread however, so there is an anomaly, and it will not compile.
  
  
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
    // for (int i= 0; i<100; i++) {
     //  std::cout << "from main: " << i << "\n";
     std::cout << "from main " << s << std::endl;
    
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
