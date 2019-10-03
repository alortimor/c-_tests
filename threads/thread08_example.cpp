#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <fstream>

class stack {
  int* _data; // integer array to store data
  std::mutex _mu; // standard mutext to protect data
  
  public:
    void pop(); // pops off item on top of the stack
    int& top(); // returns item on top of stack
};

// assume stack class above does nothing to leak data to the outside world
/*
void function_1(stack& st) {
  int v = st.top();
  st.pop();
  process(v);
}
       ThreadA              ThreadB
        
 Stack       
  | |
  | |  int v = st.top; //6
  | |                       int v = st.top; //6
  | |  st.pop();                            //6 is now popped out of the stack
  |6|                       st.pop();       //8 is now popped out of the stack
6 |8|                       process(v);     //v is equal to 6, not 8, so process(v) processes 6
8 |3|  process(v);                          //8 is popped off the stack, but never processed
  |9|                                       //6 on the hand was processed twice!

So stack is NOT thread safe.

*/

// The reason the stack is not thread safe is the interface.
// The interface is designed in such a way to NOT thread safe, since top() and pop() 
// occur independently, whereas they should be executed together as an atomic execution

// So therefore modify function_1 as follows:
void function_1(stack& st) {
  int v = st.pop();
  process(v);
}

int main () {
  stack s;
  
  return 0;
}
