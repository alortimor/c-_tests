#include <boost/signals2/signal.hpp>
#include <iostream>

void print_args(float x, float y) {
  std::cout << "The arguments are " << x << " and " << y << std::endl;
}

void print_sum(float x, float y) {
  std::cout << "The sum is " << x + y << std::endl;
}

void print_product(float x, float y) {
  std::cout << "The product is " << x * y << std::endl;
}

void print_difference(float x, float y) {
  std::cout << "The difference is " << x - y << std::endl;
}

void print_quotient(float x, float y) {
  std::cout << "The quotient is " << x / y << std::endl;
}

/*
 A "slot"  is a function or a structure or any object to which the signal is associated with.
 print_sum, print_product, print_difference and print_quotient are all "slots".
 
 * 
*/

int main () {
 
  boost::signals2::signal<void (float, float)> sig;

  
  sig.connect(&print_args);
  sig.connect(&print_sum);
  sig.connect(&print_product);
  sig.connect(&print_difference);
  sig.connect(&print_quotient);

  sig(5., 3.);
  
  return 0;
}
