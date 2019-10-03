#include <thread>
#include <iostream>

long do_something(int i) { 
  std::cout << i << " squared " << i * i << std::endl;
  return i*i;
}

struct func {
  int& i;
  func(int& i_):i(i_){}
  void operator()() {
    for(unsigned j=0;j<100;++j) {
      i = j;
      std::cout << " " << i << " squared " << i*i << "\n"; // Potential access to dangling reference
    }
  }
};

int main () {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();
  return 0;
} // my_thread might still be running
