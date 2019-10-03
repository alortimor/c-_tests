#include <iostream>
#include <cstring>

class Book {
  private:
    char * authors{nullptr};
    char * title{nullptr};
    int sold;
    double price;

  public:
    Book(const char *, const char *, int, double);
    Book(const Book &);
    Book();
    virtual ~Book();
    virtual void Report() const; // report
    Book & operator=(const Book &);
};

Book::Book(const char * s1, const char * s2, int n, double x) : sold{n}, price{x} {
  authors = new char[std::strlen(s1) + 1];
  std::strcpy(authors, s1);
  title = new char[std::strlen(s2) + 1];
  std::strcpy(title, s2);
}

Book::Book() : authors{nullptr}, title{nullptr}, sold{0}, price{0.0} { };

Book::~Book() {
  delete [] authors;
  delete [] title;
};

Book::Book(const Book & b) {
  authors = new char[std::strlen(b.authors) + 1];
  std::strcpy(authors, b.authors);
  title = new char[std::strlen(b.title) + 1];
  std::strcpy(title, b.title);
  sold = b.sold;
  price = b.price;  
}

Book & Book::operator=(const Book & b) {
  if (this == &b)
    return *this;

  delete [] authors;
  delete [] title;
  authors = new char[std::strlen(b.authors) + 1];
  std::strcpy(authors, b.authors);
  title = new char[std::strlen(b.title) + 1];
  std::strcpy(title, b.title);

  sold = b.sold;
  price = b.price;
  return *this;
}

void Book::Report() const {
  std::cout << "Author " << authors << " Title " << title ;
};

class BookCategory : public Book {
  private:
    char * category{nullptr};
  public:
    BookCategory(const char *, const char *, const char *, int, double);
    BookCategory(const BookCategory &);
    BookCategory();
    virtual ~BookCategory();
    virtual void Report() const; // report
    BookCategory & operator=(const BookCategory &);
};

BookCategory::BookCategory(const char * s1, const char * s2, const char * bc, int n, double x) : Book{s1, s2, n, x} {
  category = new char[std::strlen(bc) + 1];
  std::strcpy(category, bc);
}

BookCategory::BookCategory() : Book{}, category{nullptr} { };

BookCategory::~BookCategory() {
  delete [] category;
};

BookCategory & BookCategory::operator=(const BookCategory & bc) {
  if (this == &bc)
    return *this;
  Book::operator =(bc);
  delete [] category;
  category = new char[std::strlen(bc.category) + 1];
  std::strcpy(category, bc.category);
  return *this;
}

BookCategory::BookCategory(const BookCategory & bc) : Book(bc) {
  category = new char[std::strlen(bc.category) + 1];
  std::strcpy(category, bc.category);
}

void BookCategory::Report() const {
  Book::Report();
  std::cout << " Category " << category << "\n";
};

void BookReport(const Book & b);

int main() {
  const char * a = (char*)"Bjarne Stroustrup";
  const char * b = (char*)"The C++ Programming Language 4th Ed";
  Book b1(a, b, 14, 35.5);
  BookReport(b1);
  return 0;
}

void BookReport(const Book & b) {
  b.Report();
}
