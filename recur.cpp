#include <iostream>
void countdown(int n) {
  std::cout << n << ": Count  .. (n at " << &n << ")"<< std::endl;
  if (n > 0)
    countdown(n-1);
  std::cout << n << ": Unwrap .. (n at " << &n << ")" << std::endl;
}

int main() {
  countdown(4);
  return 0;
}

