#include "queue.h"

Queue::~Queue() {
  Node * temp;
  // remove any pointers that have not been deleted before destroying the Q object
  while (front != nullptr) {
    temp = front;
    front = front->next;
    delete temp;
  }
}

Queue::Queue(const Queue & q) {
  // create new pointers for nodes that might exist
  if (q.front != nullptr) {
    front = new Node;
    front = q.front;
    while 
  }
}

bool Queue::enqueue(const Item & item) {
  if (isfull())
    return false;
  Node * add = new Node; // create node  
  add->item = item;  
  add->next = nullptr;
  items++;
  if (front == nullptr)
    front = add;
  else
    rear->next = add;
    rear = add;
  return true;
}

bool Queue::dequeue(Item &item) {
  if (front == nullptr)
    return false;

  item = front->item;   // set item, which will be returned, i.e. dequeued
  items--;              // keeps track of number of nodes
  Node * temp = front;  // create a temp node to hld existing front
  front = front->next;  // set front to whatever is next
  delete temp;          // delete old front

  if (items == 0)
    rear = nullptr;
  return true;
}
