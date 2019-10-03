#include "stonewt.h"
using std::cout;
#include <iostream>

Stonewt::Stonewt(double lbs) {
  stone = int(lbs) / Lbs_per_stn;
  pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
  pounds = lbs;
}

void Stonewt::show_lbs() const {
  cout << stone << " stone, " << pds_left << " pounds\n";
}

void Stonewt::show_stn() const {
  cout << pounds << " pounds\n";
}

Stonewt& operator *(Stonewt & s, const double multiplier) {
  double p = ( s.stone * Stonewt::Lbs_per_stn + s.pds_left ) * multiplier;
  s.stone = int(p) / Stonewt::Lbs_per_stn;
  s.pds_left = int(p) % Stonewt::Lbs_per_stn;
  return s;
}
