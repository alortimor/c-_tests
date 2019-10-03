#ifndef STACK_H_
#define STACK_H_

template <typename Type>
class Stack {
  private:
    enum {SIZE = 10};
    int stacksize;
    Type * items;
    int top;

  public:
    explicit Stack(int ss = SIZE);
    Stack(const Stack & st); // copy constructor
    ~Stack() { delete [] items; }
    bool isempty() const { return top == 0; }
    bool isfull() const { return top == stacksize; }
    bool push(const Type & item);
    bool pop(Type & item);
    Stack & operator=(const Stack & st);

};

#include "stack.cpp"
#endif
