# include <iostream>
# include <thread>
# include <atomic>

// Following on from on from the explanation in condition_var_thread_eg1.cpp
// if std::atomic<bool> was used instead of the 'normal' boolean variable 
// there is no need for std::mutex to set the ready flag as operations are 
// now guaranteed to be atomic.

std::atomic<bool> readyFlag{false};

void function_1() {
    while (!readyFlag.load()) { // load atomically obtains value of readyFlag, the while waits until true
        std::this_thread::yield(); // reschedule the execution of main threads, allowing other threads to run.
    }
    // readyFlag is now true, so counting down can begin
    for (int i = 10 ; i > 0 ; --i) {
       std::cout << "From t1: " << i << std::endl;
    }
}

int main () {
    std::thread t1(function_1);

    {
        //do the printing from the main thread first
        for (int i = 1 ; i <= 10 ; ++i) {
            std::cout << "From main: " << i << std::endl;
        }

        ////signal that main thread is done
        readyFlag.store(true);
    }
    t1.join();
}
