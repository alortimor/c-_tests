#include <iostream>

class A;
class B;
std::ostream & operator <<(std::ostream & o, const A & a);
std::ostream & operator <<(std::ostream & o, const B & b);

class A {
  private:
    int x, y;
  public:
    A(int _x = 0, int _y = 0) : x{_x}, y{_y} { } // default
    A & operator=(const A & a) {
      if (this == &a)
        return *this;
      
      A temp(a);
      temp.swap(*this);

      return *this;
    }

    void swap(A & s) {
      std::swap(this->x, s.y);
      std::swap(this->y, s.x);
    }

    friend std::ostream & operator <<(std::ostream & o, const A & a);
};

class B: public A {
  private:
    int z;
  public:
    B(int _x = 0, int _y = 0, int _z =  0) : A{_x, _y}, z{_z} { }
    friend std::ostream & operator <<(std::ostream & o, const B & b);

    B & operator=(const A & a) {
      if (this == &a)
        return *this;

      A::operator=(a);
      z = 0;
      return *this;
    }

    B & operator=(const B & b) {
      if (this == &b)
        return *this;

      A::operator=(b);
      z = b.z;
      return *this;
    }
};

std::ostream & operator <<(std::ostream & o, const A & a) {
  o << "X " << a.x << " Y " << a.y;
  return  o;
}

std::ostream & operator <<(std::ostream & o, const B & b) {
  o << (const A &) b;
  o << " Z " << b.z << "\n";
  return  o;
}

int main() {
  A a;
  B b{10,11,12};
  A * ap = &b;
  A c {12,13};

  std::cout << *ap << "\n";
  a = b; // this should initiate A & operator=(A & a);
  std::cout << a << "\n"; // this should display X 11 Y 10
  std::cout << b;
  b = c;
  std::cout << b;

  return 0;
}
