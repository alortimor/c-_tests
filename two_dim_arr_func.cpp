#include <iostream>

int sum(int (*)[4], int);

int main()
{
  int ar[3][4] = {{2,5,1,3}, {8,1,5,2}, {2,3,1,6}};
	std::cout << "Total: " << sum(ar, 3) << std::endl;
	return 0;
}

int sum(int ar[][4], int size) {
  const int inner_size = 4;
  int total = 0;
  for (int i = 0; i < size; i++)
    for (int j = 0; j < inner_size; j++)
      total += ar[i][j];
  return total;
}

