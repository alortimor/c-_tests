#include <string>
#include <iostream>
#include "./headers/ftn_client.h"

int main() {
  
  ftn_client ftn ("127.0.0.1", 3333);
  
  ftn.send_to_server("Hello World\n");
  std::string str;
  str = ftn.receive_response;
  
  std::cout << str << "\n";
  return 0;
};
