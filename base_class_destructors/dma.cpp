#include "dma.h"
#include <iostream>
#include <cstring>

baseDMA::baseDMA(const char * l, int r) {
  label = new char[std::strlen(l) + 1];
  std::strcpy(label, l);
  rating = r;
}

baseDMA::baseDMA(const baseDMA & rs) {
  label = new char[std::strlen(rs.label) + 1];
  std::strcpy(label, rs.label);
  rating = rs.rating;
}

baseDMA::~baseDMA() {
  delete [] label;
}

baseDMA & baseDMA::operator=(const baseDMA & rs) {
  if (this == &rs) // always check is the ref parameter equals existing object, if so, do nothing and return exiting object
    return *this;

  delete [] label; // always delete memory that is pointed to by existing pointer,
                   // before assigning new memory, so that a memory leak does not ensue
  label = new char[std::strlen(rs.label) + 1];
  std::strcpy(label, rs.label);
  rating = rs.rating;
  return *this;
}

std::ostream & operator<<(std::ostream & os, const baseDMA & rs) {
  os << "Label: " << rs.label << std::endl;
  os << "Rating: " << rs.rating << std::endl;
  return os;
}

lacksDMA::lacksDMA(const char * c, const char * l, int r) : baseDMA(l, r) {
  std::strncpy(color, c, 39);
  color[39] = '\0';
}

lacksDMA::lacksDMA(const char * c, const baseDMA & rs) : baseDMA(rs) {
  std::strncpy(color, c, COL_LEN - 1);
  color[COL_LEN - 1] = '\0';
}

std::ostream & operator<<(std::ostream & os, const lacksDMA & ls) {
  os << (const baseDMA &) ls;
  os << "Color: " << ls.color << std::endl;
  return os;
}

hasDMA::hasDMA(const char * s, const char * l, int r) : baseDMA(l, r) {
  style = new char[std::strlen(s) + 1];
  std::strcpy(style, s);
}

hasDMA::hasDMA(const hasDMA & hs) : baseDMA(hs) { // base class copy constructor
  style = new char[std::strlen(hs.style) + 1];
  std::strcpy(style, hs.style);
}

hasDMA::~hasDMA() {
  delete [] style;
}

hasDMA & hasDMA::operator=(const hasDMA & hs) {
  if (this == &hs)
    return *this;
  baseDMA::operator=(hs); // copy base portion. *this = hs; will not function as intended, since
                          // a recursive call will be initiated ... with no ending!
                          // So an explicit scope resoluter is used instead
  delete [] style;
  style = new char[std::strlen(hs.style) + 1];
  std::strcpy(style, hs.style);
  return *this;
}

std::ostream & operator<<(std::ostream & os, const hasDMA & hs) {
  // the following line can also be coded as:
  // os << static_cast<const baseDMA &>(hs);  C++11 style
  os << (const baseDMA &) hs;                     // C style
  os << "Style: " << hs.style << std::endl;
  return os;
}
