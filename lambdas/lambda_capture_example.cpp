#include <iostream>
#include <functional>

int main() {
  int i=1234,j=5678,k=9;
  // [=] - pass in all local varibales by value (copy), at the point of lambda creation
  // [&] - pass in all local by refence, so any local variable changes will be reflected within the lambda function
  // [= , &j] - values of i and k are copied in, whereas j is passed in by reference
  
  // [&, j, k] - all variables are passed in by reference, but j and k are copied in
  
  std::function<int()> f=[=,&j,&k]{return i+j+k;};
  i=1;
  j=2;
  k=3;
  std::cout<<f()<<std::endl; // changes made to "j" and "k" are reflected in the calculation, since
                             // they are passed by reference, but not i, since it is passed by reference
  i = 11;
  j = 12;
  k = 13;
  std::cout<<f()<<std::endl;
}
