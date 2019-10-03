#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class MultiF {
  private:
    T item;
  public:
    MultiF(const T & i) : item{i} { }
    template <typename C, typename D> friend void show(C &, D &);
};

template <typename C, typename D>
void show(C & c, D & d) {
  cout << c.item << ", " << d.item << endl;
}

int main() {
  MultiF<int> m1(10);
  MultiF<int> m2(20);
  MultiF<double> m3(10.5);
  cout << "m1, m2: ";
  show(m1, m2);
  cout << "m3, m2: ";
  show(m3, m2);

  return 0;
};


/*
you can use template declarations for aliases
for example:
template <typename T>
using at = std::array<T,12>;

can be used as:
at<double> prices;  // sizing is fixed at 12
at<int> quantity_sold; //sizing is fixed at 12
at<std::string> customer_name; //sizing is fixed at 12

*/
