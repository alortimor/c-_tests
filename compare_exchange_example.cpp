#include <atomic>
#include <iostream>

/*

On older machines the store, using compare_exchange_weak(),  might not be successful
even if the original value was equal to the expected value, in which case the value of the variable is
unchanged and the return value of compare_exchange_weak() is false. Known as a spurious fail.

*/

int main() {


  return 0;
  
}
