#include <iostream>
double hmean(double a, double b);

int main() {
  using namespace std;

  double x, y,z;
  
  cout << "Enter 2 numbers: ";
  while (cin >> x >> y) {
    try {
      z = hmean(x, y);
    }
    catch (const char * s) {
      cout << s << endl;
      cout << "Enter a new pair of numbers: ";
      continue;
    }
    cout << "Harmonic mean of " << x << ", " << y << " = " << z << endl;
    cout << "Enter next set of numbers <q to quit>: ";
  }
  return 0;
}

double hmean(double a, double b) {
  if (a == -b)
    throw "bad hmean() arguments: a = -b not allowed";
  return 2.0 * a * b / (a + b);
}
