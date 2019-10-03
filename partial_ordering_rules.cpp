#include <iostream>
template <class T> void ShowArray(T [], int); // template A
template <class T> void ShowArray(T * [], int); // template B

struct debts {
  char name[50];
  double amount;
};


int main() {

  int things[6] = {13,31,103,301,310,130};
  struct debts mr_E[3] = {{"Ima Wolf", 2400.0},{"Ura Fox", 1300.0},{"Iby Scout", 1800.0}};

  double * pd[3];

  for (int i = 0; i < 3; i++)
    pd[i] = &mr_E[i].amount;

  std::cout << "Listing Mr. E's counts:\n";
  ShowArray(things, 6);

  
  std::cout << "Listing Mr. E's debts:\n";

  // template B is selected, since B is more specialised than A, if B did
  // not exist, A would have been selected.
  // If template A was selected, it would display the addresses, instead
  // of the amounts, which is incorrect, so the most specialised template function
  // will always take precedence, in this case B.
  ShowArray(pd, 3);

  return 0;
}

template <class T> void ShowArray(T arr[], int n) {
  std::cout << "template A\n";
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << ' ';
  std::cout << std::endl;
}

template <class T> void ShowArray(T * arr[], int n) {
  std::cout << "template B\n";
  for (int i = 0; i < n; i++)
    std::cout << *arr[i] << ' ';
  std::cout << std::endl;
}

/*
Overload resolution process looks for a function that is best match.
--------------------------------------------------------------------
If only a single function exists then that function is selected.
If more than one function exists, and one of the functions is a non-template fnuction,
then the non-template function is selected.
If there are more than one template functions, then the most most specialised
of the template functions is selected.
If there are more than one template functions, and if none are more specialised than
any of the others, then an ambiguous function call error occurs.
*/
