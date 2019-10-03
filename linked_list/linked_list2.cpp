#include "linked_list.h"

// Create a head & tail as part of the constructor
/*template <class T>
LinkedList(Node::Node<T> * node) : head(node) { // Constructor
  head->next = tail;
  tail->prev = head;
  tail->next = nullptr;
  head->prev = nullptr;
}

~LinkedList() { // destructor
  Node<T>* tmp;
  for(;head;head = tmp) {
    tmp = head->next;
    delete head;
  }
}

void LinkedList::append(Node<T> * last) {
  Node<T> * tmp = this->tail;
  last->prev = tmp->prev;
  last->next = tmp->next;
  this->tail->next = nullptr;
  this->tail->prev = last;
}*/
