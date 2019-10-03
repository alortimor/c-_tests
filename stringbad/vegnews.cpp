#include <iostream>
using std::cout;
using std::endl;
#include "stringbad.h"

void callme1(StringBad &);
void callme2(StringBad);

int main() {
  {
    cout << "Starting an inner block.\n";
    StringBad headline1("Celery Stalks at Midnight");
    StringBad headline2("Lettuce Prey");
    StringBad sports("Spinach Leaves Bowl for Dollars");
    cout << "Headline1: " << headline1 << endl;
    cout << "Headline2: " << headline2 << endl;
    cout << "sports: : " << sports << endl;
    callme1(headline1);
    cout << "Headline1: " << headline1 << endl;
    callme2(headline2);
    cout << "Headline2: " << headline2 << endl;
    cout << "Initialise one object to another:\n";
    StringBad sailor = sports;
    cout << "sailor: " << sailor << endl;
    cout << "Assign one object to another:\n";
    StringBad knot;
    knot = headline1;
    cout << "knot: " << knot << endl;
    cout << "Exiting the block.\n";
  }
  return 0;
}
void callme1(StringBad & rsb) {
  cout << "String passed by reference: ";
  cout << "   \"" << rsb << "\"\n";
}
void callme2(StringBad sb) {
  cout << "String passed by value: ";
  cout << "   \"" << sb << "\"\n";
}

/*

char words[15] = "bad idea";
char * p1 = words;
char * p2 = new chr;
char * p3;
delete [] p1; // undefined !!!!
delete [] p2; // undefined !!!!
delete [] p3; // undefined !!!!
*

therefore always create pointer strings as:
str = new char[1]; 

*/
