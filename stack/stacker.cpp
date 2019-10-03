#include <iostream>
#include <cctype>
#include "stack.h"


int main() {
  Stack st;
  char ch;
  unsigned long po;
  std::cout << "A - Add Order\n"
            << "P - Process Order\n"
            << "Q - Quit\n";

  while (std::cin >> ch && toupper(ch) != 'Q') {
    while (std::cin.get() != '\n')
      continue;
    if (!isalpha(ch)) {
      std::cout << '\a';
      continue;
    }
    switch(ch) {
      case 'A':
      case 'a': std::cout << "Enter PO Number: ";
                std::cin >> po;
                if (st.isfull())
                  std::cout << "Stack full\n";
                else
                  st.push(po);
                break;
      case 'P':
      case 'p': if (st.isempty())
                  std::cout << "Stack empty\n";
                else {
                  st.pop(po);
                  std::cout << "PO #" << po << " popped\n";
                }
                break;
    }
    std::cout << "A - Add Order\n"
              << "P - Process Order\n"
              << "Q - Quit\n";
     
  }
  std::cout << "\nDone.\n";
  return 0;
}
