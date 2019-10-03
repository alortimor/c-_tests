#include <deque>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <future>

using namespace std;

/*
void factorial (int N, int& x) {
  int res = 1;
  for (int i=N; i>1; i--)
    res *= i;
  x = res;
}

int main () {
  int x ;
  std::thread t1(factorial, 4, std::ref(x));
  // IMORTANT -- READ ****
  // variable "x" is a shared varaible between main thread and t1 thread
  // so some level of protection is required.

  t1.join();
  
  cout << x;
  
  return 0;

}
*/

/*
// therefore introduce a mutex and a condition variable
// however this complicates the code, since you now have to block, unblock, wait and loop
// 
std::mutex mu;
std::condition_variable cond;

void factorial (int N, int& x) {
  int res = 1;
  for (int i=N; i>1; i--)
    res *= i;
  x = res;
}

int main () {
  int x ;
  std::thread t1(factorial, 4, std::ref(x));
  // variable "x" is a shared varaible between main thread and t1 thread
  // so some level of protection is required.

  t1.join();
  
  cout << x;
  
  return 0;

}
*/

// Solution to simplify code is to introduce a future, which acts like a channel,
// from which the main thread can get a result from the child thread
// Global variables, condition_variable and mutex are no longer needed.

/*
 
int factorial (int N) {
  int res = 1;
  for (int i=N; i>1; i--)
    res *= i;
    
  return res;
}


int main () {
  int x ;

  // Note the factorial function no longer takes a second argument,
  // but instead has a return value "int"
  // A future object represents a class that results in a value some time in the future.
  std::future<int> fu = std::async(factorial, 4);
  x = fu.get(); // get function of a future object can only be called once
*/

/*
  // std::asynch may or may not create a thread
  // In the below case, the async function is deferred until the get is called.
  std::future<int> fu = std::async(std::launch::deferred, factorial, 4);
  x = fu.get();
*/

/*
  // In the below case, the async function creates another thread when called with sync launch.
  std::future<int> fu = std::async(std::launch::async, factorial, 4);
  x = fu.get();
*/

/*
  // In the below case, the async function creates either a thread or defers, depending on the 
  // implementation.
  // This is the default behaviour.
  // std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial, 4);
  // so the next line is equivalent to the above line
  std::future<int> fu = std::async(factorial, 4);
  x = fu.get();
  
  
  
*/

int factorial (std::future<int>& f) {
  int res = 1;
  int N = f.get();

  for (int i=N; i>1; i--)
    res *= i;
    
  return res;
}

int main() {
  int x {0};
  // the above code passes a return result from the child to the parent thread
  // The opposite can also be performed by using a future.
  // This can be achieved using a promise (std::promise)
  
  std::promise<int> p;
  
  // a separate future object is required due to the fact that a promise is made,
  // which is fulfilled some time in the future.
  std::future<int> f = p.get_future();
  // so the main thread promises to send the initial value for the factorial to the child thread
  
  // so the future promise must be passed as a reference argument to the factorial function
  std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
  
  // so the the f.get(); in the factorial function waits until the promise is fulfilled.
  // do the main thread can now do some other work, e.g.
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  
  // and now the main thread fulfills its promise
  // p.set_value(4); 
  
  // x = fu.get();

  // cout << x;
  
  // If the promise is not fulfilled, then an exception is raised,
  // An explicit exception can be passed to the futire promise
  p.set_exception(std::make_exception_ptr(std::runtime_error("Explicit Exception")));


  // Note !!!! Niether promise or future can be copied, they can only be moved
  cout << x;
  return 0;

}


