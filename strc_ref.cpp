#include <iostream>
#include <string>

struct free_throws {
  std::string name;
  int made;
  int attempts;
  float percent;
};

void display(const free_throws &);
void set_pc(free_throws &);
free_throws & accumulate(free_throws & , const free_throws &);

int main() {

  free_throws one = {"Cape Town Branch", 13, 14};
  free_throws two = {"Claremont", 10, 16};
  free_throws three = {"Maximum", 7, 9};
  free_throws four = {"Long wheel base", 5, 9};
  free_throws five = {"Four by Four", 6, 14};
  free_throws team = {"Throw away", 0, 0};

  free_throws dup;

  set_pc(one);
  display(one);
  accumulate(team, one);
  display(team);

  display(accumulate(team, two));
  accumulate(accumulate(team, three), four);
  display(team);

  dup = accumulate(team, five);
  std::cout << "\n\nDisplaying team:\n";
  display(team);
  std::cout << " \n\nDisplaying dup after assignment:\n";
  display(dup);
  set_pc(four);
  
   // the folowing statement is equivalent to accumulate(dup,five); dup = four;
   // since the return value of accumulate is a reference, so dup is in fact assigned the reference
   // so the code executed in accumulate is therefore not considered in the final outcome
  accumulate(dup, five) = four;
  std::cout << "\n\nDisplaying dup after ill-advised assignment:\n";
  display(dup);
  
  return 0;
}

void display(const free_throws & ft) {
  using std::cout;
  cout << "\nName: " << ft.name << '\n';
  cout << " Made: " << ft.made;
  cout << " Attempts: " << ft.attempts;
  cout << " Percent: " << ft.percent;
}

void set_pc(free_throws & ft) {
  if (ft.attempts != 0)
    ft.percent = 100.0f * float(ft.made) / float(ft.attempts);
  else
    ft.percent = 0;
}

// the following definition will allow an assignment to accumulate, but if
// free_throws is prefixed with const then an assignment cannot occur and will
// generate an error.
free_throws & accumulate(free_throws & target, const free_throws & source) {
  target.attempts += source.attempts;
  target.made += source.made;
  set_pc(target);
  return target;
}

// having the following definition
// const free_throws & accumulate(free_throws & target, const free_throws & source)
// will prevent the following code
//   accumulate(accumulate(team, three), four);
// since it will generate an error if the definition of free_throws is prefixed with const


