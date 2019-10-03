# include <iostream>
# include <thread>
# include <atomic>
# include <condition_variable>

// the condition variable is dependent on readyFlag
bool readyFlag{false};

// condition_variable is used in combination with 
// a std::mutex to facilitate inter-thread communication.
std::mutex mutexReady;
std::condition_variable cond_varReady;

void function_1()
{
    //wait until main thread is ready (readyFlag == true)
    {
      std::unique_lock<std::mutex> ul(mutexReady);

      // blocks the current thread until the condition variable is woken up
      cond_varReady.wait(ul, [] { return readyFlag; });

    } //release lock

    // start the countdown in the lower thread
    for (int i= 10 ; i > 0 ; --i) {
        std::cout << "From t1: " << i << "\n";
    }
}

int main () {
    std::thread t1(function_1);

    {
      //start counting up in the main thread
      for (int i = 1 ; i <= 10 ; ++i) {
        std::cout << "From main: " << i << std::endl;
      }
      //signal that main thread has prepared a condition
      {
          std::lock_guard<std::mutex> lg(mutexReady);
          readyFlag = true;
      } // release lock
      cond_varReady.notify_one(); // notifies one waiting thread 
                                  // .notify_all() would notify all waiting threads
    }
    t1.join();

    return 0;
}
