#include <iostream>

int main() {

  int rats = 101;
  int & rodents = rats;

  std::cout << "rats = " << rats;
  std::cout << ", rodents = " << rodents << std::endl;
  rodents++;
  std::cout << "rats = " << rats;
  std::cout << ", rodents = " << rodents << std::endl;
  
  std::cout << "Address of rats: " << &rats << std::endl;
  std::cout << "Address of rodents: " << &rodents << std::endl;

  return 0;
}


  
