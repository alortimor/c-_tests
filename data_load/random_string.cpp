#include <iostream>
#include <string>
#include <thread>
#include <algorithm>
#include <random>

std::string gen_random_string (int size ) {
  const std::string VALID_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0,VALID_CHARS.size() - 1);
  std::string str;

  std::generate_n(std::back_inserter(str), size, [&]() {
    return VALID_CHARS[distribution(generator)];
  });

  return str;
}

int main() {
  
  std::string str {gen_random_string(10)};
  
  std::cout << str << std::endl;
}
