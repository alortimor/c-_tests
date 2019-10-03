#include <iostream>

const int ArSize = 8;
int sum_arr(const int *, const int *);

int main() {
  int cookies[ArSize] = {1,2,4,8,16,32,64,128};

  int sum = sum_arr(cookies, cookies + ArSize);
  std::cout << "Total cookies consumed: " << sum << std::endl;

  sum = sum_arr(cookies, cookies + 3);
  std::cout << "First 3 consumed: " << sum << std::endl;

  sum = sum_arr(cookies + 4, cookies + 8);
  std::cout << "Last 4 consumed: " << sum << std::endl;

  return 0;
}

int sum_arr(const int * begin, const int * end) {
  const int *pt;
  int total = 0;

  for (pt = begin; pt != end; pt++)
    total += *pt;

  return total;
}
