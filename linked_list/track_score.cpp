#include <iostream>
#include <utility>
#include "linked_list.h"

int main() {
  typedef int Item;
  int firstItem{1};
  // Item * i;
  // Node<int> first(firstItem);

  Node<Item> first(firstItem);
  //*i = 6;
  LinkedList<Item> score_sheet(&first);

  // *i = 7;
  score_sheet.append(&first);
  return 0;
}
