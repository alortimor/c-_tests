#include <iostream>
#include <cstring>
#include "worker.h"
const int SIZE = 2;
int main() {
  using std::cin;
  using std::cout;
  using std::endl;
  using std::strchr;

  Worker * lolas[SIZE];

  int ct;
  for (ct = 0; ct < SIZE; ct++) {
    char choice;
    cout << "Enter employee category:\n"
         << "w: waiter s: singer t: singing waiter q: quit\n";
    cin >> choice;
    while (strchr("wstq", choice) == NULL) {
      cout << "Enter a, w s, t, or q: ";
      cin >> choice;
    }
    if (choice == 'q')
      break;
    switch(choice) {
      case 'w': lolas[ct] = new Waiter;
                break;
      case 's': lolas[ct] = new Singer;
                break;
      case 't': lolas[ct] = new SingingWaiter;
                break;
    }
    cin.get();
    lolas[ct]->Set();
  }

  cout << " Selections " << "\n";
  int i;
  for (i = 0; i < ct; i++) {
    cout << endl;
    lolas[i]->Show();
  }
  for (i = 0; i < ct; i++) {
    delete lolas[i];
  }

  cout << "Done.\n";
  return 0;
}
