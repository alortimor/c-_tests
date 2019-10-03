#include <iostream>
#include <string>

const int SIZE = 5;
using namespace std;
void display(const string [], int);

int main()
{
  string list[SIZE];
  std::cout << "Enter your " << SIZE << " favourite astronomical sights:\n";
  for (int i = 0; i < SIZE; i++) {
    std::cout << i + 1 << ": ";
    std::getline(std::cin, list[i]);
  }
  std::cout << "Your list:\n";
  display(list, SIZE);
	return 0;
}

void display(const string sa[], int n) {
  for (int i = 0; i < n; i++) {
    std::cout << i + 1 << ": " << sa[i] << std::endl;
  }
}
