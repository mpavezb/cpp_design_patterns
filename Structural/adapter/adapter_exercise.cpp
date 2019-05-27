#include <iostream>
using namespace std;

// Adaptee
struct Square
{
  int side{ 0 };
  explicit Square(const int side): side(side) {}
};

// Adapter Interface
struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

// ConcreteAdapter
struct SquareToRectangleAdapter: Rectangle
{
  const Square& square;
  SquareToRectangleAdapter(const Square& square): square(square) {}

  int width() const override { return square.side; }
  int height() const override { return square.side; }
};

int main()
{
  Rectangle *r = new SquareToRectangleAdapter(Square(10));

  cout << "Rectangle w=" <<  r->width() << ", h=" << r->height() << "." << endl;
  return 0;
}
