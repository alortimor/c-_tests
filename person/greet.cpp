#include <iostream>

int main() {

  const int max = 15;
  char fname[max] = "Goodbye";
  
  char * fn  = "Hello";

  std::cout << fn << std::endl;
  std::cout << fname << std::endl;

  fname[0] = *fn;
  std::cout << fname << std::endl;

  return 0;
}
