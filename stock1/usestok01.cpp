#include <iostream>
#include "stock00.h"

// use Shift-F9 to build, since a makefile exists

int main() {
  std::ios_base::fmtflags orig = std::cout.setf(std::ios_base::fixed);
  std::streamsize prec = std::cout.precision(3);
  {
    using std::cout;
    cout << "Using contructors to create new objects\n";
    Stock stock1("Nano", 12, 20.0); // #1
    stock1.show();
    
    Stock stock2 = Stock("Buffalo", 2, 2.0);
    stock1.show();                  // #2

    cout << "Assigning stock1 to stock2:\n";
    stock2 = stock1;
    cout << "Listing stock1 and stock2:\n";
    stock1.show();
    stock2.show();

    cout << "Using a constructor to reset an object\n";
    stock1 = Stock("Nifty", 10, 50.0);
    cout << "Revised Stock1:\n";
    stock1.show();
    cout << "Done.\n";

    const int size {4};

    // enumerations
    // if using the a symbolic constant then sizing defined elsewhere in the
    // class will may clash with the sizing already defined. For example "small"
    // might defined alredy in another enumerator.
    // In order to prevent the conflict the "class" prefix

    // read up on enumaration scope on page 550
  
    enum class meal {small, medium, large}; // prefix class. If classs is ommitted an error is generated
    enum class sizing {small, medium, large}; // prefix class
  
    Stock stocks[size] = {
        Stock("Nanosmart", 12, 20.0)
       ,Stock("Obelisks", 130, 3.25)
       ,Stock("Shipping", 60, 6.5)
       ,Stock("Outdoor", 32, 1.9)
    };

    const Stock * top = stocks;

    for (int i = 0; i < size; i++)
      stocks[i].show();

    for (int i = 0; i < size; i++)
      top = &top->topval(stocks[i]);

    std::cout << "\nMost valuable Stock:\n";
    top->show(); // show must be defined as "void show() const {}" for compile to succeed
  }
  
  std::cout.precision(prec);
  std::cout.setf(orig, std::ios_base::floatfield);
  return 0;
}
