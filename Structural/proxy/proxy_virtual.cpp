#include <iostream>
#include <string>

using namespace std;

struct Image {
  virtual void draw() = 0;
};

// ORIGINAL CLASS
struct Bitmap : Image {
  Bitmap(const string &filename) {
    cout << "Loading bitmap from " << filename << endl;
  }

  void draw() override { cout << "Drawing bitmap" << endl; }
};

// VIRTUAL PROXY
// we dont want to really load the image until is required.
struct LazyBitmap : Image {
  string filename;
  Bitmap *bmp{nullptr};

  LazyBitmap(const string &filename) : filename(filename) {
    cout << "Loading Lazy" << endl;
  }

  void draw() override {
    cout << "Drawing Lazy" << endl;

    if (!bmp)
      bmp = new Bitmap(filename);
    bmp->draw();
  }
};

int main() {
  Bitmap bmp{"image.png"};
  bmp.draw();
  cout << endl;

  LazyBitmap lazy_bmp{"image.png"};
  lazy_bmp.draw();

  return 0;
}
