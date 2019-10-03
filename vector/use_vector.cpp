#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vect.h"
#include <fstream>

int main() {
  using VTR::Vector;
  using std::cout;
  using std::cin;
  using std::endl;

  std::ofstream fout;
  fout.open("tewalk.txt");
  srand(time(0));
  double direction;
  Vector step;
  Vector result(0.0, 0.0);
  unsigned long steps;
  double target;
  double dstep;

  cout << "Enter target distance (q to quit): ";
  while (cin >> target) {
    cout << "Enter step length: ";
    if (!(cin >> dstep))
      break;

    while (result.magval() < target) {
      direction = rand() % 360;
      step.reset(dstep, direction, Vector::POL);
      result = result + step;
      steps++;
    }

    fout << result << endl;

    cout << "After " << steps << " steps, the subject has the location:\n";
    cout << result << endl;
    result.polar_mode();
    cout << " or\n" << result << endl;
    cout << "Average outward distance per step = " << result.magval()/steps << endl;
    steps = 0;
    result.reset(0.0, 0.0);
    cout << "Enter target distance (q to quit): ";
  }
  cout << "Bye!\n";
  cin.clear();
  fout.close();

  while (cin.get() != '\n')
    continue;
  return 0;
}
