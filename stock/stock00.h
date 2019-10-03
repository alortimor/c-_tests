#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>

class Stock {
  // private is the default access control for classes
  // so is therefore not necessary to include the "private" keyword
  private:
    std::string company;
    long shares;
  
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val; }

  public:
    Stock();
    Stock(const std::string & co, long n, double pr); // constructor
    ~Stock();
    void aquire(const std::string & co, long n, double pn);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif
