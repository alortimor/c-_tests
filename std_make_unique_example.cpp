#include <iostream>
#include <memory>
#include <string>

struct Point {
	double _x;
	double _y;
	std::string _s;

	Point (const double x, const double y, const std::string& s)	: _x(x), _y(y), _s(s){}
	~Point() {std::cout << "goodbye: " << _s << "\n";}
};

int main() {
	auto point_unique_ptr = std::make_unique<Point>(1.2, 3.4, "helloWorld");
  return 0;
}
