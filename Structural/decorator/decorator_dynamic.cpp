#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Shape {
  virtual string str() const = 0;
};

struct Circle : Shape {
  float radius;

  Circle(){};
  Circle(float radius) : radius(radius) {}

  void resize(float factor) { radius *= factor; }

  string str() const override {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

struct Square : Shape {
  float side;

  Square(){};
  Square(float side) : side(side) {}

  void resize(float factor) { side *= factor; }

  string str() const override {
    ostringstream oss;
    oss << "A square of side " << side;
    return oss.str();
  }
};

// Dynamic Decorator for Color
struct ColoredShape : Shape {
  Shape &shape;
  string color;

  ColoredShape(Shape &shape, const string &color)
      : shape(shape), color(color) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

// Dynamic Decorator for Transparency
struct TransparentShape : Shape {
  Shape &shape;
  uint8_t transparency;

  TransparentShape(Shape &shape, uint8_t transparency)
      : shape(shape), transparency(transparency) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f << "% transparency";
    return oss.str();
  }
};

int main() {
  Square square{8};
  ColoredShape red_sq{square, "red"};
  TransparentShape tr_and_red{red_sq, 51};
  cout << square.str() << endl;
  cout << red_sq.str() << endl;
  cout << tr_and_red.str() << endl;

  // Limitation: we cannot use the object interface.
  // We are limited to the base interface.
  Circle circle{10};
  ColoredShape green_circle{circle, "green"};
  // we cannot do this
  // green_circle.resize(10);

  return 0;
}
