#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>


enum { max_length = 1024 };

void split_char_arr(char* arr, char c) {
    if (!arr) return;
    while (*arr != '\0' && *arr != c) arr++;
    *arr = '\0'; // set end character at new location
}

int main () {

  char request[max_length];
  std::string s {"Test string\nxxx"};
  strcpy(request, s.c_str());

  split_char_arr(request, '\n');
  std::cout << request << "\n";

  std::cout << strlen(request)  << "\n";

  std::strncat(request, "\n", 1);

  std::cout << strlen(request)  << "\n";
  std::cout << request ;
  std::cout << "Should be two lines down \n";
  
  return 0;
}
