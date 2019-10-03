#include <iostream>
#include <string>
#include <atomic>

class flower { 
  public:
    char c {'a'};
    int i {0};
    
    flower() { }
    ~flower() { }
};

int main()  {
  
  flower ar[7];
  std::atomic<flower*> p {ar};
  
  flower* temp = p.load(std::memory_order_relaxed);

  // std::atomic<T*> cannot make arbitrary operations atomic: only loading & storing data supported.
  // so the following will generate compile error
  // std::cout << p.c << "\n"; // error: ‘struct std::atomic<flower*>’ has no member named ‘c’
  
  std::cout << temp->c << "\n";
  return 0;
}
