#ifndef SHOE_H
#define SHOE_H

#include <string>
#include <iostream>
#include <valarray>

template <typename T1, typename T2>
class Pair {
  private:
    T1 a; T2 b;
  public:
    T1 & first();
    T2 & second();
    T1 first() const { return a; }
    T2 second() const { return b; }
    Pair(const T1 & aval, const T2 & bval) : a(aval), b(bval) { } // use "( )" instead of "{ }" in case of container type
    Pair() { }
};

template<typename T1, typename T2>
T1 & Pair<T1, T2>::first() {
  return a;
}

template<typename T1, typename T2>
T2 & Pair<T1, T2>::second() {
  return b;
}

class Shoe {
  private:
    std::string _brand;
    int _year;
    int rol; // re order level
    typedef std::valarray<int> ArrayInt; // shoe size
    typedef std::valarray<double> ArrayDbl; // price
    typedef Pair<ArrayInt, ArrayDbl> PairArray;
    PairArray pa;

  public:
    Shoe(std::string & brand, int year, int count) : _brand{brand}, _year{year}, rol{count}, pa{ArrayInt(count), ArrayDbl(count)} { }
    void addSizePrice(int size, double price);
    double avgPrice() const;
    friend std::ostream & operator<<(std::ostream & os, const Shoe & shoe);
};

#include "shoe.cpp"
#endif
