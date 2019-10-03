#include <iostream>
#include "stock00.h"

// use Shift-F9 to build, since a makefile exists

int main() {
  std::ios_base::fmtflags orig = std::cout.setf(std::ios_base::fixed);
  std::streamsize prec = std::cout.precision(3);
  Stock cedar_stock("Sample company", 14, 17.0);
  cedar_stock.aquire("Tech Stock", 20, 12.50);
  cedar_stock.show();
  cedar_stock.buy(15, 18.125);
  cedar_stock.show();
  cedar_stock.sell(400, 20.00);
  cedar_stock.show();
  cedar_stock.buy(300000,40.125);
  cedar_stock.show();
  cedar_stock.sell(300000,0.125);
  cedar_stock.show();
  std::cout.precision(prec);
  std::cout.setf(orig, std::ios_base::floatfield);
  return 0;
}
