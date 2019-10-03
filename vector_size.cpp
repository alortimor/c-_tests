#include <iostream>
#include <vector>
#include <algorithm>

int main() {

  std::vector<long double> vld {1, 2.5, 4.4, 5.5, 2.1, 99.2, -101.3, 1000};
  
  std::vector<long double> sorted(vld.size());
  std::sort (begin(sorted), end(sorted)); // do not disturb original sample

  // long double sz = sorted.size(); // simply to make the next line more readable!
  auto middle = sorted.begin() + sorted.size()/2;
  std::cout << sorted[*middle];
  // long double mid_value = (sz % 2) ? (sorted[sz / 2]) : ( (sorted[sz / 2 - 1] + sorted[sz / 2]) / 2 );

  return 0;

}
