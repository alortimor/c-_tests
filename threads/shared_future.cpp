#include <future>
#include <iostream>
#include <deque>

int factorial(int N) {
  int res = 1;
  for (int i=N; i>1; i--) {
    res *= i;
  }
  return res;
}

std::deque<std::packaged_task<int()> > task_q;
std::mutex mu;
std::condition_variable cond;


void thread_1() {
  std::packaged_task<int()> t;
  { // ensure that getting the packages task (t) from the front of the queue
    // and popping it off the queue is performed as a single autonomous action
    // hence the mutex lock

    // std::lock_guard<std::mutex> locker(mu);
    
    // when using a condition variable, a unique_lock must be used, instead of lock_guard
    std::unique_lock<std::mutex> locker(mu); // 
    
    cond.wait(locker, []() { return !task_q.empty();}); // wait for task package to be available on queue
    
    t = std::move(task_q.front()); // the move occurs, since t is not referenced in the main thread
    task_q.pop_front();
  }
  t();
}


int main() {

  std::thread t1(thread_1);
  
  std::packaged_task<int()> t(std::bind(factorial, 4)); // "int" removed
  std::shared_future<int> fu = t.get_future();
  {
    std::lock_guard<std::mutex> locker(mu);
    task_q.push_back(std::move(t));
  }
  cond.notify_one();

  std::cout << fu.get() << std::endl;

  t1.join();
  return 0;
}
