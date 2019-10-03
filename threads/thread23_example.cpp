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
Another scenario for supplying arguments is where arguments cannot be copied, 
but only be moved.
Data held within one object is transferred over to another, leaving the
original object "empty." 
An example is a std::unique_ptr, which provides automatic memory management for 
dynamically allocated objects. 
Only one std::unique_ptr instance can point to a given object at a time,
and when that instance is destroyed, the pointed-to object is deleted. 
The move constructor and move assignment operator allow the ownership of an
object to be transferred around between std::unique_ptr instances.
Such a transfer leaves the source object with a NULL pointer.
This moving of values allows objects of this type to be accepted as function
parameters or returned from functions.
Where the source object is a temporary, the move is automatic, but where the
source is a named value, the transfer must be requested directly
by invoking std::move().

*/  

  std::unique_ptr<big_object> p(new big_object);
  p->prepare_data(42);
  std::thread t(process_big_object,std::move(p));

  t.join();
  return 0;
}
