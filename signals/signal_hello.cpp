#include <iostream>
#include <boost/signals2/signal.hpp>

// multiple slots

struct Hello {
  void operator()() const { std::cout << "Hello"; }
};

struct World {
  void operator()() const { std::cout << ", World!" << std::endl;}
};

struct Good {
  void operator()() const { std::cout << "good morning" << std::endl;}
};

// single slot

int main () {
 
  boost::signals2::signal<void ()> sig;

  sig.connect(1, World());
  sig.connect(0, Hello());
  sig.connect(Good());

  sig();
  
  return 0;
}

/*
struct HelloWorld
{
  void operator()() const
  {
    std::cout << "Hello, World!" << std::endl;
  }
};

int main() {
  // Signal with no arguments and a void return value
  boost::signals2::signal<void ()> sig;

  // Connect a HelloWorld slot
  HelloWorld hello;
  sig.connect(hello);

  // Call all of the slots
  sig();
  
}

*/
