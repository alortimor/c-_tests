#include <iostream>
#include <thread>

static const int num_threads = 10;
 
void call_from_thread() {
  std::cout << "Hello World \n";
}
 
int main() {
  std::thread t[num_threads];

  for (int i = 0; i < num_threads; ++i) {
    t[i] = std::thread(call_from_thread);
  }

  std::cout << "Goodbye\n";
  for (int i = 0; i < num_threads; ++i) {
    t[i].join();
  }

  return 0;
}

