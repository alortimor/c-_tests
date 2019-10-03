#include <iostream>
#include <cmath>

struct rect {
  double x; double y;
};

struct polar {
  double distance; double angle;
};

void show_polar(polar);
polar rect_to_polar(rect);

int main()
{
  rect rplace;
  polar pplace;

  std::cout << "Enter x and y: ";
  while (std::cin >> rplace.x >> rplace.y) {
    pplace = rect_to_polar(rplace);
    show_polar(pplace);
    std::cout << "Next two numbers (q to quit): ";
  }
  std::cout <<"Done.\n";
	return 0;
}

void show_polar (polar dapos) {
  const double rad_to_deg = 57.29577951;

  std::cout << "distance = " << dapos.distance;
  std::cout << ", angle = " << dapos.angle * rad_to_deg;
  std::cout << " degrees\n";
}

polar rect_to_polar(rect xypos) {
  polar answer;
  answer.distance = sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
  answer.angle = atan2(xypos.y, xypos.x);
  return answer;
}
