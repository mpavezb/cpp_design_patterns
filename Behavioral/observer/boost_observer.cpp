#include <boost/signals2.hpp>
#include <iostream>
#include <string>

using namespace boost::signals2;
using namespace std;

template <typename T> struct Observable {
  signal<void(T &, const string &)> field_changed;
};

class Person : public Observable<Person> {
  int age{0};

public:
  Person() {}
  explicit Person(int age) : age(age) {}

  int get_age() const { return age; }

  void set_age(int age) {
    if (this->age == age)
      return;
    this->age = age;

    field_changed(*this, "age");
  }
};

int main() {
  Person p;

  // subscribe
  auto conn =
      p.field_changed.connect([](const Person &p, const string &field_name) {
        cout << field_name << " has changed to: " << p.get_age() << endl;
      });

  p.set_age(18);
  p.set_age(19);
  p.set_age(20);

  // unsubscribe
  conn.disconnect();

  p.set_age(21);

  return 0;
}
