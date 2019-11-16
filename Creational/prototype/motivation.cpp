#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Address {
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite)
      : street(street), city(city), suite(suite) {}

  friend ostream &operator<<(ostream &os, const Address &address) {
    return os << "street: " << address.street << ", city: " << address.city
              << ", suite: " << address.suite;
  }
};

struct Contact {
  string name;
  Address address;

  Contact(const string &name, const Address &address)
      : name(name), address(address) {}

  friend ostream &operator<<(ostream &os, const Contact &contact) {
    return os << "name: " << contact.name << ", address: " << contact.address;
  }
};

struct ContactPtr {
  string name;
  Address *address;

  // who owns this pointer?
  ContactPtr(const string &name, Address *address)
      : name(name), address(address) {}

  friend ostream &operator<<(ostream &os, const ContactPtr &contact) {
    return os << "name: " << contact.name << ", address: " << *contact.address;
  }
};

int main() {
  // without prototype
  cout << endl << "Using constructor: " << endl;
  Contact john{"John Doe", Address{"123 East Dr", "London", 123}};
  Contact jane1{"Jane Smith", Address{"123 East Dr", "London", 103}};
  cout << john << endl;
  cout << jane1 << endl;

  // Prototype version.
  // Only works because the address field is kept by value and not by pointer.
  cout << endl << "Cloning class without pointers: " << endl;
  Contact jane2 = john;
  jane2.name = "Jane Smith";
  jane2.address.suite = 103;
  cout << john << endl;
  cout << jane2 << endl;

  // This version does not works as intended, because it does not makes
  // a deep copy, just a shallow copy.
  cout << endl << "Cloning class with ptr: " << endl;
  ContactPtr john2{"John Doe", new Address{"123 East Dr", "London", 100}};
  ContactPtr jane3 = john2;
  jane3.name = "Jane Smith";
  cout << john2 << endl;
  jane3.address->suite = 99999;
  cout << jane3 << endl;
  cout << john2 << endl;

  return 0;
}
