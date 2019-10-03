#ifndef ABSTRACT_BA_H
#define ABSTRACT_BA_H

#include <string>
#include <iostream>

using std::string;

class Abstract_BankAcc {
  private:
    string clientName;
    long accNumber;
    double currentBalance;
  protected:
    struct formatting {
      std::ios_base::fmtflags flag;
      std::streamsize pr;
    };

    const std::string & accHolderName() const { return clientName; }
    string getclientName() const { return clientName; }
    long getaccNumber() const { return accNumber; }
    double getcurrentBalance() const { return currentBalance; }
    formatting setFormat() const;
    void restore(formatting  & f) const;

  public:
    Abstract_BankAcc(const std::string & s, long ac, double initialBalance = 0.0);
    virtual ~Abstract_BankAcc() { }
    void deposit(double amt);
    virtual void withdraw(double amt) = 0; // pure virtual function
    void resetBalance(double bal) { currentBalance = bal; };

    friend std::ostream & operator<<(std::ostream & os, const Abstract_BankAcc & abc);
};

// standard Bank Account
class BankAcc : public Abstract_BankAcc {
  public:
    BankAcc(const string & customerName, long ac, double initialBalance = 0.0);
    virtual ~BankAcc () { }
    virtual void withdraw(double); // dynamic binding
};

// Derived Bank Account, BankAccPlus, allows for an overdraft facility,
// default overdraft is £500
class BankAccPlus : public Abstract_BankAcc {
  private:
    double upperLimit;
    double interestRate;
    double debt;

  public:
    BankAccPlus(const string & customerName
               ,long   ac
               ,double initialBalance = 0.0
               ,double limit = 500     // allow for an overdraft of £500 by default
               ,double rate = 0.075);  // charge 7.5% on overdraft by default

    BankAccPlus(const BankAcc & ba, double limit = 500, double rate = 0.075);
    virtual ~BankAccPlus() { }

    void resetUpperLimit(double limit) { upperLimit = limit; }
    void resetRate(double rate) { interestRate = rate; }
    void resetDebt() { debt = 0.0; }

    virtual void withdraw(double); // dynamic binding
    friend std::ostream & operator<<(std::ostream & os, const BankAccPlus & abc);
};

#endif

/*
when both the base class and the derived class use dynamic memory allocation,
the 1. derived-class destructor
    2. copy constructor
    3. assignment operator
Must all use base-class counterparts.
This requirement is managed 3 different ways.
    1. destructor  = done automatically.
    2. constructor = accomplished by calling base-class copy constructor in member initialization list
                    If no call to a base-class copy occurs then default constructor is invoked automatically
    3. assignment operator, it is accomplished by using the scope-resolution operator in an
       explicit call of the base-class assignment operator.
*/

