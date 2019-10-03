#include "tennis.h"
#include <iostream>

TennisPlayer::TennisPlayer(const string & fn
                          ,const string & ln
                          ,bool hc) : firstname(fn), lastname(ln), hasCourt(hc) { }

TennisPlayer::TennisPlayer(const TennisPlayer & tp) {
    this->firstname = tp.firstname;
    this->lastname = tp.lastname;
    this->hasCourt = tp.hasCourt;
}

void TennisPlayer::Name() const {
  std::cout << lastname << "," << firstname;
}
