#include <iostream>
#include <random>

int round_to_hundred(int d) {
	// return ((d % 100) < 50) ? d - (d % 100) : d + (100 - (d % 100));
  return (d + 50) / 100 * 100;
}

int main() {
  
  int start{300}, end{2000};
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  
  std::uniform_int_distribution<>::param_type pt(start, end);
  std::uniform_int_distribution<int> distr(pt); // define the range

  std::cout << "start " << distr.min() << " end " << distr.max() << "\n";
  std::cout << "Sample Values: " << distr(eng) << ',' << distr(eng) << "\n";

  int n {distr(eng)};
	std::cout << n << " rounded to nearest 100 is " << ((n + 50) / 100 * 100)   << "\n"; // round to nearest hundred

  start = 1; end = 100;
  //pt.min(start);
  //pt.max(end);
  // distr.param(start,end);
  //std::uniform_int_distribution<>::param_type pt2(start, end);
  std::cout << "Sample Values: " << distr(eng, decltype(distr)::param_type(start, end) ) << ',' << distr(eng, decltype(distr)::param_type(start, end) ) << "\n";
  n = distr(eng, decltype(distr)::param_type(start, end) );
	std::cout << n << " rounded to nearest 10 is " << ((n + 5) / 10 * 10)   << "\n"; // round to nearest ten


  return 0;
}
