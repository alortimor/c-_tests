#include <iostream>

void swapr(int &, int &);
void swapp(int *, int *);
void swapv(int, int);

int main() {
  int wallet1 = 300;
  int wallet2 = 350;

  std::cout << "wallet1 = $" << wallet1;
  std::cout << " wallet2 = $" << wallet2 << std::endl;

  std::cout << "Using references to swap contents:\n";
  swapr(wallet1, wallet2); // pass variables
  std::cout << "wallet1 = $" << wallet1;
  std::cout << " wallet2 = $" << wallet2 << std::endl;

  swapp(&wallet1, &wallet2); // pass addresses
  std::cout << "wallet1 = $" << wallet1;
  std::cout << " wallet2 = $" << wallet2 << std::endl;
   
  swapp(&wallet1, &wallet2); // pass addresses
  std::cout << "wallet1 = $" << wallet1;
  std::cout << " wallet2 = $" << wallet2 << std::endl;

  return 0;
}

void swapr(int & a, int & b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
}

void swapp(int * p, int * q) {
  int temp;
  temp = *p;
  *p = *q;
  *q = temp;
}

void swapv(int a, int b) {
  int temp;

  temp = a;
  a = b;
  b = temp;
}
