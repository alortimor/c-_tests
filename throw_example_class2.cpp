#include <iostream>
#include <cmath> // or math.h, unix users may need -lm flag

using namespace std;
class bad_mean {
  private:
    double v1, v2;

  public:
    bad_mean(double a = 0, double b = 0) : v1(a), v2(b) { }
    void mesg();
};

inline void bad_mean::mesg() {
  cout << "hmean(" << v1 << ", " << v2 << "); invalid arguments: a = -b\n";
}

class bad_gmean {
  public:
    double v1, v2;
    bad_gmean(double a = 0, double b = 0) : v1(a), v2(b) { }
    const char * mesg();
};

inline const char * bad_gmean::mesg() {
  return "gmean() arguments should be >= 0\n";
}


class demo {
  private:
    std::string word;
  public:
    demo (const std::string & str) {
      word = str;
      std::cout << "demo " << word << " created\n";
    }
    ~demo() {std::cout << "demo " << word << " destroyed\n";}
    void show() const {std::cout << "demo " << word << " lives!\n";
};

// function prototypes
double means(double a, double b);
double hmean(double a, double b);
double gmean(double a, double b);


int main() {
  using std::cout;
  using std::cin;
  using std::endl;
  double x, y, z;

  {
    demo d1("found in block of main()\n");
    cout << "Enter two numbers: ";
    while (cin >> x >> y) {
      try {
        z = means(x,y);
        cout << "The mean of " << x << " and " << y << " is " << z << endl;
        cout << "Enter next pair: ";
      } // end of try block
      catch (bad_hmean & bg) {
        // start of catch block
        bg.mesg();
        cout << "Try again.\n";
        continue;
      }
      catch (bad_gmean & hg) {
        cout << hg.mesg();
        cout << "Values used: " << hg.v1 << ", " << hg.v2 << endl;
        cout << "Sorry, you don't get to play any more.\n";
        break;
      } // end of catch block
      d1.show();
    }
  }
  cout << "Bye!\n";
  return 0;
}

double hmean(double a, double b) {
  if (a == -b)
    throw bad_hmean(a,b);
  return 2.0 * a * b / (a + b);
}

double gmean(double a, double b) {
  if (a < 0 || b < 0)
    throw bad_gmean(a,b);
  return std::sqrt(a * b);
}


double means(double a, double b) {
  double am, hm, gm;
  demo d2("found in means()");
  am = (a + b) / 2.0;
  // arithmetic mean
  try {
    hm = hmean(a,b);
    gm = gmean(a,b);
  }
  catch (bad_hmean & bg) {
    bg.mesg();
    std::cout << "Caught in means()\n";
    throw;
    // rethrows the exception
  }
  d2.show();
  return (am + hm + gm) / 3.0;
}
