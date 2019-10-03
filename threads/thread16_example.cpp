#include <string>
#include <future>
#include <iostream>

using namespace std;


class A {
  public:
    void f(int x, char c) { }
    long g(double x) { return 0; }
    int operator()(int N) { return 0; }
  
  //void f(int , std::string) { }
};

void foo(int x) {}

int main() {
  A a;
  
  // Up to this point, 2 ways to launch a thread have been used, one is to use std::thread, 
  // the other is to use std::async function
  // std::thread is a class, t1 is an object
  std::thread t1(a, 6);  // callable object, a in this case, need not be a functor. 
  // It could be a lambda or a normal function, for example:
  std::thread t4([](int x){return x*x;}, 6);
  
  std::thread t5(foo, 7);
  // t1 makes a copy of "a" and uses it in a separate thread.

  // if you don't want a to be copied, then use std::ref instead
  std::thread t2(std::ref(a), 6); 


  // you can also create a temporary object of A, which is then moved into the thread
  std::thread t3(A(), 6); 
  
  // You can also call a member of a class
  std::thread t6(&A::f, &a, 8, 'w');  // this makes a copy of a, and then calls f, in a different thread
  
  // you can use move instead of passing by reference
  std::thread t7(std::move(a), 6); // when using move, make sure that "a" is no longer used in  main thread!

  // this is a function call, unlike std::thread
  //std::async(std::launch::aync, a, 6);
  
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  
  return 0;

}


