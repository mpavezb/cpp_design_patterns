#include "observer.h"
#include "safer_observable.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Observable: Person notifies when the age field is changed.
 */
class Person : public SaferObservable<Person> {
  int age{0};

public:
  Person() {}
  explicit Person(int age) : age(age) {}

  int get_age() const { return age; }

  void set_age(int age) {
    if (this->age == age)
      return;
    this->age = age;
    notify(*this, "age");
  }
};

/**
 * Observer: Console observes age changes and prints them.
 */
struct ConsolePersonObserver : public Observer<Person> {
private:
  // implements field_changed() callback
  void field_changed(Person &source, const std::string &field_name) override {
    cout << "[ConsolePersonObserver] Person's " << field_name
         << " has changed to ";
    if (field_name == "age")
      cout << source.get_age();
    cout << ".\n";
  }
};

/**
 * Observer: Traffic buro observes age changes.
 */
struct TrafficAdministration : Observer<Person> {
  // implements field_changed() callback
  void field_changed(Person &source, const std::string &field_name) override {
    if (field_name == "age") {
      if (source.get_age() < 17)
        cout << "[TrafficAdministration] Whoa there, you're not old enough to "
                "drive!\n";
      else {
        // unsubscribe happens inside the notification -> possible deadlock!
        cout << "[TrafficAdministration] Oh, ok, we no longer care!\n";
        source.unsubscribe(*this);
      }
    }
  }
};

int main() {
  Person p;

  // multiple observers
  // ConsolePersonObserver cpo;
  TrafficAdministration ta;
  p.subscribe(ta);
  // p.subscribe(cpo);

  try {
    p.set_age(15);
    p.set_age(16);
    p.set_age(17);
    p.set_age(18);
    p.set_age(19);
  } catch (const std::exception &e) {
    cout << "Oops, " << e.what() << "\n";
  }

  return 0;
}
