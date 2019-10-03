#include <iostream>

// template function #1
template <class T> T lesser(T a, T b) { return a < b ? a : b; }

// function #2
int lesser(int a, int b) {
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  return a < b ? a : b;
}


int main() {

  int m = 20;
  int n = -30;

  double x = 15.5;
  double y = 25.9;

  std::cout << lesser(m, n) << std::endl; // uses #2
  std::cout << lesser(x, y) << std::endl; // uses #1

  // the angled brackets instruct the compiler to make use of
  // a template function
  std::cout << lesser<>(m, n) << std::endl;    // uses #1 with int

  // the angled brackets with int, i.e. <int>, instruct the compiler
  // to make use of a template function using int for T, otherwise called
  // explicit instatiation
  std::cout << lesser<int>(x, y) << std::endl; // uses #1 with in

  return 0;
}
