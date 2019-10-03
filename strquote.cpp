#include <iostream>
#include <string>

std::string version1(const std::string &, const std::string &);
const std::string & version2(std::string &, const std::string &);
const std::string & version3(std::string &, const std::string &);


int main() {

  std::string input;
  std::string copy;
  std::string result;

  std::cout << "Enter a string: ";
  getline(std::cin, input);
  copy = input;
  std::cout << "Your string entered: " << input << std::endl;

  result = version1(input, "***");
  std::cout << "Your string enhanced: " << result << std::endl;
  std::cout << "Your original string: " << input << std::endl;

  result = version2(input, "###");
  std::cout << "Your string enhanced: " << result << std::endl;

  // s1 is a reference parameter, so the result is that the original
  // variable, input, has been modified to what s1 has become
  std::cout << "Your original string: " << input << std::endl;

  std::cout << "Resetting original string.\n";
  input = copy;

// the following line of code causes a core dump
//  result = version3(input, "@@@");
//  std::cout << "Your string enhanced: " << result << std::endl;
//  std::cout << "Your original string: " << input << std::endl;

  return 0;
}

std::string version1(const std::string & s1, const std::string & s2) {
  std::string temp;
  temp = s2 + s1 + s2;
  return temp;
}

// the input variable above will be altered, since s1 is a reference
// and input is passed in as a parameter to s1.
const std::string & version2(std::string & s1, const std::string & s2) {
  s1 = s2 + s1 + s2;
  return s1;
}

const std::string & version3(std::string & s1, const std::string & s2) {
  std::string temp;
  temp = s2 + s1 + s2;
  return temp;
}
