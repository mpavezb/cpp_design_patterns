#include <iostream>
#include <string>

using namespace std;

// Shapes = circle, square.
// Renderer = raster, vector.
// Avoids 2x2 structure:
//  - RasterCircleRenderer
//  - RasterSquareRenderer
//  - VectorCircleRenderer
//  - VectorSquareRenderer.

struct Renderer {
  virtual void render_circle(float x, float y, float radius) = 0;
  virtual void render_square(float x, float y, float side) = 0;
};

struct RasterRenderer : Renderer {
  void render_circle(float x, float y, float radius) override {
    cout << "Rasterizing a circle of radius " << radius << endl;
  }

  void render_square(float x, float y, float side) override {
    cout << "Rasterizing a square of side " << side << endl;
  }
};

struct VectorRenderer : Renderer {
  void render_circle(float x, float y, float radius) override {
    cout << "Drawing a vector circle of radius " << radius << endl;
  }

  void render_square(float x, float y, float side) override {
    cout << "Drawing a vector square of side " << side << endl;
  }
};

struct Shape {
protected:
  // bridge to the renderer
  Renderer &renderer;
  Shape(Renderer &renderer) : renderer(renderer) {}

public:
  virtual void draw() = 0;
  virtual void resize(float factor) = 0;
};

struct Circle : Shape {
  Circle(Renderer &renderer, float x, float y, float radius)
      : Shape(renderer), x{x}, y{y}, radius{radius} {}

  float x, y, radius;

  void draw() override { renderer.render_circle(x, y, radius); }

  void resize(float factor) override { radius *= factor; }
};

struct Square : Shape {
  Square(Renderer &renderer, float x, float y, float side)
      : Shape(renderer), x{x}, y{y}, side{side} {}

  float x, y, side;

  void draw() override { renderer.render_square(x, y, side); }

  void resize(float factor) override { side *= factor; }
};

int main() {
  RasterRenderer rr;
  Circle raster_circle{rr, 5, 5, 5};
  raster_circle.draw();
  raster_circle.resize(2);
  raster_circle.draw();

  VectorRenderer vr;
  Square vector_square{vr, 0, 0, 4};
  vector_square.draw();
  vector_square.resize(3);
  vector_square.draw();
  return 0;
}
