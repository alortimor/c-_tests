#include <iostream>

unsigned int c_in_str(const char *, char);

int main()
{
  char mmm[15] = "minimum"; // string is an array

  char *wail = "ululate"; // wail points to a string

  unsigned int ms = c_in_str(mmm, 'm');
  unsigned int us = c_in_str(wail, 'u');
  std::cout << ms << " m characters in " << mmm << std::endl;
  std::cout << us << " u characters in " << wail << std::endl;
	return 0;
}

unsigned int c_in_str(const char *str, char ch) {
  unsigned int count = 0;
  while (*str) {
    if (*str == ch)
      count++;
    str++;
  }
  return count;
}
