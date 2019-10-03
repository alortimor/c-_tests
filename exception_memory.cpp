#include <iostream>
#include <new>
#include <cstdlib>

using namespace std;

struct Big {
  double stuff[20000];
};

int main() {
  Big * pb;
  try {
    cout << "Attempting to obtain a large block of memory :\n";
    pb = new Big[10000]; // 1,6000,000,000 byte
    cout << "After new memory request:\n";
  }
  catch (bad_alloc & ba) {
    cout << "Caught the exception!\n";
    cout << ba.what() << endl;
    exit(EXIT_FAILURE);
  }
  cout << "Memory successfully allocated.\n";
  pb[0].stuff[0] = 4.0;
  cout << pb[0].stuff[0] << endl;
  delete [] pb;
  return 0;
}
