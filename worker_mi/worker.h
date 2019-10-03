#ifndef WORKER_H
#define WORKER_H

#include <string>

class Worker { // abstract base class
  private:
    std::string fullname;
    long id;
  protected:
    virtual void Data() const;
    virtual void Get();
  public:
    Worker() : fullname("Anonymous"), id(0L) { }
    Worker(const std::string & s, long l) : fullname(s), id(l) { }
    virtual ~Worker() = 0; // pure virtual function
    virtual void Set() = 0;
    virtual void Show() const = 0;
};

class Waiter : virtual public Worker {
  private:
    int panache;
  protected:
    void Data() const;
    void Get();
  public:
    Waiter() : Worker(), panache(0) { }
    Waiter(const std::string & s , long l, int p = 0) : Worker(s, l), panache(p) { }
    Waiter(const Worker & wk , int p = 0) : Worker(wk), panache(p) { }
    void Set();
    void Show() const;
};

class Singer : virtual public Worker {
  protected:
    enum {other, alto, contralto, soprano, bass, baritone, tenor};
    enum {Vtypes = 7};
    void Data() const;
    void Get();

  private:
    static char *pv[Vtypes];
    int voice;
  public:
    Singer() : Worker(), voice(other) { }
    Singer(const std::string & s , long l, int v = other) : Worker(s, l), voice(v) { }
    Singer(const Worker & wk , int v = 0) : Worker(wk), voice(v) { }
    void Set();
    void Show() const;
};

class SingingWaiter : public Waiter, public Singer {
  protected:
    void Data() const;
    void Get();
  public:
    SingingWaiter() { }
    SingingWaiter(const std::string & s, long l, int p = 0, int v = other)
        :  Worker(s, l), Waiter(s, l, p), Singer(s, l, v) { }
    SingingWaiter(const Worker & wk, int p = 0, int v = other)
        :  Worker(wk), Waiter(wk, p), Singer(wk, v) { }
    SingingWaiter(const Waiter & wt, int v = other)
        :  Worker(wt), Waiter(wt), Singer(wt, v) { }
    SingingWaiter(const Singer & wt, int p = 0)
        :  Worker(wt), Waiter(wt, p), Singer(wt) { }
    void Set();
    void Show() const;

};

#endif
