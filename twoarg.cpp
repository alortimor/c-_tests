#include <iostream>

using namespace std;
void n_chars(char, int);

int main(int argc, char **argv)
{
	int times = 0;
  char ch;

  cout << "Enter character: ";
  cin >> ch;

  while (ch != 'q') {
    cout << "Enter integer: ";
    cin >> times;

    n_chars(ch, times);
    cout << "\nEnter character or q to quit: ";
    cin >> ch;
  }

  cout << "Value of times is : " << times << ".\n";
  cout << "Bye\n";
	return 0;
}

void n_chars(char c, int n)
{
    while (n-- > 0)
      cout << c;
}

