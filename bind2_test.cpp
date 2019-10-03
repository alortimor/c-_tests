#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <vector>
 
int main() {
    std::vector<int> a= {0, 30, 45, 60, 90, 180};
    std::vector<int> r(a.size());
    // double pi = std::acos(-1);
 
    std::transform(a.begin(), a.end(), r.begin(), std::bind1st(std::multiplies<double>(), 10/1.2));
 
    for(size_t n = 0; n < a.size(); ++n)
        std::cout << a[n] << " deg = " << r[n] << " rad\n";

    return 0;
}
