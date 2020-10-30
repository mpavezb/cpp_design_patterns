#include "observable.h"
#include "observer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Observable: Person notifies when the age field is changed.
 */
class Person : public Observable<Person> {
  int age{0};

public:
  Person() {}
  explicit Person(int age) : age(age) {}

  int get_age() const { return age; }

  void set_age(int age) {
    if (this->age == age)
      return;

    auto old_can_vote = get_can_vote(); // (1)
    this->age = age;
    notify(*this, "age");

    if (old_can_vote != get_can_vote()) // (2)
      notify(*this, "can_vote");        // (3)
  }

  /**
   * This "class attribute" shows a complication of the observer pattern, where
   * it is not easy to notify changes on fields which depend on others, and have
   * no setter.
   *
   * See how the set_age() method turns complex when dealing with this
   * attribute:
   * - (1): keep old state.
   * - (2): assess diff with new state.
   * - (3): notify if necessary.
   */
  bool get_can_vote() const { return age >= 16; }
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
    if (field_name == "can_vote")
      cout << boolalpha << source.get_can_vote();
    cout << ".\n";
  }
};

int main() {
  Person p;
  ConsolePersonObserver cpo;

  p.subscribe(cpo);

  p.set_age(15);
  p.set_age(16);
  p.set_age(17);

  p.unsubscribe(cpo);

  p.set_age(18);

  return 0;
}
