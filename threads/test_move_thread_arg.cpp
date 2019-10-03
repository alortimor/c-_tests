#include <iostream>
#include <thread>
#include <string>
#include <memory>

void function_1() {
  std::cout << "Hello World" << std::endl;
};

// Functor
class Fctor {
  public:
    void operator()(std::string msg ) {
      std::cout << "t1 says: " << msg << std::endl;
      msg = "Appear";
    }
};

/*
 You cannot use std::move(s) when the ragument to the function that the thread
 calls is passed by reference, i.e (std::string& msg) // this WILL NOT compile 
 
 When an argument is by reference, (std::string& msg), then std::ref must to be used.
 * 
 When an argument is by value, (std::string msg), then std::move must be used. This is more efficient
 in the case of thread arguments.
 * 
*/

int main () {
  
  std::string s = "Goodbye";
  
  std::thread t1( ((Fctor())), std::move(s) );
  
  // to view unique id for thread
  std::cout << std::this_thread::get_id() << std::endl; // parent thread id
  std::cout << t1.get_id() << std::endl; // t1's thread is
  
  // you have to use the move function to transfer one thread to another
  std::thread t2 = std::move(t1);
  std::cout << t2.get_id() << std::endl; // t1's thread is
  // t1.join();
  // t1 can no longer be called, t2 must be called
  t2.join();
  std::cout << "from main " << s << std::endl;


  if (t1.joinable()) {
    std::cout << "About to join: " << std::endl;
    t2.join();
  }
  return 0;

}
