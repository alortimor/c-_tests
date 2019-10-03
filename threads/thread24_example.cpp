#include <iostream>
#include <thread>
#include <string>

struct big_object {
  private:
    int data;
  public:
    big_object() {}
    void prepare_data(int x) { data = x; }

    void operator()() {
      for(unsigned j=0;j<100;++j) {
        std::cout << "number: " << j << " squared " << j*j << "\n"; // Potential access to dangling reference
      }
    }
};

void process_big_object(std::unique_ptr<big_object> p) {
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  p->big_object();
}

int main() {

/* 
void some_function();
void some_other_function();
std::thread t1(some_function); // new thread start

std::thread t2=std::move(t1); // Ownership transferred over to t2 when t2 is constructed, 
                              // by invoking std::move() to explicitly move ownership. 
                              // At this point, t1 no longer has an associated thread of execution;
                              // the thread running some_function is now associated with t2.

t1=std::thread(some_other_function);

std::thread t3; // default constructor, created without any associated thread of execution
* 
t3 = std::move(t2); // Ownership of thread t2 is transferred to t3, 
                    // with an explicit call to std::move().
                    
                    // t1 is now associated with the thread running some_other_function
                    // t2 has no associated thread
                    // and t3 is associated with the thread running some_function.

t1 = std::move(t3); // transfers ownership of the thread running some_function back
                    // to t1 where it started. However, t1 already had an associated
                    // thread (some_other_function), so td::terminate() is called to terminate
                    // the program.


*/  

  std::unique_ptr<big_object> p(new big_object);
  p->prepare_data(42);
  std::thread t(process_big_object,std::move(p));

  t.join();
  return 0;
}
