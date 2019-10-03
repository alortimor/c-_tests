#include <iostream>

int main() {
  int count{0};
  int arr[10] = {3,2,3,4,3,3,6,3,9,3};
  int majority_elem;
  for (int i = 0; i<=10; i++) {
    if (count == 0) {
      majority_elem = arr[i];
      count = 1;
    }
    else {
      if (majority_elem == arr[i])
        count++;
      else
        count--;
    }
  }

  if (count == 0) {
    std::cout << "No majority";
    return 0;
  }

  count = 0;
  for (int i = 0; i<=10; i++) {
    if (majority_elem == arr[i])
      count++;
  }
  if (count > 10/2)
    std::cout << "Majority element : " << majority_elem;
  else
    std::cout << "No majority";
  return 0;
}
