#include <iostream>

template <typename T> // or class T
void Swap(T &a, T &b);

int main() {

  int i = 10;
  int j = 20;
  std::cout << "i, j = " << i << ", " << j << ".\n";
  std::cout << "Using compiler-generated int swapper:\n";
  Swap(i, j);
  std::cout << "Now i, j = " << i << ", " << j << ".\n";

  double x = 24.5;
  double y = 81.7;
  std::cout << "x, y = " << x << ", " << y << ".\n";
  std::cout << "Using compiler-generated double swapper:\n";
  Swap(x, y); // generates void Swap (double &, double &);
  std::cout << "Now x, y = " << x << ", " << y << ".\n";

  return 0;
}

// function template definition
template <typename T> // or class T
void Swap (T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

