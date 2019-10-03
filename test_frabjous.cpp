#include <iostream>

class Fabulous {
  private:
    char fab[20];
  public:
    Fabulous(const char * s = "C++") : fab(s) { }
    virtual void tell() { cout << fab; }
};

class Glum {
  private:
    int glib;
    Fabulous fb;

  public:
    Glum(int g = 0, const char * s = "C++");
    Glum(int g = 0, const Fabulous &);
    void tell();
};

Glum::Glum(int g = 0, const char * s) :
  glib{g}, fb{s} { }

Glum::Glum(int g = 0, Fabulous & f) :
  glib{g}, fb{f} { }

void Glum::tell() {
  fb.tell();
  std::cout << glib << "\n";
}

int main() {
  char * a = (char *)"Bjarne Stroustrup";
  Glum g1{10};
  g1.tell();
  Glum g2{10, "Hello", a};
  g1.tell();
  return 0;
}
