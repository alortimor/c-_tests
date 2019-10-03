#include "shoe.h"
#include <iostream>
#include <string>

int main() {

  std::string st {"Timberland"};
  Shoe s(st, 2015, 10);

  s.addSizePrice(6, 55.99);
  s.addSizePrice(7, 55.99);
  s.addSizePrice(6, 55.66);
  std::cout << s ;
  std::cout << "Average Price : " << s.avgPrice() << std::endl;

  return 0;

}
