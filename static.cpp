#include <iostream>
using namespace std;
const int ArSize = 10;

void strcount(const char *);

int main() {
  using namespace std;
  char input[ArSize];
  char next;

  cout << "Enter a line:\n";
  
  cin.get(input, ArSize);

  while (cin) {
    cin.get(next);
    while (next != '\n') // string didn't fit!
      cin.get(next);     // dispose of remainder

    strcount(input);
    cout << "Enter next line (empty line to quit):\n";
    cin.get(input, ArSize);
  }

  cout << "Bye\n";
  return 0;
}

void strcount(const char * str) {
  using namespace std;
  static int total = 0; // static local variable
  int count = 0; // automatic local variable
  
  cout << "\"" << str <<"\" contains ";
  while (*str++)  // go to end of string
    count++;

  total += count;
  cout << count << " characters\n";
  cout << total << " characters total\n";
}
