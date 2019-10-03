// external.cpp -- external variables
// compile with support.cpp
#include <iostream>
using namespace std;
// external variable
double warming = 0.3; // warming defined

int errors = 20; // external declaration

/* if int errors = 20 is defined in support.cpp then that would
generate an error since it violates the "one def" rule, but if
errors is defined as static int errors = 20, then that would be
accceptable, since the compiler identifies static errors as
internal to support.cpp only, otherwise known as internal linkage
*/

void update(double dt);
void local();

int main() {
  cout << "Global warming is " << warming << " degrees.\n";
  update(0.1);

  cout << "Global warming is " << warming << " degrees.\n"; 
  local();

  cout << "Global warming is " << warming << " degrees.\n";
  return 0;
}
