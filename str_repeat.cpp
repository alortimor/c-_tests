#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include <string>

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
  std::istringstream  stm {"1 2  2 3  3 1  4 1  4 5  5 3  5 6  6 4  6 10"};
  std::map<unsigned short, std::map <unsigned short, unsigned short> > m;

  while (stm >> v1 >> v2) {
    m[v1]; // create the keys
    m[v1][v2] = 1; // set the value
  }

  int dc = digit_count(m.rbegin()->first); // equals 10
  std::string ss = "";

  for (const auto & p : m) {
    std::cout << p.first << ss.append(" ",  (dc - digit_count(p.first))) << "|";
    for (const auto & x : p.second)
      std::cout << x.first << "(" << x.second << ")";
    std::cout << "\n";
  }

  return 0;
}

