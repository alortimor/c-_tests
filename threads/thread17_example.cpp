#include <future>
#include <iostream>
#include <chrono>

int factorial(int N) {
  int res = 1;
  for (int i=N; i>1; i--) {
    res *= i;
  }
  return res;
}

int main() {

  
  // std::thread t1(factorial, 6);

/*  
  // a packaged task can be passed around as a parameter
  std::packaged_task<int(int)> t(factorial); // Note you cannot pass arguments into a packages task
                                             // as you do for a normal thread
*/
// INSTEAD, an argument has to be bound to the function, and in so doing creates a function object, e.g.
/*
  std::packaged_task<int(int)> t(std::bind(factorial, 6));

  // Do some other work
  // ...
  
  t(6); // Will be executed later in a different context
*/

/*
// Since the parameter is bound up in std::bind, the task "t" no longer takes a parameter, 
// so the code  should be modified to remove the parameter from the packaged_task and the call of the task

  std::packaged_task<int()> t(std::bind(factorial, 6)); // "int" removed

  // Do some other work
  // ...
  
  t(); // Will be executed later in a different context - 6 no longer passe
*/
// You can simply use auto though
  // But with auto, you cannot associate the callable object to a future
  // auto t = std::bind(factorial, 6);
  std::packaged_task<int(int)> t(factorial); // "int" removed
  t(5);
  
  // do some other work
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  
  const int x = t.get_future().get(); // this will return the value from factorial
  std::cout << x << std::endl;

  return 0;
}
