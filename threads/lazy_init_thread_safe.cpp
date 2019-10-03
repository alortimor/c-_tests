#include <iostream>
#include <memory>
#include <string>

class Student {
  private:
    std::string sname;
    int sage{0};
    
  public:
    Student(std::string & name, int age) :  sname{name}, sage{age}  { }
    Student() {}

    Student ( const Student & ) = delete; // avoid copy constructor
    // Student ( const Student & ) = default; // lets the compiler create copy constructor

    ~Student() {}
    void init_profile(const std::string & name, const int age) {
      sname = name;
    }

    const std::string view_profile() const {
      return "Name : " + sname + ", age: " + std::to_string(sage) ;
    }

};

// if you pass the shared pointer by value, a segmentation fault occurs at runtime.
// void lazy_initialise(std::shared_ptr<Student> sptr, const std::string & name, const int age) {
void lazy_initialise(std::shared_ptr<Student> & sptr, const std::string & name, const int age) {
  if(!sptr) 
    sptr.reset(new Student);
  sptr->init_profile(name, age);
}

int main() {

  std::shared_ptr<Student> sptr;
  std::string name {"Peter"};
  int age {20};
  lazy_initialise(sptr, name, age);
  std::cout << "Profile : " << sptr->view_profile() << "\n";

  // the above scenario is not thread safe.
  // Refer to lazy_init_thread_safe2.cpp


  return 0;
}
