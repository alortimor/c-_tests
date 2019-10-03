#include <iostream>
#include <fstream>
#include <cstdlib>

using std::ofstream;
using std::ostream;
using std::cout;
using std::cin;
using std::ios_base;

void file_it(ostream &, double, const double [], int);
const int LIMIT = 5;

int main() {

  ofstream fout;

  const char * fn = "ep-data.txt";
  fout.open(fn);

  if (!fout.is_open()) {
    cout << "Cannot open " << fn << ". Goodbye.\n";
    exit(EXIT_FAILURE);
  }

  double objective;
  cout << "Enter focal length of telescope objective in mm: ";
  cin >> objective;
  double eps[LIMIT];

  cout << "Enter focal lengths in mm of " << LIMIT << " eyepieces:\n";
  for (int i = 0; i < LIMIT; i++) {
    cout << "Eypiece #" << i + 1 << ": ";
    cin >> eps[i];
  }
  file_it(fout, objective, eps, LIMIT);
  file_it(cout, objective, eps, LIMIT);
  cout << "Done.\n";

  return 0;
}

void file_it(ostream & os, double fo, const double fe[], int n) {
  using std::endl;
  ios_base::fmtflags initial;
  initial = os.setf(ios_base::fixed); // save initial formatting state
  os.precision(0);
  os << "\nFocal length of objective: " << fo << " mm\n";
  os.setf(std::ios::showpoint);
  os.precision(1);
  os.width(12);
  os << "f.1. eyepiece";
  os.width(15);
  os << "maginification" << endl;
  for (int i = 0; i < n; i++) {
    os.width(12);
    os << fe[i];
    os.width(15);
    os << int (fo/fe[i] + 0.5) << endl;
  }
  os.setf(initial);
}
