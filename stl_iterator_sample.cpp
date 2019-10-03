#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename Iterator, typename Elem>
int cnt(Iterator start, const Iterator & finish, const Elem & v) {
  int n = 0; 
  for ( ; start != finish; ++start) {
    if (*start == v)
      n++;
  }
  return n;
}

struct Book {
  std::string title;
  int pages;
};

bool operator==(const Book & r1, const Book & r2) {
  if (r1.title == r2.title)
    return true;
  return false;
}

int main() {
  using std::cout;
  using std::vector;
  vector<Book> books { Book{"Elephant Song", 10}, Book{"Monsoon", 10} };
  Book temp;
  typedef vector<Book>::iterator iter;

  cout << "Count " << cnt<iter, Book>(begin(books),end(books), Book{"Monsoon",10}) << "\n";

  return 0;

}
