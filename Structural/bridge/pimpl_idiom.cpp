#include "pimpl_idiom.hpp"
#include <iostream>
#include <string>

using namespace std;

// implementation is hidden by writting it on the source file.
class Person::PersonImpl {
public:
  void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p) {
  cout << "Hello, my name is " << p->name << "." << endl;
}

Person::Person() : impl(new PersonImpl) {}

Person::~Person() { delete impl; }

void Person::greet() { impl->greet(this); }

int main() {
  Person p;
  p.name = "Peter";
  p.greet();
  return 0;
}
