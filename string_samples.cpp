#include <iostream>
#include <string>

int main() {

  std::string s1; // default constructor string()
  std::string s2 = "bill"; //string( const char a[] ) constructor takes array of characters
  std::string s3 = s2; //string( const string &o ) - copy constructor

  int n = 10;
  int i = 1;
  for (i = 1; i < n; ++i) {
    std::cout << "n: " << i << std::endl;
  }
  std::cout << "------------- " <<  i << std::endl;
  i = 1;  
  for (i = 1; i < n; i++) {
    std::cout << "n: " << i << std::endl;
  }
  std::cout << "------------- " <<  i << std::endl;
  return 0;
}


  
