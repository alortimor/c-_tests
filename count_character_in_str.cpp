#include <algorithm>
#include <string>
#include <iostream>

int main() {
  
  char ch;
  std::string msg;
  std::cout << "Enter a character to search for: " ;
  std::cin >> ch;

  std::cout << "Enter a string o serach in: " ;
  std::cin.ignore();
  getline (std::cin, msg);
  unsigned short c = std::count (msg.begin(), msg.end(), ch);
 
  std::cout << "Number of occurrences of " << c << " of character " << ch << " in " << msg << "\n";
  return 0; 
}
