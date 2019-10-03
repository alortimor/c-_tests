#ifndef TIME0_H_
#define TIME0_H_

#include <iostream>

class Time {
  friend Time operator+(const Time &, const int m);
  friend Time operator-(const Time &, const int m);
  friend Time operator+(const Time &, const Time &);
  friend Time operator-(const Time &, const Time &);
  //template <typename T> friend Time operator-(const Time &, const T &);
  //template <typename T> friend Time operator+(const Time &, const T &);
  friend Time& operator*(Time &, double &&);
  friend std::ostream & operator<<(std::ostream &o, const Time & t);
  private:
    int minutes;

  public:
    Time(int m = 0);
    void Reset(int m = 0);
    Time& operator+=(const Time &);
};

#endif

