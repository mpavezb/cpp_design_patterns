#include <cmath>
#include <iostream>
#include <string>

using namespace std;

/*
We want to force using the factory:
- hide constructors.
- put the factory inside the class.
*/
class Point {
  float x, y;
  Point(float x, float y) : x(x), y(y) {}

public:
  friend ostream &operator<<(ostream &os, const Point &point) {
    return os << "(x, y) = (" << point.x << ", " << point.y << ")";
  }

private:
  // Inner Class
  class PointFactory {
  public:
    static Point NewCartesian(float x, float y) { return {x, y}; }

    static Point NewPolar(float rho, float theta) {
      return {rho * cosf(theta), rho * sinf(theta)};
    }
  };

public:
  // Optional: Make inner class private and provide this singleton.
  // Makes a cleaner API.
  // we prevent the creation of instances of the factory.
  static PointFactory Factory;
};

int main() {
  // V1: if inner class is public.
  // auto p1 = Point::PointFactory::NewCartesian(0, 1);
  // auto p2 = Point::PointFactory::NewPolar(1, M_PI_4);

  // Using singleton
  auto p1 = Point::Factory.NewCartesian(0, 1);
  auto p2 = Point::Factory.NewPolar(1, M_PI_4);

  cout << p1 << endl;
  cout << p2 << endl;
  return 0;
}
