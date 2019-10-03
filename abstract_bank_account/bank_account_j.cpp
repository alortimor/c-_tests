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


/*std::ostream & operator<<(std::ostream & os, const BankAcc & abc) {
  Abstract_BankAcc::formatting initialState = abc.setFormat();
  os << "Client         : " << abc.clientName << endl
     << "Account Number : " << abc.accNumber << endl
     << "Current Balance: £" << abc.currentBalance << endl;
  abc.restore(initialState, prec);
  return os;
}

std::ostream & operator<<(std::ostream & os, const BankAccPlus & abc) {
Abstract_BankAcc::formatting initialState = abc.setFormat();

// print what is already present for the standard Bank Account and then display
// the additional attributes for the Bank Account Plus
os  << "Client          : " << abc.clientName << endl
<< "Account Number  : " << abc.accNumber << endl
<< "Current Balance : £" << abc.currentBalance << endl
<< "Upper Limit     : £" << abc.upperLimit << endl
<< "Outstanding Debt: £" << abc.debt << endl
<< "Interest Rate   : %" << 100 * abc.interestRate << endl;
abc.restore(initialState);
return os;
}
*/

std::ostream & operator<<(std::ostream & os, const Abstract_BankAcc & abc) {
  Abstract_BankAcc::formatting initialState = abc.setFormat();

  // print what is already present for the standard Bank Account and then display
  // the additional attributes for the Bank Account Plus
  os << "Client          : " << abc.clientName << endl
	  << "Account Number  : " << abc.accNumber << endl
	  << "Current Balance : £" << abc.currentBalance << endl;
  abc.print(os);
      /*<< "Upper Limit     : £" << abc.upperLimit << endl
      << "Outstanding Debt: £" << abc.debt << endl
      << "Interest Rate   : %" << 100 * abc.interestRate << endl;*/
  abc.restore(initialState);
  return os;
}

void BankAccPlus::print(std::ostream & os) const
{
	os << "Upper Limit     : £" << upperLimit << endl
		<< "Outstanding Debt: £" << debt << endl
		<< "Interest Rate   : %" << 100 * interestRate << endl;
}

void BankAcc::showAcc(BankAcc & ba) const {
  formatting initialState = ba.setFormat();
  cout << endl;
  cout << "Client          : " << ba.getclientName() << endl
       << "Account Number  : " << ba.getaccNumber() << endl;
       // << "Current Balance : £" << ba.getcurrentBalance() << endl;
  ba.restore(initialState);
}

void BankAccPlus::showAcc(BankAccPlus & ba) const {
  formatting initialState = ba.setFormat();
  /*
  cout << (BankAcc)this->showAcc() <<
       << "Upper Limit     : £" << upperLimit << endl
       << "Outstanding Debt: £" << debt << endl
       << "Interest Rate   : %" << 100 * interestRate << endl;
  */
  /*
  cout << "Client          : "  << ba.getclientName() << endl
       << "Account Number  : "  << ba.getaccNumber() << endl
       << "Current Balance : £" << ba.getcurrentBalance() << endl
       << "Upper Limit     : £" << ba.upperLimit << endl
       << "Outstanding Debt: £" << ba.debt << endl
       << "Interest Rate   : %" << 100 * ba.interestRate << endl; */
  cout << endl;
  ba.restore(initialState);
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
  f.pr = cout.precision(3); // f.pr);
  return f;
}
