#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <valarray>

class Student : private std::string, private std::valarray<double> {
  private:
    typedef std::valarray<double> ArrayDb;
    std::ostream & arr_out(std::ostream & os) const;
  public:
    Student() : std::string{"Null Student"}, ArrayDb{} {}
    explicit Student(const std::string & s) : std::string{s}, ArrayDb{} { }
    explicit Student(double n) : std::string{"Nully"}, ArrayDb{n} { }
    explicit Student(const std::string & s, double n) : std::string{s}, ArrayDb{n} { }
    explicit Student(const std::string & s, const ArrayDb & a) : std::string{s}, ArrayDb{a} { }
    explicit Student(const std::string & s, const double pd, double n) : std::string{s}, ArrayDb{pd, n} { }
    ~Student() {}
    double Average() const;
    const std::string & Name() const;
    double & operator[](int i);
    double operator[](int i) const;
    friend std::istream & operator>>(std::istream &, Student &);
    friend std::istream & getline(std::istream &, Student &);
    friend std::ostream & operator<<(std::ostream &, const Student &);
    
};

#endif
