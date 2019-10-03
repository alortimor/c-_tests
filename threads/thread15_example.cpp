#include <string>
#include <future>
#include <iostream>

using namespace std;


int factorial (std::shared_future<int> f) {
  int res = 1;
  int N = f.get();

  for (int i=N; i>1; i--)
    res *= i;
    
  return res;
}

// If you have more than one future thread, then you would naturally need more than one promise,
// one for each future. This is rather clumsy though, since it is a lot of unnecessary coding.

// Solution is to have a shared_future, which will enable a shared get() function call.

int main() {
  int x {0};
  
  std::promise<int> p;
  
  // a separate future object is required due to the fact that a promise is made,
  // which is fulfilled some time in the future.
  std::future<int> f = p.get_future();
  std::shared_future<int> sf = f.share();

  // so the main thread promises to send the initial value for the factorial to the child thread
  
  // so the future promise must be passed as a reference argument to the factorial function
  std::future<int> fu = std::async(std::launch::async, factorial, sf);
  std::future<int> fu2 = std::async(std::launch::async, factorial, sf);
  std::future<int> fu3 = std::async(std::launch::async, factorial, sf);
  
  // so the the f.get(); in the factorial function waits until the promise is fulfilled.
  // do something 
  std::this_thread::sleep_for(std::chrono::milliseconds(20));

  // and now the main thread fulfills its promise
  p.set_value(4); 
  
  x = fu.get();

  // If the promise is not fulfilled, then an exception is raised,
  // An explicit exception can be passed to the future promise
  // p.set_exception(std::make_exception_ptr(std::runtime_error("Explicit Exception")));

  // Note !!!! Niether promise or future can be copied, they can only be moved
  cout << x;
  return 0;

}


