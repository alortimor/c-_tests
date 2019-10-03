#include <iostream>
#include "tennis.h"

int main (void) {
  using std::cout;  using std::endl;
  TennisPlayer p1("Stefi", "Graf", false);

  p1.Name();
  if (p1.HasCourt())
    cout << ": has a court.\n";
  else
    cout << ": does not have a court.\n";

//  RatedPlayer rplayer1(999, "John", "McEnroe", true); // specify all parameters explicitly
//  unsigned int r = rplayer1.Rating();
//  cout << r << endl;

  RatedPlayer p2 = RatedPlayer(10, p1); // pass a TennisPlayer object
  
  TennisPlayer *p5 = new RatedPlayer(22, "Geoff", "Whitman", false);
  // RatedPlayer p4 = RatedPlayer(22, "Geoff", "Whitman", false);
  // TennisPlayer *p5 = &p4;

  p5->Name();
  if (p5->HasCourt())
    cout << ": has a court.\n";
  else
    cout << ": does not have a court.\n";

  delete p5;

  TennisPlayer player{"Gabriela", "Sabatini", true};
  RatedPlayer r;
  player = r;

  // RatedPlayer & r = player; // error - invalid initialization of reference of type ‘RatedPlayer&’ from expression of type ‘TennisPlayer’
  // RatedPlayer * p = player; // error - cannot convert ‘TennisPlayer’ to ‘RatedPlayer*’ in initialization

  return 0;

}
