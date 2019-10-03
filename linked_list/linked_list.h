#ifndef LINK_LIST_H_
#define LINK_LIST_H_

template <class T>
class Node {
  public:
    T data;
    Node*  next;
    Node*  prev;
    Node(T & node_data, Node* next_node = nullptr, Node* prev_node = nullptr)
      : data(node_data), next(next_node), prev(prev_node) { }
    ~Node() {}
};

template <class T>
class LinkedList {
  private:
    Node<T>* head;
    Node<T>* tail;

  public:
    LinkedList(Node<T> * node) : head(node), tail(node) {
        head->prev = tail;
        head->next = nullptr;
        tail->next = head;
        tail->prev = nullptr;
    } // Create a head & tail as part of the constructor

    ~LinkedList() { }
    void append(Node<T> * last) {
      Node<T> * tmp;
      tmp = this->tail;
      last->prev = tmp->prev;
      last->next = tmp->next;
      this->tail->next = nullptr;
      this->tail->prev = last;
    }
};


//template <typename L, typename T>
//L & operator++ (L & l, const & Node<T>) {
//  return l.append(Node<T>);
//};

#endif
