#include <iostream>
#include <string>
#include "golf.h"

Golf::Golf(const char * full_name, const int handicap) {
  fn = *full_name;
  hc = handicap;
}

Golf::~Golf() {}

Golf& Golf::setgolf(const char * full_name, const int handicap) {
  Golf && g = Golf(full_name, handicap);
	std::cout << "Enter full name: ";
	std::cin >> g.fn;
	std::cout << "Enter handicap: ";
  std::cin >> g.hc;
  return g;
}

// function resets handicap to new value
void Golf::set_handicap(const int handicap) {
	this->hc = handicap;
	return;
}

// function displays contents of golf structure
void Golf::showgolf() const
{
	using std::cout;
	using std::endl;
	
	cout << "Player name: " << this->fn << endl;
	cout << "Player handicap: " << (this->hc) << endl;
	return;
}
