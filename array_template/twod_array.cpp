#include <iostream>
#include "array.h"

int main(void) {
  using std::endl;
  using std::cout;

  Array<int, 10> sums;
  Array<double, 10>   aves;
  Array< Array<int, 5>, 10> twod;

  int i, j;
  for (i = 0; i < 10; i++) {
    sums[i] = 0;
    for (j = 0; j < 5; j++) {
      twod[i][j] = (i + 1) * (j + 1);
      sums[i] += twod[i][j];
    }
    aves[i] =(double) sums[i]/10;
  }
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 5; j++) {
      cout.width(2);
      cout << twod[i][j] << ' ';
    }
    cout << ": sum = ";
    cout.width(3);
    cout << sums[i] << ", average = " << aves[i] << endl;
  }

  cout << "Done.\n";
  return 0;
}
