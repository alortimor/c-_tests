#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <cstdlib>

template <typename T, int n>
class Array {
  private:
    T ar[n];

  public:
    Array() {};
    explicit Array(const T & v);
    virtual T & operator[](int i);
    virtual T operator[](int i) const;
};

template <typename T, int n>
T & Array<T, n>::operator[](int i) {
  if (i < 0 || i >= n) {
    std::cerr << "Error, array : " << i << " out of range \n";
    std::exit(EXIT_FAILURE);  
  }
  return ar[i];
}

template <typename T, int n>
T Array<T, n>::operator[](int i) const {
  if (i < 0 || i >= n) {
    std::cerr << "Error, array : " << i << " out of range \n";
    std::exit(EXIT_FAILURE);  
  }
  return ar[i];
}

#endif
