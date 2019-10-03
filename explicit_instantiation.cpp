#include <iostream>

template <class T> // template prototype
void Swap(T &, T &);
// explicit instantiation of the above Swap prototype
template void Swap<char>(char &, char &);

struct job {
  char name[40];
  double salary;
  int floor;
};

// explicit specialisation
template <> void Swap<job>(job &, job &); // to identify an explicit specialisation
                                          // one has to prefix void Swap with <>.
                                          // Also, the difference between
                                                // - template <> void
                                                // - template void
                                          // is that the code for the former has to be
                                          // explicitly written.

void Show(job &);

int main() {
  std::cout.precision(2);
  std::cout.setf(std::ios::fixed, std::ios::floatfield);

  int i = 10;
  int j = 20;
  std::cout << "i, j = " << i << ", " << j << ".\n";
  std::cout << "Using compiler-generated int swapper:\n";
  Swap(i, j);
  std::cout << "Now i, j = " << i << ", " << j << ".\n";

  job sue = {"Susan Thompson", 73000.60, 7};
  job terry = {"Terry Goodyear", 78060.72, 9};
  std::cout << "Before job swapping:\n";
  Show(sue);
  Show(terry);

  Swap(sue, terry); // use explicit specialisation for job

  std::cout << "After job swapping:\n";
  Show(sue);
  Show(terry);

  short a=-99, b=99;
  std::cout << "Before swap of short variables" << std::endl;
  std::cout << "a, b = " << a << ", " << b << ".\n";
  Swap(a, b); // implicit template instantiation
  std::cout << "After swap of short variables" << std::endl;
  std::cout << "a, b = " << a << ", " << b << ".\n";

  char c1='a', c2='z';
  std::cout << "Before swap of char variables" << std::endl;
  std::cout << "c1, c2 = " << c1 << ", " << c2 << ".\n";
  Swap(c1, c2); // explicit template instatiation
  std::cout << "After swap of char variables" << std::endl;
  std::cout << "c1, c2 = " << c1 << ", " << c2 << ".\n";
 
  return 0;
}

// this is referred to to as a function template specialisation
// a specialisation template overides a a non-specialised template
// a non-template function overides any kind of template function
template <> void Swap<job>(job &j1, job &j2) {
  double t1;
  int t2;
  t1 = j1.salary;
  j1.salary = j2.salary;
  j2.salary = t1;
  t2 = j1.floor;
  j1.floor = j2.floor;
  j2.floor = t2;
}

// function template definition
template <class T> // or class T
void Swap (T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

void Show(job &j) {
  std::cout << j.name << ": $" << j.salary << " on floor " << j.floor << std::endl;
}
