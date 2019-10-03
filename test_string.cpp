#include <string>
#include <iostream>

int main() {

  using namespace std;
  string s{"Hello World"};

  string s1(s, 0 ,5);
  string s2("Goodbye", 5);
  string s3(20, '$');
  cout << s1 << "\n";
  cout << s2 << "\n";
  cout << s3 << "\n";
  s += " ";
  s += s2;
  cout << s << "\n";
  s1 = s2 + s3;
  cout << s1 << "\n";

  char ch_ar[] = "The ugly duckling";
  cout << ch_ar << "\n";
  string ch_ar2(&ch_ar[0], &ch_ar[3]);
  cout << ch_ar2 << "\n";

  s[0] = 'P';
  cout << s << "\n";
  
  return 0;
}
