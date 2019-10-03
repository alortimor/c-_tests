#include <iostream>
#include <thread>
#include <string>
#include <mutex>

std::mutex mu;

void shared_print(std::string msg, int id) {
  mu.lock();
  std::cout << msg << id << "\n"; // if the code between mu.lock and mu.unblock causes an exception
                                  // then the mutex (mu) will end up being locked forever.

  mu.unlock();
}

// do not use mu.lock and mu.unblock as above in case code between mu.lock and mu.unblock
// throws an exception in which case the mutex will be forever locked, hence use a lock guard
// instead

// lock_guard is a mutex wrapper that provides a RAII-style mechanism for owning a mutex
// for the duration of a scoped block.
// When a lock_guard object is created, it attempts to take ownership of the mutex it is given.
// When control leaves the scope in which the lock_guard object was created,
// lock_guard is destructed and the mutex is released.

void shared_prn(std::string msg, int id) {
  std::lock_guard<std::mutex> guard(mu); // This is RAII 
  std::cout << msg << id << "\n";
  // lock is released and destroyed, the mutex however lives on
}

// This above shread_prn function, although better than shared_print, still poses
// a problem though.
// cout is shared amongst many other processes, so another thread could still use cout
// directly without going through the lock

// Therefore, in order to protect the resource completely, a mutex must be bundled together with
// the resource it is protecting. Refer to thread7_example.cpp for such an example.

void function_1() {
  for (int i=0 ; i>-100 ; i--)
    shared_prn( std::string("From t1: "), i);
}

int main () {

  std::thread t1(function_1);
  
  
  for (int i=0 ; i<100 ; i++)
    shared_prn( std::string("From main: "), i);

  // Messages appear in muddled order, i.e. sometime 
  // "From main" appears and sometimes "From t1"
  
  // instead of all of "From main", followed by all of "From t1"
  // This is known as a race condition.
  // Both threads are racing for the common resource, which in this case is stdout.
  
  // Typically race conditions are to be avoided.
  
  t1.join();
  
  // Using a mutex to synchronise the access of stdout will prevent the race condition
  // if the code between mu.lock() and mu.unlock() ends up raising an exception
  return 0;

}
