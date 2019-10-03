#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ctime>

const int NUM = 26;
const std::string wordlist[NUM] = {"apiary","beetle","cereal", "danger"
                             ,"ensign","florid","garage","health",
                             "insult","jackal","keeper","loaner",
                             "manage","nonce","onset", "plaid","quilt"
                             ,"remote","stolid","train","useful",
                             "valid","whence","xenon","yearn","zippy"};
int main() {
  using namespace std;
  srand(time(0));
  char play;
  cout << "Play word hame Y/N? ";
  cin >> play;
  while (play == 'y') {
    string target = wordlist[rand() % NUM];
    int length = target.length();
    string attempt(length, '-');
    string badchars;
    int guesses{6};
    cout << "Guess word \n"
    << "one letter at a time. Wrong guesses allowed " << guesses << "\n";
    cout << "Your word: " << attempt << endl;
    while (guesses > 0 && attempt != target)  {
      char letter;
      cout << "Guess a letter: ";
      cin >> letter;
      if (badchars.find(letter) != string::npos ||
          attempt.find(letter) != string::npos) {
        cout << "You already guessed that. Try again.\n";
        continue;
      }
      unsigned int loc = target.find(letter);
      if (loc == string::npos) {
        cout << "Bad guess!\n";
        --guesses;
        badchars += letter;
      }
      else {
        cout << "Good guess!\n";
        attempt[loc] = letter;
        loc = target.find(letter, loc + 1);
        while (loc != string::npos) {
          attempt[loc]=letter;
          loc = target.find(letter, loc + 1);
        }
      }
      cout << "Your word: " << attempt << endl;
      if (attempt != target) {
        if (badchars.length() > 0)
          cout << "Bad choices: " << badchars << endl;
        cout << guesses << " bad guesses left\n";
      }
    }
    if (guesses > 0)
      cout << "That's right!\n";
    else
      cout << "Sorry, the word is " << target << ".\n";
    cout << "Will you play another? <y/n> ";
    cin >> play;
    play = tolower(play);
  }
  return 0;
}
