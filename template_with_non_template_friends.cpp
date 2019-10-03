#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class HasFriend {
  private:
    T item;
    static int ct;

  public:
    HasFriend(const T & i) : item{i} {ct++;}
    ~HasFriend() {ct--;}
    friend void counts();
    friend void reports(HasFriend<T> & hf); // template parameter
};

template <typename T>
int HasFriend<T>::ct{0};

// non-template friend to all HasFriend<T> classes
void counts() {
  cout << "int count : " << HasFriend<int>::ct << "; ";
  cout << "double count : " << HasFriend<double>::ct << "; ";
}

// non-template friend to HasFriend<double> "double" only!
void reports(HasFriend<double> & hf) {
  cout << "HasFriend<double>: " << hf.item << endl;
}

// non-template friend to HasFriend<double> "double" only!
void reports(HasFriend<int> & hf) {
  cout << "HasFriend<double>: " << hf.item << endl;
}

// non-template friend to HasFriend<T>, all data types.
//void reports(HasFriend<T> & hf) {
//  cout << "HasFriend<double>: " << hf.item << endl;
//}

int main() {
  cout << "No objects declared: ";
  counts();
  
  HasFriend<int> hfil1{10};
  cout << "After hfil1{10}: ";
  counts();
  
  HasFriend<int> hfil2{20};
  cout << "After hfil2{20}: ";
  counts();

  HasFriend<double> hfdb{10.5};
  cout << "After hfdb{10.5}: ";
  counts();

  reports(hfil1);
  reports(hfil2);
  reports(hfdb);

  return 0;
}
