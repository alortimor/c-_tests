#include <iostream>
#include <utility>
#include "linked_list.h"

int main() {
  typedef int Item;
  int firstInt{ 6 };
  Node<Item> first(firstInt);
  LinkedList<Item> score_sheet(&first);

  score_sheet.test(firstInt);
  //score_sheet.test(6);

  return 0;
}
