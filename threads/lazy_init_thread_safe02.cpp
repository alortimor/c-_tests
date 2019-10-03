#include <iostream>
#include <memory>
#include <string>
#include <mutex>

class Member;
using sharep = std::shared_ptr<Member>;

class Member {
  private:
    std::string sname;
    int sage{0};
    std::once_flag once_flag; // std::once_flag cannot be copied or moved

  public:
    Member(const std::string & name, int age) :  sname{name}, sage{age}  { }
    Member() {}
    Member ( const Member & ) = delete; // avoid copy
    ~Member() {}

    void init_profile(const std::string & name, const int age) {
      sname = name;  sage = age;
    }

    const std::string view_profile() const {
      return "Name : " + sname + ", age: " + std::to_string(sage);
    }

    void init(sharep & sptr, const std::string & name, const int age ) {
      std::call_once(once_flag, [/*sharep*/ & sptr](){ if(!sptr) sptr.reset(new Member); } ) ;
      sptr->init_profile(name, age);
    }
};

int main() {
  // sharep sptr(new Member());
  // the above line works as well, but make_shared is preferred since it is safer to use,
  // new might cause memory leek.
  // In addition make_shared is more efficient
  sharep sptr = std::make_shared<Member>();
  sptr->init(sptr, "Harry Potter", 12);
  std::cout << "Profile : " << sptr->view_profile() << "\n";
  return 0;
}
