#include <iostream>
#include "worker.h"
using std::cout;
using std::cin;
using std::endl;

Worker::~Worker() { }

void Worker::Data() const {
  cout << "Name: " << fullname << endl;
  cout << "ID  : " << id << endl;
}

void Worker::Get() {
  getline(cin, fullname);
  cout << "ID : ";
  cin >> id;
  while (cin.get() != '\n')
    continue;
}

void Waiter::Get() {
  cout << "Waiter's panache rating : ";
  cin >> panache;
  while (cin.get() != '\n')
    continue;
}

void Waiter::Set() {
  cout << "Enter Waiter's name: ";
  Worker::Get();
  Get();
}

void Waiter::Data() const {
  cout << "Panache rating: " << panache << "\n";
}

void Waiter::Show() const {
  cout << "Category : Waiter\n";
  Worker::Data();
  Data();
}

char * Singer::pv[Singer::Vtypes] = {"other", "alto", "contralto", "soprano", "bass", "baritone", "tenor"};

void Singer::Set() {
  cout << "Singers name: ";
  Worker::Get();
  Get();
}

void Singer::Show() const {
  cout << "Category: singer\n";
  Worker::Data();
  Data();
}

void Singer::Data() const {
  cout << "Vocal range: " << pv[voice] << endl;
}

void Singer::Get() {
  cout << "Number of singers vocal range : ";
  int i;
  for (i = 0; i < Vtypes; i++) {
    cout << i << ": " << pv[i] << "  ";
    if (i % 4 == 3)
      cout << endl;
  }
  if (i % 4 != 3)
    cout << endl;
  while (cin >> voice && (voice < 0 || voice >= Vtypes) )
    cout << "Enter a value >= 0 and < " << Vtypes << endl;

  while (cin.get() != '\n')
    continue;
}

void SingingWaiter::Data() const {
  Singer::Data();
  Waiter::Data();
}

void SingingWaiter::Get() {
  Waiter::Get();
  Singer::Get();
}

void SingingWaiter::Set() {
  cout << "Enter singing waiter's name: ";
  Worker::Get();
  Get();
}

void SingingWaiter::Show() const {
  cout << "Category: singing waiter\n";
  Worker::Data();
  Data();
}
