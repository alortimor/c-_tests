#include <iostream>

char * buildstr(char, int);

int main() {

  int times = 0;
  char ch;

  std::cout << "Enter character: ";
  std::cin >> ch;
  std::cout << "Enter integer: ";
  std::cin >> times;
  char *ps = buildstr(ch, times);
  std::cout << ps << std::endl;
  delete [] ps;
  ps = buildstr('+', 20);
  std::cout << ps << "-DONE-" << ps << std::endl;
  delete [] ps;
  
	return 0;
}

char * buildstr(char c, int n) {
  char * pstr = new char[ n + 1];
  pstr[n] = '\0';
  while (n-- > 0)
    pstr[n] = c;
  return pstr;
}
