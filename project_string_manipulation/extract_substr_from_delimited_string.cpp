#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

std::string & ltrim(std::string &s, char c) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [c](int ch) { return !(ch==c);} ));
  return s;
}
  
std::string & rtrim(std::string &s, char c) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [c](int ch) { return !(ch==c);} ).base(), s.end());
  return s;
}

std::string & trim(std::string &s, char c) {
  ltrim(s, c);
  rtrim(s, c);
  return s;
}

int main() {
/*
  int c_id{0};
  std::string c_last {""};
  double c_discount{0.0};
  float w_tax{0.0};
  std::stringstream data {"1,zzz,0.09,10.0"};
  //std::string data {"1,z zz,0.09,10.0"};
  //unsigned short pos {0};
  //unsigned short start {0};

  char ch;
  data >> c_id >> ch;
  getline(data, c_last, ',');
  data >> c_discount >> ch >> w_tax;
  
  pos = data.find(',', start);
  c_id = std::stoi( data.substr(start, pos-start) );
  start = pos+1;
  c_last = std::stoi( data.substr(start, pos-start) );
  start = pos+1;
  c_discount = std::stod( data.substr(start, pos-start) );
  start = pos+1;
  w_tax = std::stof(data.substr(start, pos-start));
*/

  // data >> c_id >> c_last >> c_discount >> w_tax;
  // ltrim(c_last,',');
  // ltrim(c_discount,',');
 // std::cout << c_id << " " << c_last  << " " << c_discount << " "<< w_tax << "\n";

  int r {0};

  for (int i{1} ; i<10; ++i) {
    
    r = 1 + rand() % (6 - 1);
    std::cout << "random number " << r << "\n";
  }

  
  
  return 0; 
}
