#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <iostream>

namespace VTR {
  class Vector {
    public:
      enum Mode {RECT, POL};
    private:
      double x, y;
      Mode mode;
      void set_mag();
      void set_ang();
      void set_y();
      void set_x();
    
    public:
      Vector();
      Vector(double n1, double n2, Mode form = RECT);
      void reset(double n1, double n2, Mode form = RECT);
      ~Vector();
      double xval() const {return x;}
      double yval() const {return y;} 
      double magval() const;
      double angval() const;
  
      void polar_mode();
      void rect_mode();
      Vector operator+(const Vector & b) const;
      Vector operator-(const Vector & b) const;
      Vector operator-() const;
      Vector operator*(const double n) const;

      friend Vector operator *(const double n, const Vector & a);
      friend std::ostream & operator <<(std::ostream & os, const Vector & v);
  };
}

#endif

