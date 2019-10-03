#include <deque>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <atomic>
#include <condition_variable>


std::deque<int> q; // global variable
std::mutex mu; //
std::condition_variable cond;

// producer
void function_1() {
  int count = 10;
  while (count > 0) {
    std::unique_lock<std::mutex> locker(mu);
    q.push_front(count);
    locker.unlock();
    cond.notify_one(); // Notify a single thread that is waiting on the condition "cond"
//    cond.notify_all(); // Notify all waiting threads
    std::this_thread::sleep_for(std::chrono::seconds(1)); // sleep for a second before next loop
    count--;
  }
}


// consumer
// function_2 is in a busy waiting state, since it keeps checking
// and then loops, this is inefficient.
/*
void function_2() {
  int data = 0;
  while (data != 1) {
    std::unique_lock<std::mutex> locker(mu);
    if (!q.empty()) {
      data = q.back();
      q.pop_back();
      locker.unlock();
      std::cout << "t2 obtained value from t1 " << data << std::endl;
    }
    else {
      locker.unlock();
      // You could possibly introduce a sleep in order to reduce the number of loops, e.g.
      // std::this::thread::sleep_for(std::chrono::milliseconds(10));
      // the problem with this approach is that you diminish opportunities for
      // concurrency, since data might be available and yet the loop is blocking whilst 
      // the sleep is performing.
      // On the other hand if the time is too short, and no data is available, then you'll still end up
      // looping too many times and thus consuming valudable CPU cycles that impact other
      // processes..
    }
  }
}

*/
// Solution to the above problem is to introduce a condition variable:

void function_2() {
  int data = 0;
  while (data != 1) {
    std::unique_lock<std::mutex> locker(mu);
    // cond.wait(locker); // prone to spurious wake
                          // condition variable ensures that no looping occurs and that
                          // popping of data will only occur once function_1 thread has in fact
                          // pushed data.
                          // So the condition variable ensures that thread 1 and thread 2 execute in
                          // predefined order.
                          // wait(locker), unblocks the locker and then goes to sleep, so as
                          // to remove any blocking on the locked mutex, hence wait takes the locker
                          // as a  parameter.
                          // When the condition variable is set to true, it will lock the locker
                          // and then proceed to access the queue.
                       
                          // after data is popped, lock is unlockd once again.
                          // Given that the unique_lock has to be locked and unlocked several times,
                          // a unique lock is required, instead of a lock_guard.

    // in the case below, if a spurious wake does occur, the condition variable will first
    // verify if q is indeed empty before continuing, otherwise it will go back to sleep again.
    cond.wait(locker, [](){ return !q.empty();} );
    data = q.back();
    q.pop_back();
    locker.unlock();
    std::cout << "t2 obtained value from t1 " << data << std::endl;
    }
  }
}


int main () {
  std::thread t1(function_1);
  std::thread t2(function_2);

  t1.join();
  t2.join();
  
  
  return 0;

}

