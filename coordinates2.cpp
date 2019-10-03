#include <iostream>
#include <cmath>

struct rect {
  double x; double y;
};

struct polar {
  double distance; double angle;
};

void show_polar(const polar *);
void rect_to_polar(const rect *, polar *);

int main()
{
  rect rplace;
  polar pplace;

  std::cout << "Enter x and y: ";
  while (std::cin >> rplace.x >> rplace.y) {
    rect_to_polar(&rplace, &pplace);
    show_polar(&pplace);
    std::cout << "Next two numbers (q to quit): ";
  }
  std::cout <<"Done.\n";
	return 0;
}

void show_polar (const polar *pda) {
  const double rad_to_deg = 57.29577951;

  std::cout << "distance = " << pda->distance;
  std::cout << ", angle = " << pda->angle * rad_to_deg;
  std::cout << " degrees\n";
}
void rect_to_polar(const rect *pxy, polar *pda) {
  pda->distance = sqrt(pxy->x * pxy->x + pxy->y * pxy->y);
  pda->angle = atan2(pxy->y, pxy->x);
}
