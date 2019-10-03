#include <future>
#include <iostream>
#include <functional> // required

int factorial( int n ) { return n < 2 ? 1 : n * factorial(n-1) ; }

int main() {

  // unary task (do not bind any args): invoke passing one integer argument
  std::packaged_task< int(int) > unary_task(factorial) ; 

  // nullary task (bind the integer argument): invoke without passing any arguments
  std::packaged_task< int() > nullary_task( std::bind(factorial,5) ) ; // bind 

  unary_task(5) ; // unary: pass one argument
  nullary_task() ; // nullary: no arguments

  const int x = unary_task.get_future().get() ;
  const int y = nullary_task.get_future().get() ;
  std::cout << x << ' ' << y << '\n' ;
}
