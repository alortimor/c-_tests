#include <iostream>
#include <cstring>

class Cd {
  private:
    char * performers{nullptr};
    char * label{nullptr};
    int selections;
    double playtime;

  public:
    Cd(char *, char *, int, double);
    Cd(const Cd &);
    Cd();
    virtual ~Cd();
    virtual void Report() const; // report
    Cd & operator=(const Cd &);
};

Cd::Cd(char * s1, char * s2, int n, double x) : performers{s1}, label{s2}, selections{n}, playtime{x} { }
Cd::Cd() : performers{nullptr}, label{nullptr}, selections{0}, playtime{0.0} { };

Cd::~Cd() {
  delete [] label;
  delete [] performers;
};

Cd::Cd(const Cd & d) {
  performers = new char[std::strlen(d.performers) + 1];
  std::strcpy(performers, d.performers);
  label = new char[std::strlen(d.label) + 1];
  std::strcpy(label, d.label);
  selections = d.selections;
  playtime = d.playtime;  
}

Cd & Cd::operator=(const Cd & d) {
  if (this == &d)
    return *this;

  delete [] performers;
  delete [] label;
  performers = new char[std::strlen(d.performers) + 1];
  std::strcpy(performers, d.performers);
  label = new char[std::strlen(d.label) + 1];
  std::strcpy(label, d.label);

  selections = d.selections;
  playtime = d.playtime;
  return *this;
}

void Cd::Report() const {
  std::cout << "Performer " << performers << label ;
};

class Classic : public Cd {
  private:
    char * primarywork{nullptr};
  public:
    Classic(char *, char *, char *, int, double);
    Classic(const Classic &);
    Classic();
    virtual ~Classic();
    virtual void Report() const; // report
    Classic & operator=(const Classic &);
};

Classic::Classic(char * s1, char * s2, char * pw, int n, double x) :
  Cd{s1, s2, n, x}, primarywork{pw} { }

Classic::Classic() : Cd{}, primarywork{nullptr} { };

Classic::~Classic() {
  delete [] primarywork;
};

Classic & Classic::operator=(const Classic & d) {
  if (this == &d)
    return *this;

  Cd::operator =(d);
  delete [] primarywork;
  primarywork = new char[std::strlen(d.primarywork) + 1];
  std::strcpy(primarywork, d.primarywork);

  return *this;
}

Classic::Classic(const Classic & d) : Cd(d) {
  primarywork = new char[std::strlen(d.primarywork) + 1];
  std::strcpy(primarywork, d.primarywork);
}

void Classic::Report() const {
  Cd::Report();
  std::cout << " Primary Work " << primarywork << "\n";
};

void Bravo(const Cd & disk);

int main() {
  char * p = (char*)"Beatles";
  char * l = (char*)"Capitol";
  Cd c1(p, l, 14, 35.5);
  // Classic c2 = Classic((char*)"Piano Sonata", (char*)"Alfred Brendel", (char*)"Philips", 2, 57.17);
  //Cd *pcd = &c1;
  //std::cout << "Using object directly:\n";
  //c1.Report();
  // use Cd method
  //c2.Report();
  /*// use Classic method
  std::cout << "Using type cd * pointer to objects:\n";
  pcd->Report(); // use Cd method for cd object
  pcd = &c2;
  pcd->Report(); // use Classic method for classic object
  std::cout << "Calling a function with a Cd reference argument:\n";
  Bravo(c1);
  Bravo(c2);
  std::cout << "Testing assignment: ";
  Classic copy;
  copy = c2;
  copy.Report();*/
  return 0;
}

void Bravo(const Cd & disk) {
  disk.Report();
}
