#include <string>
#include <iostream>
#include <valarray>

typedef std::valarray<double> Scores;
    
class Student {
  private:
    std::string name;
    Scores scores;
    std::ostream & arr_out(std::ostream & os) const;
  public:
    Student() : name("Anonymous"), scores() {}
    explicit Student(int n) : name("Anonymous"), scores(n) { }
    explicit Student(const std::string & s, int n) : name(s), scores(n) { }
    explicit Student(const std::string & s, const double * pd, int n) : name(s), scores(pd, n) { }
    ~Student() {}
};

int main() {
  Scores sa(10);
  Student s;
  return 0;
}
