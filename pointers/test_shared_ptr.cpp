#include <iostream>
#include <string>
#include <memory>

int main() {
  using namespace std;

  shared_ptr<std::string> tvsets[5] = {
        shared_ptr<string> (new string("Samsung"))
       ,shared_ptr<string> (new string("LG"))
       ,shared_ptr<string> (new string("Toshiba"))
       ,shared_ptr<string> (new string("Sony"))
       ,shared_ptr<string> (new string("Phillips"))
       };
  shared_ptr<string> best;
  best = tvsets[3];

  cout << "Best TV is\n";
  for (int i = 0; i < 5; i++)
    cout << *tvsets[i]<< endl;
  cout << "Fabulous! " << *best << "\n";
  return 0;
}

/*
// when using auto_ptr and assignment, the assigned pointer
// takes ownership, for example:
auto_ptr<string> p1(new string("sample");
auto_ptr<string> p2;
p2 = p1; // allowed
// p2 takes over ownership of the string, p1 stripped of ownership.
// p1 can no longer be used, if so, might lead to undefined behaviour!

unique_ptr<string> p3(new string("sample"));
// instead of "new", make_unique can also be used
unique_ptr<string> p3(std::make_unique<string>("sample"));
unqiue_ptr<string> p4;
p4 = p3; // invalid, generates error!

//however, in cases where a temporary copy is made and moved
//of unique_ptr, then that is allowed, for example:
unique_ptr<string> some_string(const char * s) {
  unique_ptr<string> temp(new string(s));
  return temp;
}

unique_ptr<string> ps;
ps = some_string("Test String");

// in this scenario some_string() returns a temporary unique_ptr
// temporary unique_ptr is then destroyed.

//if an attempt to assign one unique_ptr to another is made,
//it is allowed, if source object is temporary rvalue, but disallowed
//if source object has some duration:

// more examples:
using namespace std;
unique_ptr<string> p1(new string("Hello World"));
unique_ptr<string> p2;
p2 = p1; // invalid, generates compiler error!
unique_ptr<string> p3;
p3 = unique_ptr<string> (new string("Goodbye")); // VALID!

// assignment to p3 is valid because the temporary unique ptr that is generated
// is moved, therefore no duration

// one of the ways to get around the lack of an assignment for
// unique pointers is to use a move, for example:

using namespace std;
unique_ptr<string> p1, p2;
p1 = some_string("Test1");
p2 = move(p1);
p1 = some_string("Test2");
cout << *p2 << *p1 << endl;


// IMPORTANT POINT, unique_ptr can accommodate both "new/delete" and "new[]/delete[]"
// auto_ptr and shared_ptr can only accommodate "new/delete".

// for example:
std::unique_ptr < double[]->pd(new double(5)); // will use delete []

*/
