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

class Address {
public:
  string street, city;
  int suite;

  Address() {}

  Address(const string &street, const string &city, int suite)
      : street(street), city(city), suite(suite) {}

  friend ostream &operator<<(ostream &os, const Address &address) {
    return os << "street: " << address.street << ", city: " << address.city
              << ", suite: " << address.suite;
  }

private:
  friend class serialization::access;

  template <class archive> void serialize(archive &ar, const unsigned version) {
    ar &street;
    ar &city;
    ar &suite;
  }
};

class Contact {
public:
  string name;
  Address *address;

  Contact() {}

  Contact(const string &name, Address *address)
      : name(name), address(address) {}

  friend ostream &operator<<(ostream &os, const Contact &contact) {
    return os << "name: " << contact.name << ", address: " << *contact.address;
  }

private:
  friend class serialization::access;

  template <class archive> void serialize(archive &ar, const unsigned version) {
    ar &name;
    ar &address;
  }
};

// The prototype factory creates new employees from the same prototype employee.
class EmployeeFactory {
public:
  static unique_ptr<Contact> new_main_office_employee(const string &name,
                                                      const int suite) {
    static Contact p{"", new Address{"123 East Road", "London", 0}};
    return new_employee(name, suite, p);
  }

private:
  static unique_ptr<Contact> new_employee(const string &name, int suite,
                                          const Contact &prototype) {
    // copy
    auto result = make_unique<Contact>(prototype);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

int main() {
  // clone though serialization
  auto clone = [](const Contact &c) {
    // serialization
    ostringstream oss;
    archive::text_oarchive oa(oss);
    oa << c;
    string s = oss.str();
    cout << s << endl;

    // deserialization
    istringstream iss(s);
    archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;
    return result;
  };

  auto john = EmployeeFactory::new_main_office_employee("john", 123);
  auto jane = clone(*john);
  jane.name = "Jane";
  cout << *john << endl;
  cout << jane << endl;

  return 0;
}
