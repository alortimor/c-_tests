#include <iostream>
#include "person.h"

int main() {
  std::string &&fn = "Peter";
  char * ln = "Koukoulis";
  Person one;
  Person two(fn, ln);
  Person three("Morgan");

  two.Show();
  one.Show();
  three.Show();
  std::cout << std::endl;
  one.FormalShow();
  // etc. for two and

  return 0;
}
