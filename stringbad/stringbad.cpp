#include <iostream>
#include <cstring>
#include "stringbad.h"

int StringBad::num_strings = 0;

StringBad::StringBad(const char * s) {
  len = std::strlen(s);
  str = new char[len + 1];
  std::strcpy(str, s);
  num_strings++;
  std::cout << "\n" << num_strings << ": \"" << str << "\" object created\n"; 
}

StringBad::StringBad() {
  len = 4;
  str = new char[4];
  std::strcpy(str, "C++");
  num_strings++;
  std::cout << "\n" << num_strings << ": \"" << str << "\" default object created\n"; 
}

StringBad::~StringBad() {
  std::cout << "\n" << "\"" << str << "\" << object deleted, ";
  --num_strings;
  std::cout << "\n" << num_strings << " left\n";
  delete [] str;
}

// Always create an explicit copy constructor and perform
// a deep copy when pointers exist in a class.
// Not doing so will result in runtime failures since multiple pointers
// will end up pointing to the same adresses
StringBad::StringBad(const StringBad & s) {
  num_strings++;
  len = s.len;
  str = new char [len + 1];
  std::strcpy(str, s.str);  
}

std::ostream & operator<<(std::ostream & os, const StringBad & st) {
  os << st.str;
  return os;
}

StringBad & StringBad::operator=(const StringBad & st) {
  if (this == &st)   // in case assigment occurs to self
    return *this;

  delete [] str;
  len = st.len;
  str = new char [len + 1];
  std::strcpy(str, st.str);
  return *this;
}
