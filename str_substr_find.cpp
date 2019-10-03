#include <iostream>
#include <string>
#include <algorithm>


template<typename Iter>
Iter nth_occurence(Iter first, Iter last, Iter first_, Iter last_, unsigned nth) {
  Iter it = std::search(first, last, first_, last_);
  if (nth == 0) return it;
  if (it == last) return it;
  return nth_occurence(it + std::distance(first_, last_), last, first_, last_, nth -1);
}
unsigned int nthOccurrence(const std::string& str, const std::string& findMe, unsigned int nth) {
  unsigned int pos {0};
  unsigned int cnt {0};

  while( cnt != nth ) {
      pos-=1;
      pos = str.rfind(findMe, pos);
      if ( pos == std::string::npos )
          return -1;
      cnt++;
  }
  return pos;
}


int main() {

  std::string s {"'Kris','Ma','King, Christophe','228 Runamuck Pl #280','Baltimore','Baltimore City','MD',21224,'410-655-8723'"};
  // std::string s {"1,1,1,'CA','xxx','aaa'"};
  std::string c{","};
  //auto it1 = nth_occurence(begin(s), end(s), begin(c), end(c), 5);

  std::cout << "\nResult string : " << s << "\n";

  //std::cout << std::distance(begin(s), it1) << "\n";
  unsigned int p { (nthOccurrence(s, c, 3)+1) };
  std::cout <<  p << " " << s.substr(p+1,2) << "\n";


  return 0;
}
