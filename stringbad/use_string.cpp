#include <iostream>
#include <cstdlib>
#include <ctime>

#include "string.h"

const int ArSize = 10;
const int MaxLen = 81;


using std::cin;
using std::cout;
using std::endl;

int main() {

  String name;

  cout << "Name :\n>> ";
  cin >> name;

  cout << name << ", Enter " << ArSize << " short sentences <empty line to quit>:\n";

  String sayings[ArSize];
  char temp[MaxLen];
  int i = 0;

  for (; i < ArSize; i++) {
    cout << i+1 << ": ";
    cin.get(temp, MaxLen);
    while (cin && cin.get() != '\n')
      continue;
    if (!cin || temp[0] == '\0') // empty line
      break;
    else
      sayings[i] = temp;
  }

  int total = i; // number of sentences

  if (total > 0) {
    cout << "Short sentences :\n";
    for (i = 0; i < total; i++)
      cout << sayings[i] << "\n";

    // 2 pointers that :
    //    a. keep track of the first ( alphabteically )
    //    b. and also the shortest in terms of number of characters
    String * shortest = &sayings[0];
    String * first = &sayings[0];

    for (i = 1; i < total; i++) {
      if (sayings[i].length() < shortest->length())
        shortest = &sayings[i];
      if (sayings[i] < *first)
        first = &sayings[i];
    }
    cout << "Shortest sentence: \n" << * shortest << endl;
    cout << "First alphabetically: \n" << * first << endl;
    srand(time(0));
    int choice = rand() % total;
    String * favourite = new String(sayings[choice]);
    cout << "My first saying:\n" << * favourite << endl;
    delete favourite; // the delete only deletes the str pointer and the len member,
                      // not the str that str point to
  }
  else
    cout << "No sentences \n";

  cout << "Done! \n";
  
  return 0; 
}
