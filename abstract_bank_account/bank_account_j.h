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
	virtual void print(std::ostream & os) const = 0;

  protected:
    struct formatting {
      std::ios_base::fmtflags flag;
      std::streamsize pr;
    };

    const std::string & accHolderName() const { return clientName; }
    formatting setFormat() const;
    void restore(formatting  & f) const;
	
	

  public:
    Abstract_BankAcc(const std::string & s, long ac, double initialBalance = 0.0);
    virtual ~Abstract_BankAcc() { }
    void deposit(double amt);
    virtual void withdraw(double amt) = 0; // pure virtual function
    double getcurrentBalance() const { return currentBalance; }
    void resetBalance(double bal) { currentBalance = bal; };
    string getclientName() const { return clientName; }
    long getaccNumber() const { return accNumber; }

	friend std::ostream & operator<<(std::ostream & os, const Abstract_BankAcc & abc);
};

// standard Bank Account
class BankAcc : public Abstract_BankAcc {
  public:
    BankAcc(const string & customerName, long ac, double initialBalance = 0.0);

    virtual ~BankAcc () { }
    virtual void withdraw(double); // dynamic binding
    virtual void showAcc(BankAcc &) const; // dynamic binding

	//friend std::ostream & operator<<(std::ostream & os, const BankAcc & abc);
private:
	void print(std::ostream & os) const {}
};

// Derived Bank Account, BankAccPlus, allows for an overdraft facility,
// default overdraft is £500
class BankAccPlus : public Abstract_BankAcc {
  private:
    double upperLimit;
    double interestRate;
    double debt;

	void print(std::ostream & os) const;

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
    virtual void showAcc(BankAccPlus &) const; // dynamic binding
    //friend std::ostream & operator<<(std::ostream & os, const BankAccPlus & abc);
};

#endif

/*
If you redefine the signature of a virtual function in a derived class,
it doesn’t just override the base class declaration with the same function signature.
Instead, it hides all base class methods of the same name, regardless of the argument signatures.

for example
class A {
  private:
    int x,y;
    long sum;
  public:
    A(int p_x =0, int p_y =0) : x(p_x), y(p_y) { }
    virtual ~A() { }
    virtual int sum_all(int);
}

class B : public A {
  private:
    int z; // common divisor, use euclidean algorithm
  public:
    B(int p_x=0, int p_y=0, int p_z=0) : A(p_x,p_y), z(p_z)  { }
    virtual ~B() { }
    virtual int sum_all(int, int);
}
In the above case, sum_all is in fact redefined, so:

B a;
a.sum_all(7); // valid
a.sum_all(7,7); //invalid

class A {
  private:
    int x,y;
    long sum;
  public:
    A(int p_x =0, int p_y =0) : x(p_x), y(p_y) { }
    virtual ~A() { }
    virtual A & sum_all(int);
}

class B : public A {
  private:
    int z; // common divisor, use euclidean algorithm
  public:
    B(int p_x=0, int p_y=0, int p_z=0) : A(p_x,p_y), z(p_z)  { }
    virtual ~B() { }
    virtual B & sum_all(int);
}

So, although the return type is different (note - return type can only vary by base/derived class type),
they are only different in so much as an upcast might be necessary,
the arguments to the function however remain the same!

If the base class virtual function is overloaded, then each overloaded function
needs to be specified in the derived class as well.

class A {
  private:
    int x,y;
    long sum;
  public:
    A(int p_x =0, int p_y =0) : x(p_x), y(p_y) { }
    virtual ~A() { }
    virtual int sum_all(int);
    virtual int sum_all(int, int);
}

class B : public A {
  private:
    int z; // common divisor, use euclidean algorithm
  public:
    B(int p_x=0, int p_y=0, int p_z=0) : A(p_x,p_y), z(p_z)  { }
    virtual ~B() { }
    virtual int sum_all(int);
    virtual int sum_all(int, int);
}
If any overloaded virtual, present in the base class, is missing in the derived class, then the
the base class virtual function remains hidden.

 

If no change is needed, then you can use the following notation, no need for virtual
void B::sum_all(int) const {A::sum_all(int);}
 
*/
