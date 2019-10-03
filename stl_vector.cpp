#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename Iterator, typename Elem>
int cnt(Iterator & start, const Iterator & finish, const Elem & v) {
  int n = 0; 
  for ( ; start != finish; ++start) {
    if (*start == v)
      n++;
  }
  return n;
}

struct Review {
  std::string title;
  int rating;
};

/*
If the container elements are user-defined objects, then there has to be an
operator<() function defined that works with that type of object in order to use sort()
*/

bool operator==(const Review & r1, const Review & r2) {
  if (r1.title == r2.title)
    return true;
  else
    return false;
}

bool operator<(const Review & r1, const Review & r2) {
  if (r1.title < r2.title)
    return true;
  else
    return false;
}

// so now sort(begin(books), end(books)); can be used, uses the operator<

// you can have a custom sort as well
bool ratingSort(const Review & r1, const Review & r2) {
  if (r1.rating < r2.rating)
    return true;
  else
    return false;
}
// so now sort(begin(books), end(books), RatingSort); can be used

bool FillReview(Review & rr);
void ShowReview(const Review & rr);

int main() {
  using std::cout;
  using std::vector;
  vector<Review> books;
  Review temp;
  typedef vector<Review>::iterator iter;

  while (FillReview(temp))
    books.push_back(temp);

  cout << "Count " << cnt<iter, Review>(books.begin(),books.end(), Review{"River God",10}) << "\n";

  if (books.size() > 0) {
    cout << "Thank you. You entered the following:\n"
         << "Rating\tBook\n";

    for_each(begin(books), end(books), ShowReview); // works with any container
    sort(begin(books), end(books)); 
    cout << "Sorted by title:\nRating\tBook\n";
    for_each(begin(books), end(books), ShowReview); // works with any container

    sort(begin(books), end(books), ratingSort);
    cout << "Sorted by rating:\nRating\tBook\n";
    for_each(begin(books), end(books), ShowReview); // works with any container

    random_shuffle(begin(books), end(books));
    cout << "After shuffling:\nRating\tBook\n";
    for_each(begin(books), end(books), ShowReview); // works with any container
    // random_shuffle only works with vectors
    // sort only works for containers with random access, i.e. vectors
/*    if (num > 3)  {
      // remove 2 items
      books.erase(begin(books) + 1, begin(books) + 3);
      cout << "After erasure:\n";
      for_each(begin(books), end(books), ShowReview);
      // insert 1 item
      books.insert(begin(books), begin(oldlist) + 1, begin(oldlist) + 2);
      cout << "After insertion:\n";
      for_each(begin(books), end(books), ShowReview);
    }
    books.swap(oldlist);
    cout << "Swapping oldlist with books:\n";
    for (pr = books.begin(); pr != books.end(); pr++)
      ShowReview(*pr);
*/
  }
  else
    cout << "No Entries.\n";
  return 0;
}

bool FillReview(Review & rr) {
  std::cout << "Enter book title (q to quit): ";
  std::getline(std::cin,rr.title);
  if (rr.title == "q")
    return false;
  std::cout << "Enter book rating: ";
  std::cin >> rr.rating;
  if (!std::cin)
    return false;
  // get rid of rest of input line
  while (std::cin.get() != '\n')
    continue;
  return true;
}
void ShowReview(const Review & rr) {
  std::cout << rr.rating << "\t" << rr.title << std::endl;
}

