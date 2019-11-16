#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

using namespace boost;
using namespace std;

struct Point {
  int x{0}, y{0};

  Point() {}

  Point(const int x, const int y) : x{x}, y{y} {}

  Point(const Point &p) : x(p.x), y(p.y) {}

  friend ostream &operator<<(ostream &os, const Point &point) {
    return os << "(" << point.x << ", " << point.y << ")";
  }

private:
  friend class serialization::access;

  template <class archive> void serialize(archive &ar, const unsigned version) {
    ar &x;
    ar &y;
  }
};

struct Line {
  Point *start, *end;

  Line() {}

  Line(Point *const start, Point *const end) : start(start), end(end) {}

  // copy ctor
  Line(const Line &l) : start{new Point{*l.start}}, end{new Point{*l.end}} {}

  ~Line() {
    delete start;
    delete end;
  }

  Line deep_copy() const {
    // using copy ctor
    // return Line(*this);

    // serialization
    ostringstream oss;
    archive::text_oarchive oa(oss);
    oa << *this;
    string s = oss.str();

    // deserialization
    istringstream iss(s);
    archive::text_iarchive ia(iss);
    Line result;
    ia >> result;
    return result;
  }

  friend ostream &operator<<(ostream &os, const Line &line) {
    return os << "p1: " << *line.start << ", p2: " << *line.end;
  }

private:
  friend class serialization::access;

  template <class archive> void serialize(archive &ar, const unsigned version) {
    ar &start;
    ar &end;
  }
};

int main() {
  auto l1 = Line(new Point(0, 0), new Point(1, 1));
  auto l2 = l1.deep_copy();
  l2.end->x = 90;
  l2.end->y = 100;
  cout << l1 << endl;
  cout << l2 << endl;

  return 0;
}
