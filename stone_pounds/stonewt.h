#ifndef STONEWT_H_
#define STONEWT_H_

#include <iostream>

class Stonewt {
  private:
    enum {Lbs_per_stn = 14}; // pounds per stone
    int stone;
    double pds_left;
    double pounds;

  public:
    // explicit Stonewt(double lbs);
    Stonewt(double lbs);
    Stonewt(int stn, double lbs) : stone(stn), pds_left(lbs), pounds(stn/Lbs_per_stn) { }
    Stonewt()  { stone = pounds = pds_left = 0; }
    ~Stonewt() { }
    void show_lbs() const;
    void show_stn() const;

    operator int() const {return int (pounds + 0.5); }
    operator double() const {return pounds;}
    friend Stonewt& operator*(Stonewt &, const double);

    // you can also define the above 2 functions as
    // explicit  operator int() const {return int (pounds + 0.5); }
    // explicit  operator double() const {return pounds; }

    // by prefixing explicit, there is no ambiguity when attempting a conversion
    // i.e. it only converts when a valid integer or double are passed as arguments

};

#endif

