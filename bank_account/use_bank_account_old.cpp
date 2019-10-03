#include "bank_account.h"
#include <iostream>

int main() {

  using std::cout;
  using std::endl;

  BankAcc huge("Peter Koukoulis", 287643754, 4000.0);
  BankAccPlus massive("Felix Larring", 349765549, 50000.0);
  huge.viewAcct();
  massive.viewAcct();


  huge.deposit(200);
  massive.deposit(20000);
  
  cout << endl;
  cout << endl;

  huge.viewAcct();
  massive.viewAcct();

  huge.withdraw(4800);
  massive.withdraw(4800);

  return 0;
}
