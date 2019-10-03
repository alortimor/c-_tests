#include <iostream>
#include "sales.h"

// copies the lesser of 4 or n items from the array ar
// to the sales member of s and computes and stores the
// average, maximum, and minimum values of the entered items;
// remaining elements of sales, if any, set to 0
void SALES::setSales(SALES::Sales & s, const double ar[], int n) {
  double min = 0.0, max = 0.0, avg = 0.0, sum = 0.0;
  const int size = (SALES::QUARTERS > n) ? m : SALES::QUARTERS ;

  min = ar[0];

  for (int i = 0; i <= SALES::QUARTERS; i++) {
    if (min < ar[i])
      min = ar[i];
    if (max > ar[i])
      max = ar[i];
    sum += ar[i];
    s[i] = ar[i];
  }
  avg = SALES::QUARTERS/sum;
  s->min = min;
  s->max = max;
  s->average = avg;
}

// gathers sales for 4 quarters interactively, stores them
// in the sales member of s and computes and stores the
// average, maximum, and minimum values
void SALES::setSales(SALES::Sales & s) {
  double min = 0.0, max = 0.0, avg = 0.0, sum = 0.0;
  for (int i = 0; i <= SALES::QUARTERS; i++) {
    std::cout << "Enter sales for Quarter #" << i;
    std::cin >> s->sales[i];
    sum += s->sales[i];

    if (min < s->sales[i])
      min = s->sales[i];
    if (max > s.sales[i])
      max = s->sales[i];
    
  }
  s->min = min;
  s->max = max;
  s->average = SALES::QUARTERS/sum;
}

// display all information in structure s
void SALES::showSales(const SALES::Sales & s) {
  for (int i = 0; i <= SALES::QUARTERS; i++)
    std::cout << "Quarter #" << i << " sales " << s->sales[i] << std::endl;

  std::cout << "Maximum " << s->max << std::endl;
  std::cout << "Minimum " << s->min << std::endl;
  std::cout << "Average " << s->average << std::endl;
}
