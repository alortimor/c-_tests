#include <iostream>
#include <thread>
#include <string>


void f(int i,std::string const& s) {
  int x = i;
  std::string y {s};
  
  // do something....
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  std::cout << "string " << y << " integer " << x << "\n";
}


/*
This creates a new thread of execution associated with t , which calls f(3,”hello”) .
Note that even though f takes a std::string as the second parameter, the string lit-
eral is passed as a char const* and converted to a std::string only in the context of
the new thread. This is particularly important when the argument supplied is a
pointer to an automatic variable, as follows:
*/
// std::thread t(f,3,”hello”);


int main() {

  char buffer[1024];
/* Buffer is a  pointer to the local variable buffer that is passed through to the
   new thread, and there is a significant chance that the main thread will exit before
   the buffer has been converted to a std::string on the new thread, thus leading to
   undefined behavior. Solution is to cast to std::string before passing the buffer
*/  
  //   std::thread t(f,3,buffer);

  std::thread t(f,3,std::string(buffer));

  t.detach();
  return 0;
}

/* You can also call a thread as follows:
class X {
  public:
    void do_lengthy_work();
};

X my_x;
// first argument is a suitable object pointer.
// second argument is a member function pointer as the function
* // a third argument (not passed in this case), will be the first argument to the function
std::thread t(&X::do_lengthy_work,&my_x);

*/


