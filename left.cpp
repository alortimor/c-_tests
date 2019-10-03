#include <iostream>
const int ArSize = 80;
char * left (const char * str, int n = 1);

int main() {
  char sample[ArSize];
  std::cout << "Enter a string:\n";
  std::cin.get(sample, ArSize);
  char *ps = left(sample, 4);

  std::cout << ps << std::endl;
  delete [] ps;
  ps = left(sample);
  std::cout << ps << std::endl;
  delete [] ps;
  return 0;
}

// default argument value should be left out from the function definition
// and should only occur in the function prototype

char * left (const char * str, int n) {

  int len = strlen(str);
  n = (n < len) ? n : len; // set n to only the length that is required or the full length
                           // this prevents an error if a length greater than the actual
                           // length of the original string is specified

  char * p = new char[n+1];

  int i;
  for (i = 0; i < n && str[i]; i++)
    p[i] = str[i]; // copy characters

  while (i <= n)
    p[i++] = '\0'; // set rest of string to '\0'

  return p;

}
