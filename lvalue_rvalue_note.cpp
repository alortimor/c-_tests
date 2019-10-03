
/*
 * 
 Simplified Definition
 * 
 lvalue - An object that occupies some identifiable location in memory (not something in the register)
 rvalue - Any object that is not a lvalue
 * 

  lvalue is a lvalue if the address is idenifiable!!!



*/

int main()

  int i; // i is a lvalue
  int* p = &i; // i is an lvalue as you can assign address of i to a pointer (p)
  
  class dog;
  dog d1; // lvalue of a user defined type
          // Most varaiables in C++ code are lvalues


  // rvalue example
  int x = 2; // 2 is a rvalue
  int x = i + 2; (i+2) is an ravlue
  
  // all these are rvalues, because they will not compile if you attempt to obtain address the 
  // int* p = &(i+2);
  // i+2 = 4
  // 2 = i;

  d1 = dog(); // dog is a rvalue of user defined type (class)

  int sum(int x, int y) { return x+y;}
  int i = sum(3,4);  // sum(3,4) is rvalue
  
  int y;
  int& r = y;
  // int& r = 5 // generates error

  // exception to this is when you make int& a constant,
  // since you assign a constant lvalue to an rvalue
  const int& r = 5;


  int square(int& x) { return x*x; }
  std::cout << square(i); // this will compile
  // std::cout << square(40); // this will ERROR!
  
  // workaround for the above error, make argument constant, e.g.
  int square(const int& x) { return x*x; } // square(40) and square(i) will now both compile
  
  // lvalue can be used to create a rvalue
  int i = 1;
  int x = i + 2;
  int x = i; // i (which is an lvalue above) is implicitly transformed to an rvalue
  // an rvalue however cannot be implicitly transformed to an lvalue
  
  // rvalue can be used to create an lvalue, if an address can be obtained, e.g.
  int v[3];
  *(v+2) = 4; // in this case, an rvalue is used to create a lvalue
  
  
  // Misconception 1 - function or operator always yields rvalues
  
  // in the following case the operator + yields a rvalue
  int x = i + 3; 
  
  // in the following case the function yields a rvalue
  int y = sum(3,4);
  
  // however, in this case, the function can be assigned an rvalue, instead of yielding an rvalue
  int myglobal;
  int& foo() { return myglobal; }
  foo() = 50;
  // the function foo returns an integer reference
  // inside foo, a global variable is returned by reference, since foo is defined to return int&
  // since it is returned as a reference, you can therefore assign a rvalue to foo()
  
  // generally, lvalues are modifiable
  // however, constant lvalues are not modifiable
  const int c = 1;
  // c = 5; // error

  // generally, rvalues are not modifiable,
  // however for user defined types, a ravlue can be modified, e.g.
  class dog;
  dog().bark();  // a method of dog, bark(), could potentially modify dog()
  return 0;
  
  
}
