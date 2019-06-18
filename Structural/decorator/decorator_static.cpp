#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Shape
{
  virtual string str() const = 0;
};

struct Circle: Shape
{
  float radius;

  Circle() {};
  Circle(float radius): radius(radius) {}

  void resize(float factor) {
    radius *= factor;
  }

  string str() const override {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }
};

struct Square: Shape
{
  float side;

  Square() {};
  Square(float side): side(side) {}

  void resize(float factor) {
    side *= factor;
  }

  string str() const override {
    ostringstream oss;
    oss << "A square of side " << side;
    return oss.str();
  }
};


///////////////////////////////
// Static Decorators
///////////////////////////////

// uses Mixing inheritance (inherits from template argument)
template <typename T> struct ColoredShape: T
{
  static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape");

  string color;

  // The constructor must enable the nesting of decorators.
  ColoredShape() {}
  
  template <typename...Args>
  ColoredShape(const string& color, Args ...args):
    T(std::forward<Args>(args)...), color{color} {}

  // it is correct to override, beacause T is always going to be a Shape.
  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <typename T> struct TransparentShape: T
{
  static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape");

  uint8_t transparency;

  // The constructor must enable the nesting of decorators.
  TransparentShape() {}
  
  template <typename...Args>
  TransparentShape(const uint8_t& transparency, Args ...args):
    T(std::forward<Args>(args)...), transparency{transparency} {}

  // it is correct to override, beacause T is always going to be a Shape.
  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";
    return oss.str();
  }
};

int main()
{
  Square square{8};

  ColoredShape<Square> red_square{"red", 4};
  TransparentShape<ColoredShape<Square>> transparent_and_red{51, "blue", 10};
  cout << square.str() << endl;
  cout << red_square.str() << endl;
  cout << transparent_and_red.str() << endl;

  Circle circle{10};
  ColoredShape<Circle> green_circle{"green", 7};
  cout << circle.str() << endl;
  cout << green_circle.str() << endl;
  green_circle.resize(10);
  cout << green_circle.str() << endl;

  return 0;
}
