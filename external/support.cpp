// compile with external.cpp
#include <iostream>
extern double warming; // use warming from another file

void update(double dt);
void local();
using std::cout;

void update(double dt) {
  extern double warming;
  // modifies global variable

  // optional redeclaration
  warming += dt;
  // uses global warming
  cout << "Updating global warming to " << warming;
  cout << " degrees.\n";
}

void local() {
  double warming = 0.8;
  cout << "Local warming = " << warming << " degrees.\n";

  // scope resolution operator ::
  cout << "But global warming = " << ::warming << " degrees.\n";
}
