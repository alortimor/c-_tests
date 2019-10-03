#include <iostream>
#include <random>

typedef unsigned int uint32;

class Random {
  private:
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<uint32> uniform_dist{0, UINT32_MAX};
  public:
    Random() = default;
    Random(const Random &) = delete;
    Random & operator=(const Random &) = delete;
    Random(std::mt19937::result_type seed) : eng{seed} {}

    uint32 generate();
    uint32 generate(uint32 ub);
};

uint32 Random::generate() {
  return uniform_dist(eng);
}

uint32 Random::generate(uint32 ub) {
  return uniform_dist(eng, decltype(uniform_dist)::param_type(0, ub));
}

int main() {
  Random r;
  std::cout << r.generate() << std::endl;
  std::cout << r.generate(42) << std::endl;
}
