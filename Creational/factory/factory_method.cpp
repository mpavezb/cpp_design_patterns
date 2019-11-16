#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Point {
  // We would like to create cartesian and polar points, but we:
  // - cannot have 2 constructors with the same types.
  // - want to avoid optional parameters.
  // - want to avoid meaningless parameters.
  //
  //   Point(float x, float y);
  //   Point(float rho, float theta);
  //   Point(float a, float b, PointType type == PointType::cartesian);

  // Hide constructor
  Point(float x, float y) : x(x), y(y) {}

public:
  float x, y;

  // Our static methods allow us to to generate points using different logic.
  static Point NewCartesian(float x, float y) { return {x, y}; }

  static Point NewPolar(float rho, float theta) {
    return {rho * cosf(theta), rho * sinf(theta)};
  }

  friend ostream &operator<<(ostream &os, const Point &point) {
    return os << "(x, y) = (" << point.x << ", " << point.y << ")";
  }
};

int main() {
  auto p1 = Point::NewCartesian(0, 1);
  auto p2 = Point::NewPolar(1, M_PI_4);

  cout << p1 << endl;
  cout << p2 << endl;
  return 0;
}
