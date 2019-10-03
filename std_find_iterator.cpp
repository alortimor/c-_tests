# include <iostream>
# include <vector>
# include <algorithm>


class A{
  public:
    int n;
    A(int integer) : n(integer) {}
};

int main() {

  std::vector<int> i = {2, 4};
  std::vector<A> a = {1, 2, 3, 2, 4, 2, 5};

  for (auto & elem : a)
    if(std::find(i.cbegin(), i.cend(), elem.n) != i.end()) elem.n = 0;

  for (const auto& elem : a) 
    std::cout << elem.n << " "; 
}
