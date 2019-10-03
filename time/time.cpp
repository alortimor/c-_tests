#include <iostream>
#include "time.h"

Time::Time(int m) {this->minutes = m;}

void Time::Reset(int m) {this->minutes = m;}

/*
template <typename T>
Time operator+(const Time & t1, const T & t) {
  Time tmp;
  tmp.minutes = t1.minutes + t; // how this add either an integer or minutes if Time is passed
  return tmp;
}
*/

Time operator+(const Time & t1, const int m) {
  Time tmp;
  tmp.minutes = t1.minutes + m;
  return tmp;
}

Time operator+(const Time & t1, const Time & t2) {
  Time tmp;
  tmp.minutes = t1.minutes + t2.minutes;
  return tmp;
}

Time operator-(const Time & t1, const int m) {
  Time tmp;
  tmp.minutes = t1.minutes - m;
  return tmp;
}

Time operator-(const Time & t1, const Time & t2) {
  Time tmp;
  tmp.minutes = t1.minutes - t2.minutes;
  return tmp;
}

/*
template <typename T>
Time operator-(Time & t1, const T & t) {
  Time tmp;
  tmp.minutes = t1.minutes - t; // how this subtract either an integer or minutes if Time is passed
  return tmp;
}
*/

Time& Time::operator+=(const Time & t1) {
  this->minutes = this->minutes + t1.minutes;
  return *this;
}

Time& operator*(Time &t1, double && multiplier) {
  t1.minutes = t1.minutes * multiplier;
  return t1;
}

std::ostream & operator<<(std::ostream &o, const Time & t) {
  return o << t.minutes/60 << " hours " << t.minutes%60 << " minutes" << std::endl;
}
