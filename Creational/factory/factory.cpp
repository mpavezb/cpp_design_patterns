#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Point
{
  float x, y;

public:
  Point(float x, float y): x(x), y(y) {}

  friend ostream &operator<<(ostream &os, const Point &point)
  {
    return os << "(x, y) = (" << point.x << ", " << point.y << ")";
  }
};

/*
This factory implementation is optional for the user, he 
can use the public constructor or the factory.

There is no strong mechanism to force the user to use the factory.
 */
struct PointFactory
{
  static Point NewCartesian(float x, float y)
  {
    return {x, y};
  }

  static Point NewPolar(float rho, float theta)
  {
    return { rho*cosf(theta), rho*sinf(theta)};
  }
};


int main()
{
  auto p1 = PointFactory::NewCartesian(0, 1);
  auto p2 = PointFactory::NewPolar(1, M_PI_4);

  cout << p1 << endl;
  cout << p2 << endl;
  return 0;
}
