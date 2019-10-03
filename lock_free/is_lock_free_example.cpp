#include <atomic>
#include <iostream>
#include <thread>
#include <vector>


/*
std::atomic_flag does not provide load or store operations.

is_lock_free() determines whether operations on a given type are done directly with atomic
instructions (true) or by using a lock internal to compiler & library (false).


*/

/*

3 categories of operations operations divided into 3 categories:

1. Store operations             - can have memory_order_relaxed, memory_order_release or memory_order_seq_cst ordering
2. Load operations              - can have memory_order_relaxed, memory_order_consume, memory_order_acquire, 
                                  or memory_order_seq_cst ordering
3. Read-modify-write operations - can have memory_order_relaxed, memory_order_consume, memory_order_acquire, 
                                  memory_order_release , memory_order_acq_rel, or memory_order_seq_cst ordering
*/


// default ordering for all operations is memory_order_seq_cst

/* clear() and test_and_set() can have memory ordering  specified

clear() is a store operation, so cannot have memory_order_acquire or memory_order_acq_rel

test_and_set() is a read-modify-write operation, so any any memory ordering can be specified


*/

/*
Common to all atomic types is that you cannot copy-construct atomic object from another atomic, and
you can’t assign one to another!!!
*/

// std::atomic_flag has to be set using ATOMIC_FLAG_INIT. No other way to initialise a variable of
// type std::atomic_flag!!

// use atomic<bool> instead os std::atomic_flag as it has a few more features
std::atomic_flag lock = ATOMIC_FLAG_INIT;
 
void f(int n) {
    for (int cnt = 0; cnt < 100; ++cnt) {
      
        // test_and_set() member functions query and set an atomic_flag
        while(std::atomic_flag_test_and_set_explicit(&lock, std::memory_order_acquire))
             ; // spin until the lock is acquired

        std::cout << "thread output " << n << '\n';
        std::atomic_flag_clear_explicit(&lock, std::memory_order_release);
    }
}

int main() {
    std::vector<std::thread> v;
    for (int n = 0; n < 10; ++n)
      v.emplace_back(f, n);

    for (auto& t : v)
      t.join();
}

// std::atomic_flag does not provide the is_lock_free function
