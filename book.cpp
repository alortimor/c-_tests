#include <string>
#include <iostream>

class Book  {
  public:
    std::string t;
    int p;
  
  Book (std::string title, int pg) : t(title), p(pg)  { }
};

int main() {
Book *b = new  Book{"Monsoon",200} ;
  std::cout << b->t << "\n";
  return 0;
  
}
  

  
