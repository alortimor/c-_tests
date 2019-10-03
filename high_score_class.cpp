#include <iostream>
#include <string>

class GameEntry {
  // a game score entry
  public:
    GameEntry(const std::string &n="", int s=0) : nm(n), sc(s) {}

    std::string name() const {return nm};  // get player name
    int score() const {return sc};         // get score

    private:
      std::string nm;  // player’s name
      int sc;         // player’s score
};

int main() {
  return 0;
}
