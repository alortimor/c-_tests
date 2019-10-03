#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::vector<int> make_data(int, int, int);

int main() {
  std::vector<int>  data {make_data(10, 1, 100)};
  std::for_each(data.begin(),data.end(),[](int i){std::cout<<i<<"\n";});
  return 0;
}

std::vector<int> make_data(int max, int start, int end) {
  
  std::vector<int> v;
  
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(start, end); // define the range

  for(int n=0; n<max; n++) v.emplace_back(distr(eng));

  return v;
}

