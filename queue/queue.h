#ifndef QUEUE0_H_
#define QUEUE0_H_

#include <cstdlib>

class Customer {
  private:
    long arrive;
    int processtime;

  public:
    Customer() : arrive{0}, processtime{0} { }
    ~Customer() { }

    // set time to a random value in range 2 to 5
    void set(long when) {processtime = std::rand() % 5 + 2; arrive=when;}
    long when() const { return arrive; }
    int ptime() const { return processtime; }
};

using Item = Customer;

class Queue {
  private:
    struct Node {
      Item item;
      struct Node * next;
    };

    Node * front;
    Node * rear;
    int  items;
    const int qsize;
    const static int QSIZE {10};

  // the following 2 declerations are private so as to prevent public copy constructors

  public:

    explicit Queue(int qs = QSIZE) : qsize(qs), front(nullptr), rear(nullptr), items(0) { }
    Queue(const Queue & q) : qsize(0);
    Queue & operator =(const Queue & q);
    
    // Queue(Item & item);
    ~Queue();
    bool isempty() const { return (front == nullptr && rear == nullptr) ; }
    bool isfull() const { return items == qsize; }
    int  queuecount() const {return items; }                                                       
    bool enqueue(const Item &item);
    bool dequeue(Item &item);
};

#endif
