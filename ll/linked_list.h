#ifndef LL0_H_
#define LL0_H_

class Queue {
  private:
    struct Node {
      Item item;
      struct Node * next;
    };

    Node * head;
    Node * tail;
    Node * prev;
    Node * next;
    int  items;

  public:

    explicit Double_List() : font(nullptr), rear(nullptr), items(0) { }
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
