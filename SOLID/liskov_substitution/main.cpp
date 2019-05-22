#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(int width, int height): width(width), height(height) {}

  int getWidth() const {
    return width;
  }

  virtual void setWidth(int width) {
    Rectangle::width = width;
  }

  int getHeight() const {
    return height;
  }

  virtual void setHeight(int height) {
    Rectangle::height = height;
  }

  int area() const {
    return width * height;
  }
};

/* This Square implementation breaks the Rectangle logic for setters. */
class Square: public Rectangle
{
public:
  Square(int size): Rectangle(size, size) {}

  void setWidth(int width) override {
    this->width = this->height = width;
  }

  void setHeight(int height) override {
    this->width = this->height = height;
  }
};

/* Square is derived from Rectangle, but cannot be passed to this function! 
It might seem that a Square is a subtype of a rectangle, but really it is not.
*/
void process(Rectangle& r) {
  int w = r.getWidth();
  r.setHeight(10);
  
  cout << "expected area = " << (w*10)
       << ", got " << r.area() << endl;
}

int main()
{
  Rectangle r{3,4};
  process(r);

  Square sq{5};
  process(sq);
  return 0;
}
