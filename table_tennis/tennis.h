#ifndef TABLETENNIS_H_
#define TABLETENNIS_H_

#include <string>

using std::string;

class TennisPlayer {
  private:
    string firstname;
    string lastname;
    bool hasCourt;

  public:
    TennisPlayer(const string & fn = "none"
                ,const string & ln = "none"
                ,bool hc = false);         // default constructor
    TennisPlayer(const TennisPlayer & tp); // copy constructor
    ~TennisPlayer() { }

    void Name() const;
    bool HasCourt() const { return hasCourt; }
    void ResetTable(bool v) { hasCourt = v; }
};

class RatedPlayer : public TennisPlayer {
  private:
    unsigned int rating;

  public:
    RatedPlayer(unsigned int r = 0, const string & fn = "none",
                const string & ln = "none", bool hc = false)
            : TennisPlayer(fn, ln, hc), rating(r) { }

    ~RatedPlayer() { }
    RatedPlayer(unsigned int r, const TennisPlayer & tp) :
            TennisPlayer(tp), rating(r)  { }
  
    unsigned int Rating() const { return rating; }
    void ResetRating (unsigned int r) { rating = r; }
};

#endif
