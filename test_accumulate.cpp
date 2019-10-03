#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <sstream>      // std::stringstream
#include <iomanip>

int sq(int c, int d) {return c+d*d;}   

int digit_count(int number) {
  int digits = 0;
  if (number < 0) digits = 1; // remove this line if '-' counts as a digit
  while (number) {
      number /= 10;
      digits++;
  }
  return digits;
}

int main () {
  int numbers[]={10,20,30};
  int result;
  result = std::accumulate (numbers, numbers+3, 100, std::minus<int>());
  std::cout << "The result of 100-10-20-30 is " << result << ".\n";

  int sample[]={3 ,21 ,98 ,203 ,17 ,9};
  result = std::accumulate (sample, sample+6, 0, sq);
  std::cout << "The result of squares is " << result << ".\n";

  std::vector<double> v {1.2, 5.5, 9.9, 4.4, 3.3, 101.2};

  double sum = std::accumulate(begin(v), end(v), 0.0);
  double mean = sum / v.size();

  std::vector<double> diff(v.size());
  std::transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  // double stdev = std::sqrt(sq_sum / v.size());

  std::cout << "Variance : " << sq_sum/(v.size() -1) << std::endl;

  std::transform(v.begin(), v.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
  sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  std::cout << "Variance : " << sq_sum/(v.size() -1) << std::endl;

  unsigned short v1,v2;
  std::istringstream  stm {"1 2  2 3  3 1  4 1  4 5  5 3  5 6  5 7  5 8  6 4  7 6  8 9  9 10"};
  // std::map< T, std::map< T, T> >
  std::map<unsigned short, std::map <unsigned short, unsigned short> > m;
  // 1 2  2 3  3 1  4 1  4 5  5 3  5 6  5 7  5 8  6 4  7 6  8 9  9 10
  while (stm >> v1 >> v2) {
    m[v1]; m[v2]; // create the key(s), v2 required as well in case there are no outbounds
    m[v1][v2] = 1; // set the value
  }


  int dc = digit_count(m.rbegin()->first);
  
  // header
	for (const auto & p : m) {
		std::cout << "  " << p.first << "";
	}

	std::cout << "\n";

  std::vector<int> row(10, 0);
  std::string ss;

  // body
  for (const auto & p : m) {    
    std::cout << p.first << ss( (dc - digit_count(p.first)), ' ') << "|";
    for (const auto & x : p.second) {
      // std::cout << std::string(x.first, "  ");
      row.at(x.first - 1) = 1;
      std::string ss(x.first, ' ');
      std::cout << ss;
      for (auto val : row)
        std::cout << (val == 1 ? 1 : 0) << ' ' << ' ';
    }
    std::cout << "\n";
  }

  

  return 0;

}

