#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>

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
  unsigned short v1,v2;
  std::istringstream  stm {"1 2  2 3  3 1  4 1  4 5  5 3  5 6  5 7  5 8  6 4  7 6  8 9  9 10"};
  std::map<unsigned short, std::map <unsigned short, unsigned short> > m;
  while (stm >> v1 >> v2) {
    m[v1]; m[v2]; // create the key(s), v2 required as well in case there are no outbounds
    m[v1][v2] = 1; // set the value
  }

  int dc = digit_count(m.rbegin()->first); // equals 10

  // header
	for (const auto & p : m) {
		std::cout << "  " << p.first << "";
	}

	std::cout << "\n";

  // std::vector<int> row(10, 0);
  std::string ss;

  // body
  for (const auto & p : m) {    
    std::cout << p.first << ss( (dc - digit_count(p.first)), ' ') << "|";
/*    for (const auto & x : p.second) {
      row.at(x.first - 1) = 1;
      std::string ss(x.first, ' ');
      std::cout << ss;
      for (auto val : row)
        std::cout << (val == 1 ? 1 : 0) << ' ' << ' ';
    } */
    std::cout << "\n";
  }

  return 0;

}

