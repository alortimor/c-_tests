#include <ios>
#include <iostream>
using namespace std;

struct skip {
  const char * text;
  skip(const char * text) : text(text) {}
};

std::istream & operator >> (std::istream & stream, const skip & x) {
  ios_base::fmtflags f = stream.flags();
  stream >> noskipws;

  char c;
  const char * text = x.text;
  while (stream && *text++)
    stream >> c;

  stream.flags(f);
  return stream;
}

int main() {
  int a, b;
  cin >> a >> skip(" # ") >> b;
  cout << a << ", " << b << endl;
  return 0;
}
