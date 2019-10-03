#include <algorithm>
#include <string>
#include <iostream>

int main() {
  
  std::string str {"insert into test1 (x, y) values (:1, :22)"};
  std::string srch {":1"};
  int pos = str.find(srch);
  std::string part1 = str.substr(0, pos);
  std::string part2 = str.substr(pos+srch.size(), str.size());

  std::cout << "Part 1:" << part1 << std::endl;
  std::cout << "Part 2:" << part2 << std::endl;

  int w_id{122}; 
  std::string {"'Yello'"};
  part1 += std::to_string(w_id) +part2;

  std::cout << "Part 1:" << part1 << std::endl;



  srch =":22";
  pos = str.find(srch);
  part1 = str.substr(0, pos);
  part2 = str.substr(pos+srch.size(), str.size());

  std::cout << "Part 1:" << part1 << std::endl;
  std::cout << "Part 2:" << part2 << std::endl;

  std::string yell {"'Yellow'"};
  part1 += yell+part2;

  std::cout << "Part 1:" << part1 << std::endl;
  

  
    
  // std::cout << "Position found " << f << " size " << std::to_string(w_id).size() << std::endl;
  // std::to_string(f);
  // msg.replace(f, std::to_string(w_id).size(), std::to_string(w_id));
   
   //std::cout << msg << std::endl;

  /*std::cout << "Enter a string o serach in: " ;
  std::cin.ignore();
  getline (std::cin, msg);
  unsigned short c = std::count (msg.begin(), msg.end(), ch);
 
  std::cout << "Number of occurrences of " << c << " of character " << ch << " in " << msg << "\n"; */
  return 0; 
}
