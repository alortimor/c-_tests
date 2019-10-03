#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <string>

using std::string;

class BankAcc {
  private:
    string clientName;
    long accNumber;
    double currentBalance;

  public:
    BankAcc(const string &customerName, long ac, double initialBalance = 0.0); // default constructor

    virtual ~BankAcc () { }
    void deposit(double amt);
    double balance() const { return currentBalance; }; // static binding

    // Using "virtual" indicates that the function behaves differently in BankAcc as opposed
    // to the same function in BankAccPlus.
    // When referring to either viewAcct or withdraw using a pointer or a reference
    // then the function that is called is based on the pointer or reference type,
    // for example if pointer is BankAcc * b, then BankAcc::withdraw will be called
    // if BankAccPlus & bap, then BankAccPlus::withdraw will be called
    virtual void viewAcct() const; // dynamic binding
    virtual void withdraw(double amt);
};

// BankAccPlus allows for an overdraft facility, default overdraft is £500
class BankAccPlus : public BankAcc {
  private:
    double upperLimit;
    double interestRate;
    double debt;

  public:
    BankAccPlus(const string & customerName
               ,long  ac
               ,double initialBalance = 0.0
               ,double limit = 500     // allow for an overdraft of £500 by default
               ,double rate = 0.075);  // charge 7.5% on overdraft by default

    BankAccPlus(const BankAcc & ba, double limit = 500, double rate = 0.075);
    virtual ~BankAccPlus() { }

    void resetUpperLimit(double limit) { upperLimit = limit; }
    void resetRate(double rate) { interestRate = rate; }
    void resetDebt() { debt = 0.0; }

    virtual void viewAcct() const;
    virtual void withdraw(double amt);
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
