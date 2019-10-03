#ifndef STRBAD_H_
#define STRBAD_H_

#include <iostream>

class String {
  private:
    char * str;
    int len{0};
    static int num_strings;
    static const int CINLIM{80};
  public:
    String(const char *);
    String();
    String(const String & s);
    ~String();
    int length() const { return len; }

    // operator overloaders
    String & operator=(const String &);
    String & operator=(const char *);
    char & operator[](int i);
    const char & operator[](int i) const;

    // overloaded operator friend functions
    friend bool operator<(const String &st1, const String &st2);
    friend bool operator>(const String &st1, const String &st2);
    friend bool operator==(const String &st1, const String &st2);
    friend std::ostream & operator<<(std::ostream & os, const String & st);
    friend std::istream& operator>>(std::istream & is, String & st);

    static int HowMany();

    
};

#endif

