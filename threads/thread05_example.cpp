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
    }
};


int main () {

  // Prevent Oversubscription
  // More threads than are actually available causes a lot of context switching, 
  // so it is something to avoid.

  unsigned int n = std::thread::hardware_concurrency();
    
  std::cout << n << " concurrent threads supported.\n";
  
  return 0;

}
