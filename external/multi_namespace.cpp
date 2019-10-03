#include <iostream>
using namespace std;
void other();
namespace n1 {
  int x = 1;
}

namespace n2 {
  int x = 2;
}

int main() {
  using namespace n1;
  cout << x << endl;
  {
    int x = 4;
    cout << x << ", " << n1::x << ", " << n2::x << endl;
  }

  using n2::x;
  cout << x << endl;
  other();
  return 0;
}

void other() {
  using namespace n2;
  cout << x << endl;
  {
    int x = 4;
    cout << x << ", " << n1::x << ", " << n2::x << endl;  
  }
  using n2::x;
  cout << x << endl;
}
