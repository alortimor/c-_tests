#include <iostream>

using namespace std;
int main() {

int *p, i;
i = 10;
{
  int i = 5;
  int *p = &i;
  std::cout << "p " << *p << "\n";
}
std::cout << "Before assignment \n";
p = &i;
std::cout << "After assignment " << *p << "\n";
int arr[] = {1, 2, 3, 4, 5};
int *p1 = arr;

cout << p1[2] << "\n";
cout << 2[p1] << "\n";
cout << *(p1 + 2) << "\n";
cout << arr[2] << "\n";
cout << 2[arr] << "\n";
cout << *(arr + 2) << "\n";
return 0;
}
