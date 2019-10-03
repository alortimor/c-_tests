#include <iostream>
#include "stonewt.h"

int main() {

  Stonewt myCat; // create object is valid;
  // mycat = 19.6; // would be invalid if explicit were used
  myCat = Stonewt(19.6); // valid, explicit conversion
  myCat = (Stonewt) 19.6; // valid, old style explicit typecast

  /* Implicit
    constructor performs a type conversion from argument type to clss type
    Examples: when you assign double to a Stonewt object
              when you initialise a Stonewt object to a type double
              when you pass a type double to a function that expects a Stonewt argument
              when a function declared as returning a Stonewt value, returns a double
  */

  /* if you had the following code:
   Stonewt s1(10000);
   s1 = 20000;

   and if you had the following declerations
   Stonewt(double)
   Stonewt(long)

   the compiler would generate an error, since the code is ambigous, since it would not know
   which constructor to call.
  */

  Stonewt w(285.8);
  int host = w; // invalid if there is no operator int
  // Stonewt e(243);
  // double gyro =  e; // invalid if tere is no operator double
  std::cout << host << std::endl;
  
  return 0;
}
