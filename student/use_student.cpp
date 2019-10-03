#include <iostream>
#include "student.h"
using std::cin;
using std::cout;
using std::endl;

void set(Student & sa, int n);

const int pupils = 2;
const int scorecnt = 3;

int main() {

  Student sarray[pupils] {Student(scorecnt), Student(scorecnt)};
  int i;
  for (i= 0; i < pupils; ++i)
    set(sarray[i], quizzes);

  for(i = 0; i < pupils; ++i)
    cout << sarray[i].Name() << endl;

  cout << "\nResults:";
  for (i = 0; i < pupils; ++i) {
    cout << endl << sarray[i];
    cout << " avarage: " << sarray[i].Average() << endl;
  }
  cout << "Done.\n";
  return 0;
}

void set(Student & sa, int n) {
  cout << "Enter student name : ";
  getline(cin, sa);
  cout << "Enter " << n << " scores:\n";
  for (int i = 0; i < n; i++)
    cin >> sa[i];
  while (cin.get() != '\n')
    continue;
}

