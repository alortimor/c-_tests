#include <iostream>
#include <cstring>
#include "string.h"

using std::cin;
using std::cout;

int String::num_strings = 0;
int String::HowMany() { return num_strings; }

// explicit pointer of type char constructor
String::String(const char * s) {
  len = std::strlen(s);
  str = new char[len + 1];
  std::strcpy(str, s);
  num_strings++;
}

// Default constructor
String::String() {
  len = 4;
  str = new char[1]; // use char[1] instead of char, since delete uses []
  str[0] = '\0';
  num_strings++;
}

// Destructor
String::~String() {
  --num_strings;
  // always pair new [] with delete [] and new with delete, do not mix
  delete [] str;
}

// copy constructor
String::String(const String & s) {
  num_strings++;
  len = s.len;
  str = new char [s.len + 1]; // when initialising in c++ you can use nullptr.
                            // Using nullptr allows for either delete or delete [] to be used
  std::strcpy(str, s.str);
}

std::ostream & operator<<(std::ostream & os, const String & st) {
  os << st.str;
  return os;
}

std::istream & operator>>(std::istream & is, String & st) {
  char temp[String::CINLIM];
  is.get(temp, String::CINLIM);
  if (is)
    st = temp;
  while (is && is.get() != '\n')
    continue;
  return is;
}

String & String::operator=(const String & st) {
  if (this == &st)   // in case assigment occurs to self
    return *this;

  delete [] str;
  len = st.len;
  str = new char [len + 1];
  std::strcpy(str, st.str);
  return *this;
}

// explicit operator= for c style strings
String & String::operator=(const char * s) {
  delete [] str;
  len = std::strlen(s);
  str = new char [len + 1];
  std::strcpy(str, s);
  return *this;
}

char & String::operator[](int i) { return str[i]; }
const char & String::operator[](int i) const { return str[i]; }

bool operator==(const String &st1, const String &st2) {
  return (std::strcmp(st1.str, st2.str) == 0);
}

bool operator<(const String &st1, const String &st2) {
  return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String &st1, const String &st2) {
  return st2 < st1;
}
