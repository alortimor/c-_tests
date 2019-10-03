#include "bank_account.h"
#include <iostream>

const int CUSTOMERS = 4;

void test_view(BankAccPlus &);

int main() {

  using std::cout;
  using std::cin;
  using std::endl;

  BankAcc db = BankAcc("Paul Hogan", 10000, 1000);
  // test_view(db);

  BankAcc * p_customers[CUSTOMERS]; // using pointers allows for holding a BankAcc or a BankAccPlus type.
  std::string name;

  long accNo;
  double bal;
  char accType;

  for (int i = 0; i < CUSTOMERS; i++) {
    cout << "Customer name  : ";
    cin >> name;
    cout << "Account Number : ";
    cin >> accNo;
    cout << "Initial Deposit: ";
    cin >> bal;

    cout << "\n1 = Bank Account 2 = Bank Account Plus: ";
    while (cin >> accType && (accType != '1' && accType != '2'))
      cout << "Enter 1 or 2: ";

    if (accType == '1')
      p_customers[i] = new BankAcc(name, accNo, bal);
    else {
      double xLimit, xRate;
      cout << "Enter upper limit  : £";
      cin >> xLimit;
      cout << "Enter interest rate: ";
      cin >> xRate;
      p_customers[i] = new BankAccPlus(name, accNo, bal, xLimit, xRate);
    }
    while (cin.get() != '\n')
      continue;
  }

  cout << endl;

  for (int i = 0; i < CUSTOMERS; i++) // free memory
    delete p_customers[i];

  cout << "Done.\n";
  return 0;
}

void test_view(BankAccPlus & rb) {
  rb.viewAcct();
}


/*

void testa(BankAcc & rb); // uses rb.showAcc()
void testb(BankAcc * pb); // uses pb->showAcc()
void testc(BankAcc b);    // uses b.showAcc()

int main() {
  BankAcc x("Peter Koukoulis", 123432, 10000.0);
  BankAccPlus y("Paul Simon", 232313, 12345.0);

  testa(x); // uses BankAcc::showAcc()
  testa(y); // uses BankAccPlus::showAcc()
  
  testb(x); // uses BankAcc::showAcc()
  testb(y); // uses BankAccPlus::showAcc()

  testc(x); // uses BankAcc::showAcc()
  testc(y); // uses BankAcc::showAcc()

  return 0;
}

..
..
 
*/
