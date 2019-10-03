#include <iostream>

template <typename T> // or class T
void Swap(T &, T &);

struct job {
  char name[40];
  double salary;
  int floor;
};

// explicit specialisation
template <> void Swap<job>(job &, job &);
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

  Swap(sue, terry);
  std::cout << "After job swapping:\n";
  Show(sue);
  Show(terry);
  
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
template <typename T> // or class T
void Swap (T &a, T &b) {
  T temp;
  temp = a;
  a = b;
  b = temp;
}

void Show(job &j) {
  std::cout << j.name << ": $" << j.salary << " on floor " << j.floor << std::endl;
}
