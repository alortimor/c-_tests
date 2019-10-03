#include <iostream>

template <typename T> // or class T
void Swap(T &, T &);

template <typename T> // or class T
void Swap(T *, T *, int);
void Show(int []);
const int Lim = 8;


int main() {

  int i = 10;
  int j = 20;
  std::cout << "i, j = " << i << ", " << j << ".\n";
  std::cout << "Using compiler-generated int swapper:\n";
  Swap(i, j);
  std::cout << "Now i, j = " << i << ", " << j << ".\n";

  int d1[Lim] = {0,7,0,4,1,7,7,6};
  int d2[Lim] = {0,7,2,0,1,9,6,9};

  std::cout << "Original arrays:\n";
  Show(d1);
  Show(d2);
  Swap(d1, d2, Lim);
  std::cout << "Swapped arrays:\n";
  Show(d1);
  Show(d2);
  
  
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

template <typename T> // or class T
void Swap (T a[], T b[], int n) {
  T temp;
  for (int i = 0; i < n; i++) {
    temp = a[i];
    a[i] = b[i];
    b[i] = temp;
  }
}

void Show(int a[]) {
  std::cout << a[0] << a[1] << "/";
  std::cout << a[2] << a[3] << "/";
  for (int i = 4; i < Lim; i++)
    std::cout << a[i];

  std::cout << std::endl;
}
