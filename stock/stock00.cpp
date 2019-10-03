#include <iostream>
#include "stock00.h"

Stock::Stock() {
  std::cout << "Default constructor called.\n";
  company = "no name";
  shares = 0;
  share_val = 0.0;
  total_val = 0.0;  
}

Stock::Stock(const std::string & co, long n=0, double pr=0.0) {
  std::cout << "Constructor using " << co << " called\n";
  company = co;
  if (n < 0) {
    std::cerr << "Number cannot be negative; "
              << company << " shares set to 0.\n";
  shares = 0;
  }
  else
    shares = n;

  share_val = pr;
  set_tot();
}

Stock::~Stock() {
  std::cout << "Bye, " << company << "!\n";
}

void Stock::aquire(const std::string & co, long n, double pr) {
  company = co;
  if (n < 0) {
    std::cout << "Number of shares cannot be negative; "
              << company << " shares set to 0.\n";
    shares = 0;
  }
  else
    shares = n;

  share_val = pr;
  set_tot();
}

void Stock::buy(long num, double price) {
  if (num < 0)
    std::cout << "Number cannot be negative. Transaction aborted";
  else {
    shares += num;
    share_val = price;
    set_tot();
  }
}

void Stock::sell(long num, double price) {
  if (num < 0)
    std::cout << "Number of shares purchased cannot negative. Transaction aborted\n";
  else if (num > shares)
    std::cout << "Cannot sell more than existing holding. Transaction aborted\n";
  else {
    shares -= num;
    share_val = price;
    set_tot();
  }
}

void Stock::update(double price) {
  share_val = price;
  set_tot();
}

void Stock::show() {
  using std::cout;
  using std::ios_base;

  ios_base::fmtflags orig = cout.setf(ios_base::fixed, ios_base::floatfield);
  std::streamsize prec = cout.precision(3);
  
  cout << "\nCompany: " << company
       << " Shares: " << shares << '\n';
  cout << " Price: $" << share_val;
  
  cout << " Total Worth: $" << total_val << '\n';

  cout.setf(orig, ios_base::floatfield);
  cout.precision(prec);
}
