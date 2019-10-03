#include <iostream>
#include <string>
// #include <new>

using namespace std;

const int BUF = 512;

class Tester {
  private:
    string words;
    int number;

  public:
    Tester(const string & s = "Tester", int n = 0) : words(s), number(n) {    }
    ~Tester() { cout << words << ", " << number << endl; }
    void Show() const { cout << words << ", " << number << endl; }
};

int main() {
  char * buffer = new char[BUF]; // 
  Tester *pc1, *pc2;

  pc1 = new (buffer) Tester; // place object in buffer
  pc2 = new Tester("Heap 1", 1); // place object on heap

  cout << "Memory addresses: \n" << "buffer: "
       << (void *) buffer << "   heap: " << pc2 << endl;

  cout << "Memory contents:\n";
  cout << pc1 << ", ";
  pc1->Show();
  cout << pc2 << ": ";
  pc2->Show();

  Tester *pc3, *pc4;
  // pc3 = new (buffer) Tester("New Object", 6); // overwrites buffer with the new object
                                              // the destructor for previous object is not called
  pc3 = new (buffer + sizeof(Tester)) Tester("New Object", 6);
  pc4 = new Tester("Heap 2", 2);

  cout << "Memory contents:\n";
  cout << pc3 << ": ";
  pc3->Show();
  cout << pc4 << ": ";
  pc4->Show();

  delete pc2;
  delete pc4;
  
  // delete pc3; // generates runtime error
  // delete pc1; // generates runtime error
  pc1->~Tester();
  pc3->~Tester();
  delete [] buffer; // this does not invoke the destructors for objects pointed to by
                    // pc1 and pc3
  cout << "Done.\n";
  return 0;
}
