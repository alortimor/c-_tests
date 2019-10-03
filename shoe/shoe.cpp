#include <iostream>
std::ostream & operator<<(std::ostream & os, const Shoe & shoe) {
  os << "Brand : " << shoe._brand << " Year: " << shoe._year << "\n";
  for (int i = 0; i < shoe.rol; i++) {
    os << "Shoe Size " << shoe.pa.first()[i] << " Price " << shoe.pa.second()[i] << "\n";
  }
  return os;
}

double Shoe::avgPrice() const {
  double d;
  for (int i = 0; i < rol; i++)
    d += pa.second()[i];
  return d/rol;

}

void Shoe::addSizePrice(int size, double price) {
  for (int i = 0; i < rol; i++) {
    if ( (pa.first()[i] == 0) || (pa.first()[i] == size) ) {
      pa.first()[i] = size;
      pa.second()[i] = price;
      break;
    }
  }
}
