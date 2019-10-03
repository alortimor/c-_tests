#include <iostream>

const int ArSize = 8;
int sum_arr(int *, int);

int main()
{

  int cookies[ArSize] = {1,2,4,8,16,32,64,128};
  std::cout << "Array address: " << cookies << std::endl;
  std::cout << "Array size   : " << sizeof cookies << std::endl;

  int sum = sum_arr(cookies, ArSize);
  std::cout << "Total cookies consumed : " << sum << std::endl;
  
  std::cout << "First 3 consumed : " << sum_arr(cookies, 3) << std::endl;
  std::cout << "Last 4 consumed : " << sum_arr(cookies + 4, 4) << std::endl;
	return 0;
}

int sum_arr(int *arr, int n) {
  int total = 0;

  std::cout << arr << " = arr, ";
  std::cout << sizeof arr << " = sizeof arr" << std::endl;
  for (int i = 0; i < n; i++)
    total += arr[i];
  return total;
}
