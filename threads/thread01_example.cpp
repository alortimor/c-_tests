#include <iostream>
#include <thread>

void function_1() {
  std::cout << "Hello World" << std::endl;
};

int main () {
  
  // stdout is now a shared resource, which is owned by main thread
  std::thread t1(function_1);
  // t1.join(); // join instructs the main thread to wait for the 
                // t1 thread to complete before return to the main thread
                
  t1.detach();  // t1 will run as a daemon since you detatch from the main thread, but t1
                // will still run in the background.
                // "Hello World" will however not appear, since main will complete prior to t1 completing
                // even though both share stdout
                
  // once a thread is detached, then it is forever detached, so you cannot join at a later point.
  // t1.join();  // this will crash your programme
  
  // you can prvent a crash, but verifying if a thread is joinable at all, for example
  // if (t1.joinable())
  //   t1.join(); 
  

  if (t1.joinable())
    t1.join(); 

  return 0;

}
