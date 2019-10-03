#ifndef STRBAD_H_
#define STRBAD_H_

#include <iostream>
// #include <string>

class StringBad {
  private:
    char * str;
    int len = 0;
    static int num_strings; // must be initialised outside class, not kept in same memory as class
    // if the static were a const integral then an initialisation can occur

  public:
    StringBad(const char *);
    StringBad(const StringBad & s);
    StringBad();
    ~StringBad();
    
    StringBad & operator=(const StringBad & st);
    friend std::ostream & operator<<(std::ostream & os, const StringBad & st);
};

#endif

