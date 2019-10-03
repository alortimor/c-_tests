#ifndef GOLF_H_
#define GOLF_H_

#include <string>

class Golf {
  private:
    enum {Len = 40};
    std::string fn;
    int hc;

  public:
    Golf(const char * full_name, const int handicap = 0);
    Golf() {fn = ""; hc = 0;};
    ~Golf();

    void set_handicap(const int handicap);
    Golf& setgolf(const char * full_name = "", const int handicap = 0);
    void showgolf() const;
};

#endif
