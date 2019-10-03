#include <iostream>

// calculates probability of winning, given the selection of 6 numbers across a range of 51 possible numbers

long double probability (unsigned numbers, unsigned picks);

int main()
{
  double total = 0, choices = 0;

  std::cout << "Enter number of choices and number of picks : ";
  while ((std::cin >> total >> choices) && choices <= total) {
    std::cout << "One chance in " << probability(total, choices) << " of winning.\n";
    std::cout << "Next 2 numbers (q to quit): ";
  }

  std::cout << "bye\n";
  return 0;

}

long double probability (unsigned numbers, unsigned picks) {
  long double result = 1.0;
  long double n;
  unsigned p;

  for (n = numbers, p = picks; p > 0; n--, p--)
    result = result * n / p;
  return result;
}
