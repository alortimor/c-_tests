#include "student.h"

using std::ostream;
using std::string;
using std::endl;
using std::istream;

std::ostream & Student::arr_out(std::ostream & os) const {
  int i;
  int lim = ArrayDb::size();
  if (lim > 0) {
    for (i = 0; i < lim; i++) {
      os << ArrayDb::operator[](i) << " ";
      if (i % 5 == 4)
        os << endl;
    }
  }
  else
    os << " empty array ";
  return os;
}

double Student::Average() const {
  if (ArrayDb::size() > 0)
    return ArrayDb::sum()/ArrayDb::size();
  else
    return 0;
}

const std::string & Student::Name() const {
  return (const std::string &) *this;
}

double & Student::operator[](int i) {
  return ArrayDb::operator[](i);
}

double Student::operator[](int i) const {
  return ArrayDb::operator[](i);
}

std::istream & operator>>(std::istream & is, Student & su) {
  // the failed bit can be set as follows: is.setstate(std::ios::failbit);
  is >> (std::string &) su;
  return is;
}

std::istream & getline(std::istream & is, Student & su) {
  getline(is, (std::string &) su);
  return is;
}

std::ostream & operator<<(std::ostream & os, const Student & su) {
  os << "Scores for " << (std::string &) su << ":\n";
  su.arr_out(os);
  return os;
}
