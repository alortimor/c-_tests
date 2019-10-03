#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "stack.h"

const int Num = 4;

int main() {
  std::srand(std::time(0));
  std::cout << "Enter stack size: ";
  int stacksize;
  std::cin >> stacksize;
  
  Stack<const char *> st(stacksize);

  // in basket
  const char * in[Num] = {" 1: Peter Koukoulis"
                        , " 2: Liz Morgan"
                        , " 3: Teri Goodyear"
                        , " 4: Jane Reid"};
  // out basket
  const char * out[Num];

  int processed{0};
  int nextin{0};
  while (processed < Num) {
    if (st.isempty())
      st.push(in[nextin++]);
    else if (st.isfull())
      st.pop(out[processed++]);
    else if (std::rand() % 2 && nextin < Num)
      st.push(in[nextin++]);
    else
      st.pop(out[processed++]);
  }
  for (int i = 0; i < Num; i++)
    std::cout << out[i] << "\n";

  std::cout << "Done.\n";
  return 0;
}
