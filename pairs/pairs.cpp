#include <iostream>
#include <string>

template <typename T1, typename T2>
class Pair {
  private:
    T1 a;
    T2 b;

  public:
    T1 & first();
    T2 & second();
    T1 first() const { return a; }
    T2 second() const { return b; }
    Pair(const T1 & aval, const T2 & bval) : a{aval}, b{bval} { }
    Pair() { }
};

template<typename T1, typename T2>
T1 & Pair<T1, T2>::first() {
  return a;
}

template<typename T1, typename T2>
T2 & Pair<T1, T2>::second() {
  return b;
}

int main() {
  using std::cout;
  using std::endl;
  using std::string;

  Pair<string, int> ratings[4] = {
    Pair<string, int>("Brockley Jack", 3)
   ,Pair<string, int>("Oscars", 4)
   ,Pair<string, int>("The Rock", 4)
   ,Pair<string, int>("La De Lice", 5)
  };

  // the sizeof (ratings) will show the total size of the array
  cout << "Sizeof " << sizeof(ratings) << "\n";
  // dividing the array sizeof by the elements's sizeof will return
  // the number of elements
  int restaurants = sizeof(ratings) / sizeof (Pair<string, int>);
  cout << "Rating:\t Restaurant\n";
  for (int i = 0; i < restaurants; i++) {
    cout << ratings[i].second() << ":\t" << ratings[i].first() << "\n";
  }
  return 0;
}
