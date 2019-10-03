#include <iostream>

int main() {

  int rats = 101;
  int & rodents = rats;

  std::cout << "rats = " << rats;
  std::cout << ", rodents = " << rodents << std::endl;
  
  std::cout << "Address of rates: " << &rats << std::endl;
  std::cout << "Address of rodents: " << &rodents << std::endl;

  int bunnies = 50;
  rodents = bunnies; //  this assignment will set rats to 50
  // the address of rodents is still the same, i.e. points to rats

  std::cout << "bunnies = " << bunnies;
  std::cout << ", rats = " << rats;
  std::cout << ", rodents = " << rodents << std::endl;

  
  std::cout << "Address of bunnies: " << &bunnies << std::endl;
  std::cout << "Address of rodents: " << &rodents << std::endl;

  return 0;
}


  
