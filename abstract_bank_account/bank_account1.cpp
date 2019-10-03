#include "bank_account.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ios_base;

Abstract_BankAcc::Abstract_BankAcc(const std::string & s, long ac, double initialBalance) :
  clientName(s), accNumber(ac), currentBalance(initialBalance) { }

BankAcc::BankAcc(const string &customerName, long ac, double initialBalance) :
  Abstract_BankAcc(customerName, ac, initialBalance) { }

void Abstract_BankAcc::deposit(double amt) {
    if (amt > 0)
      currentBalance += amt;
    else
      cout << "Negative deposit unacceptable" << endl;
}

std::ostream & operator<<(std::ostream & os, const Abstract_BankAcc & abc) {
  Abstract_BankAcc::formatting initialState = abc.setFormat();
  os << "Client          : "  << abc.clientName     << endl
     << "Account Number  : "  << abc.accNumber      << endl
     << "Current Balance : £" << abc.currentBalance << endl;
  abc.print(os);
  abc.restore(initialState);
  return os;
}

void BankAccPlus::print(std::ostream & os) const {
  os  << "Upper Limit     : £" << upperLimit << endl
      << "Outstanding Debt: £" << debt << endl
      << "Interest Rate   : %" << 100 * interestRate << endl;
}

void BankAcc::withdraw(double amt) {
  Abstract_BankAcc::formatting initialState = setFormat();
  double bal = getcurrentBalance();
  if (amt < 0)
    cout << "Withdraw cannot be negative" << endl;
  else if (amt <= bal) {
    bal -= amt;
    resetBalance(bal);
  }
  else
    cout << "Withdrawal exceeds current balance" << endl;
  restore(initialState);
}

BankAccPlus::BankAccPlus( const string & customerName
                         ,long  ac
                         ,double initialBalance
                         ,double limit      // allow for an overdraft of £500 by default
                         ,double rate) :    // charge 7.5% on overdraft by default
        Abstract_BankAcc(customerName, ac, initialBalance), upperLimit(limit), interestRate(rate) { }

BankAccPlus::BankAccPlus(const BankAcc & ba, double limit, double rate) :
    Abstract_BankAcc(ba), upperLimit(limit), interestRate(rate) { }

void BankAccPlus::withdraw(double amt) {
  formatting initialState = setFormat();

  double bal = getcurrentBalance();
  if (amt <= bal) {
    bal -= amt;
    resetBalance(bal);
  }
  else if (amt <= bal + upperLimit - debt) {
    double overdraft = amt - bal;
    debt += overdraft * (1.0 * interestRate);
    cout << "Bank overdraft : £" << overdraft << endl;
    cout << "Interest charge: £" << overdraft * interestRate << endl;
    deposit(overdraft);
    bal -= amt;
    resetBalance(bal);
  }
  else
    cout << "Upper limit exceeded" << endl;

  restore(initialState);
}

void Abstract_BankAcc::restore(formatting  & f) const {
  cout.setf(f.flag, ios_base::floatfield);
  cout.precision(f.pr);
}

Abstract_BankAcc::formatting Abstract_BankAcc::setFormat() const {
  formatting f;
  f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
  f.pr   = cout.precision(2);
  return f;
}
