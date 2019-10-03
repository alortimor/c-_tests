#include <iostream>
#include "person.h"
#include <string>

Person::Person(const std::string & ln, const char * fn) {
  lname = ln;
  for (int i = 0; i <= LIMIT; i++)
    fname[i] = *(fn+i);
};

Person::~Person() {};

// the following methods display lname and fname
void Person::Show() const {
  std::cout << "Hello " << fname << " " << lname << std::endl;
}

// firstname lastname format
void Person::FormalShow() const { // lastname, firstname format
  std::cout << lname << ", " << fname << std::endl;
};
