#include "bank_account.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;

format setFormat();
void restore(format &, precis &);

BankAcc::BankAcc(const string &customerName, long ac, double initialBalance)
       : clientName(customerName), accNumber(ac), currentBalance(initialBalance) { }

void BankAcc::deposit(double amt) {
    if (amt > 0)
      currentBalance += amt;
    else
      cout << "Negative deposit unacceptable" << endl;
}

void BankAcc::viewAcct() const {
  format initialState = setFormat();
  precis prec = cout.precision(2);
  cout << "Client         : " << clientName << endl;
  cout << "Account Number : " << accNumber << endl;
  cout << "Current Balance: £" << currentBalance << endl;
  restore(initialState, prec);
}

void BankAcc::withdraw(double amt) {
  format initialState = setFormat();
  precis prec = cout.precision(2);
  if (amt < 0)
    cout << "Withdraw cannot be negative" << endl;
  else if (amt <= currentBalance)
    currentBalance -= amt;
  else
    cout << "Withdrawal exceeds current balance" << endl;
  restore(initialState, prec);
}

BankAccPlus::BankAccPlus( const string & customerName
                         ,long  ac
                         ,double initialBalance
                         ,double limit      // allow for an overdraft of £500 by default
                         ,double rate) :    // charge 7.5% on overdraft by default
        BankAcc(customerName, ac, initialBalance), upperLimit(limit), interestRate(rate) { }

BankAccPlus::BankAccPlus(const BankAcc & ba, double limit, double rate) :
    BankAcc(ba), upperLimit(limit), interestRate(rate) { }

void BankAccPlus::viewAcct() const {
  format initialState = setFormat();
  precis prec = cout.precision(2);
  BankAcc::viewAcct();
  cout << "Upper Limit     : £" << upperLimit << endl;
  cout << "Outstanding Debt: £" << debt << endl;
  cout << "Interest Rate   : %" << 100 * interestRate << endl;
  restore(initialState, prec);
}

void BankAccPlus::withdraw(double amt) {
  format initialState = setFormat();
  precis prec = cout.precision(2);

  double bal = balance();
  if (amt <= bal)
    BankAcc::withdraw(amt);
  else if (amt <= bal + upperLimit - debt) {
    double overdraft = amt - bal;
    debt += overdraft * (1.0 * interestRate);
    cout << "Bank overdraft : £" << overdraft << endl;
    cout << "Interest charge: £" << overdraft * interestRate << endl;
    deposit(overdraft);
    BankAcc::withdraw(amt);
  }
  else
    cout << "Upper limit exceeded" << endl;

  restore(initialState, prec);

}

format setFormat() {
  return cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}

void restore (format & f, precis & p) {
  cout.setf(f, std::ios_base::floatfield);
  cout.precision(p);
}
