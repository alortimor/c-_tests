#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
int main() {
  int A[] = {1, 4, 2, 8, 5, 7};
  int count = 0;

  auto greeting = [count]() { cout << count;};


  for_each( begin(A), end(A), [ &count ] (int i) { cout << i << " ";++count;});
    cout << endl << count << " objects printed." << endl; // *** THAT’S ALL NOW!!!


cout << "HH";
    greeting();
    cout << "HH";

  // BELOW ARE MORE EXAMPLES.
  sort(begin(A), end(A), [] (const int & a, const int & b) { return a < b; });
  
  for_each(begin(A), end(A), [] (const int & i) { cout << i << " "; });
  cout << endl;
  
  sort(begin(A), end(A), [] (const int & a, const int & b) { return a > b; });

  for_each(begin(A), end(A), [] (int i) { cout << i << " "; }); cout << endl;
  set<int> s1(begin(A), end(A)); s1.insert(1); s1.insert(13); s1.insert(10);

  for_each(begin(s1), end(s1), [] (int i) { cout << i << " "; }); cout << endl;
  auto comparison = [] (int i1, int i2) { // odd numbers come first
    return ((i1%2) == (i2%2)) ? (i1 < i2) : (1 == i1%2);
  };

  set<int, decltype(comparison)> // non­ standard comparison operator!!!
    s2(begin(A), end(A), comparison);
    
  s2.insert(1); s2.insert(13); s2.insert(10);
  for_each(begin(s2), end(s2), [] (int i) { cout << i << " "; }); cout << endl;
  auto an_iterator = s2.find(86); // type is "auto" !!!
  if (an_iterator != end(s2))
    cout << "86 is in the set\n";
  else
    cout << "86 is not in the set\n";

  return 0;
}

