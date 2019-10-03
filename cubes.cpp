#include <iostream>
#include <cmath>

double cube(double);
double refcube(double &);
double c_refcube(const double &);

int main() {
  double x = 3.0;

  std::cout << cube(x);
  std::cout << " = cube of " << x << std::endl;
  std::cout << refcube(x);
  std::cout << " = cube of " << x << std::endl;
  x = 3;
  std::cout << c_refcube(x);
  std::cout << " = cube of " << x << std::endl;

  /*
  // double z = refcube(x + 3.0); // this generates an error, but in earlier versions of c++
                                  // expressions to reference parameters generted warnings
                                  // the expression would then be converted to a temporary variable
  */

  double z = 1.0;
  std::cout << c_refcube(x + z); // expression x+z generates temp variable, which is assigned to ra
  std::cout << " = cube of " << x + z << std::endl;

  double &&rref = std::sqrt(36.0); // variables prefixed with && are called rvalue variables
  std::cout << rref << std::endl;

  double j = 25.0;
  
  double &&jref = 2.0 * j + 18.5; // double &jref = 2.0*j+18,5; // this will cause error, hence prefix with &&
  std::cout << jref << std::endl;
  
  return 0;
}

double cube (double a) {
  a *= a * a;
  return a;
}

double refcube (double &ra) {
  ra *= ra * ra;
  return ra;
}

double c_refcube(const double &ra) {
  return ra * ra * ra; // cannot modify ra, so simply return the cube without modifying
}
