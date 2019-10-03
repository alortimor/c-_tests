#include "bank_account.h"
#include <iostream>

int main() {

  using std::cout;
  using std::endl;

  BankAcc huge("Peter Koukoulis", 287643754, 4000.0);
  BankAccPlus massive("Felix Larring", 349765549, 50000.0);
  cout << huge;
  cout << massive;

  huge.deposit(200);
  massive.deposit(20000);
  cout << endl;
  cout << endl;

  cout << huge;
  cout << massive;

  huge.withdraw(4800);
  massive.withdraw(4800);

  cout << huge;
  cout << massive;

  cout << "Done.\n";
  return 0;
}
