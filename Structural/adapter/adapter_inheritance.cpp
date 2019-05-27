#include <iostream>

using namespace std;

typedef int Coordinate;
typedef int Dimension;

// Adapter Interface
class Rectangle
{
  public:
    virtual void draw() = 0;
};

// Adaptee
// Legacy component that we want to reuse
// Works with coordinates
class LegacyRectangle
{
  public:
    LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
    {
        x1_ = x1;
        y1_ = y1;
        x2_ = x2;
        y2_ = y2;
        cout << "LegacyRectangle:  create.  (" << x1_ << "," << y1_ << ") => ("
          << x2_ << "," << y2_ << ")" << endl;
    }
    void oldDraw()
    {
        cout << "LegacyRectangle:  oldDraw.  (" << x1_ << "," << y1_ << 
          ") => (" << x2_ << "," << y2_ << ")" << endl;
    }
  private:
    Coordinate x1_;
    Coordinate y1_;
    Coordinate x2_;
    Coordinate y2_;
};

// ADAPTER wrapper
// - publicly inherits the desired interface.
// - privately inherits the adaptee component.
class RectangleAdapter: public Rectangle, private LegacyRectangle
{
  public:
    RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h):
      LegacyRectangle(x, y, x + w, y + h)
    {
        cout << "RectangleAdapter: create.  (" << x << "," << y << 
          "), width = " << w << ", height = " << h << endl;
    }
    virtual void draw()
    {
        cout << "RectangleAdapter: draw." << endl;
        oldDraw();
    }
};

// CLIENT
int main()
{
  // Now we can use the new interface.
  Rectangle *r = new RectangleAdapter(120, 200, 60, 40);
  r->draw();
}
