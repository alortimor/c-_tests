#include <iostream>

int main() {
  std::cout << "1 XOR-bitwise 3 = " << (     1     ^     3    ) << std::endl;
  std::cout << "1 XOR-logical 3 = " << ( ((bool)1) ^ ((bool)3)) << std::endl;
  return 0;
}
