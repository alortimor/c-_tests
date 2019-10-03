#include <iostream>
#include <cassert>
#include <string>
#include <regex>

int main() {

  std::string s = "";

  std::cin >> s;

  std::cout << "\nResult string : " << s;

  std::regex reg_expr("<[[:digit:]]+:");
  // std::regex reg_expr("\|[[:digit:]]+\|");
  assert(regex_match(s,reg_expr));

  std::cout << "\nResult string : " << s << std::endl;

//  std::cout << "String size " << s.size() << " Substring " << std::stol(s.substr (1,s.size()-2)) << std::endl;
  std::cout << "String size " << s.size() << " Substring " << s.substr (1,s.find(',',1,

  std::cin >> s;

  assert(s == ">");

  return 0;
}
