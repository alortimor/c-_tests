// Doubly Linked List 
#include<iostream>
#include<cstdio>
#include<cstdlib>

// Node Declaration
using namespace std;
struct node {
    int info;
    struct node *next;
    struct node *prev;
}* start;

// Class Declaration 
class double_llist {
  public:
    void create_list(int value);
    void add_begin(int value);
    void add_after(int value, int position);
    void delete_element(int value);
    void search_element(int value);
    void display_dlist();
    void count();
    void reverse();
    double_llist() {
      start = NULL;  
    }
};

// Main with Menu
int main() {
  int choice, element, position;
  double_llist dl;
  while (1) {
    cout << endl << "Menu for a doubly linked list" << endl;
    cout << endl << "-----------------------------" << endl;

    cout << "1.Create Node" << endl;
    cout << "2.Add at begining" << endl;
    cout << "3.Add after position" << endl;
    cout << "4.Delete" << endl;
    cout << "5.Display" << endl;
    cout << "6.Count" << endl;8
    cout << "7.Reverse" << endl;
    cout << "8.Quit" << endl;
    cout << "Enter selection : ";
    cin>>choice;

    switch ( choice ) {
    case 1:
      cout << "Enter node: ";
      cin >> element;
      dl.create_list(element);
      cout << endl;
      break;
    case 2:
      cout << "Enter the node: ";
      cin>>element;
      dl.add_begin(element);
      cout << endl;
      break;
    case 3:
      cout << "Enter the node: ";
      cin >> element;
      cout << "Insert Node after : ";
      cin >> position;
      dl.add_after(element, position);
      cout << endl;
      break;
    case 4:
      if (start == NULL) {                      
        cout << "List empty" << endl;   
        break;
      }
      cout << "Enter the element for deletion: ";
      cin >> element;
      dl.delete_element(element);
      cout << endl;
      break;
    case 5:
      dl.display_dlist();
      cout << endl;
      break;
    case 6:
      dl.count();
      break;    
    case 7:
      if (start == NULL) {
        cout << "List empty" << endl;
        break;
      }
      dl.reverse();
      cout << endl;
      break;
  case 8:
      exit(1);
    default:
      cout << "Unidentified selection" << endl;
    }
  }
  return 0;
}
 
// Create Double Link List
void double_llist::create_list(int value) {
  struct node *s, *temp;
  temp = new(struct node); 
  temp->info = value;
  temp->next = NULL;
  if (start == NULL) {
    temp->prev = NULL;
    start = temp;
  }
  else {
    s = start;
    while (s->next != NULL)
      s = s->next;

    s->next = temp;
    temp->prev = s;
  }
}
 
// Insertion at the beginning
void double_llist::add_begin(int value) {
  if (start == NULL) {
    cout << "Create List before adding!" << endl;
    return;
  }
  struct node *temp;
  temp = new(struct node);
  temp->prev = NULL;
  temp->info = value;
  temp->next = start;
  start->prev = temp;
  start = temp;
  cout << "Node Added" << endl;
}
 
// Insertion of element at a particular position
void double_llist::add_after(int value, int pos) {
  if (start == NULL) {
    cout << "Create List before adding!" << endl;
    return;
  }
  struct node *tmp, *q;
  int i;
  q = start;
  for (i = 0; i < pos - 1; i++) {
      q = q->next;
      if (q == NULL) {
        cout << "Less than " << pos << " elements." << endl;
        return;
      }
  }
  tmp = new(struct node);
  tmp->info = value;

  if (q->next == NULL) {
    q->next = tmp;
    tmp->next = NULL;
    tmp->prev = q;
  }
  else {
    tmp->next = q->next;
    tmp->next->prev = tmp;
    q->next = tmp;
    tmp->prev = q;
  }
  cout << "Element Added" << endl;
}
 
// delete specific element from list
void double_llist::delete_element(int value) {
  struct node *tmp, *q;
  
  // if first element
  if (start->info == value) {
    tmp = start;
    start = start->next;  
    start->prev = NULL;
    cout << "Element Deleted" << endl;
    free(tmp);
    return;
  }

  q = start;
  while (q->next->next != NULL) {   
    // Element deleted in between
    if (q->next->info == value) {
      tmp = q->next;
      q->next = tmp->next;
      tmp->next->prev = q;
      cout << "Element Deleted" << endl;
      free(tmp);
      return;
    }
    q = q->next;
  }

  // delete last
  if (q->next->info == value) { 	
    tmp = q->next;
    free(tmp);
    q->next = NULL;
    cout << "Element Deleted" << endl;
    return;
  }
  cout << "Element " << value << " not found" << endl;
}
 

// Display all elements
void double_llist::display_dlist() {
    struct node *q;
    if (start == NULL) {
      cout << "List empty" << endl;
      return;
    }
    q = start;
    cout << "Doubly Link List :" << endl;
    while (q != NULL) {
      cout << q->info << " <-> ";
      q = q->next;
    }
    cout << "NULL" << endl;
}
 

// Count number of nodes
void double_llist::count() { 	
    struct node *q = start;
    int cnt = 0;
    while (q != NULL) {
      q = q->next;
      cnt++;
    }
    cout << "Node Count: " << cnt << endl;
}

// Reverse Doubly Link List
void double_llist::reverse() {
    struct node *p1, *p2;
    p1 = start;
    p2 = p1->next;
    p1->next = NULL;
    p1->prev = p2;
    while (p2 != NULL) {
      p2->prev = p2->next;
      p2->next = p1;
      p1 = p2;
      p2 = p2->prev; 
    }
    start = p1;
    cout << "List Reversed" << endl; 
}
