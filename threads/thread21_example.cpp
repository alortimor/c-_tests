#include <iostream>
#include <thread>

class thread_guard {
  std::thread& t;
  public:
    explicit thread_guard(std::thread& t_): t(t_) {}
    ~thread_guard() {
      if (t.joinable()) t.join();
    }

    // copy constructor and copy-assignment operator are marked "delete"
    // to ensure that they are not automatically provided by the compiler.
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete; // prevents compiler from 
};

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

int main() {
  int some_local_state=0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  
  // .. do something
  std::cout << "Do some other work..." << "\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // notice that the message "Do some other work..." occurs first,
  // since the thread join occurs when the main thread terminates, after the message


  // Alternative to join is detach.
  /*
  detach() makes thread to run in the background. 
  No direct means of communicating with it after detach.
  It’s no longer possible to wait for that thread to complete; 
  
  If a thread becomes detached, it isn’t possible to obtain a
  std::thread object that references it, so it can no longer be joined. 
  
  Detached threads truly run in the background; ownership and control are passed over to the
  C++ Runtime Library, which ensures that the resources associated with the thread are correctly
  reclaimed when the thread exits.
*/

  return 0;
}
