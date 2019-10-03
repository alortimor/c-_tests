#include "time.h"
#include <iostream>

int main() {
  Time t1;
  Time t2;
  Time t3;
  t1 = t1 + 120;
  std::cout << t1;
  t2 += 30;
  t3 += 10;
  t1 = t2 + t3;
  std::cout << t1;
  t1 = t1 + 5;
  std::cout << t1;
  t1 = t1 - t3;
  std::cout << t1;
  t1 = t1 * 2; // double the time
  std::cout << t1;

  return 0;
}
