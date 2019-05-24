#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Address
{
public:
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite): street(street), city(city), suite(suite) {}

  // copy constructor
  Address(const Address& address): street{address.street}, city{address.city}, suite{address.suite} {}

  friend ostream& operator<<(ostream &os, const Address &address)
  {
    return os << "street: " << address.street << ", city: " << address.city << ", suite: " << address.suite;
  }
};

class Contact
{
public:
  string name;
  Address *address;

  Contact(const string &name, Address* address): name(name), address(address) {}

  // Copy constructor makes deep copy
  Contact(const Contact& other): name{other.name}, address{new Address{*other.address}}
  {}

  friend ostream& operator<<(ostream &os, const Contact &contact)
  {
    return os << "name: " << contact.name << ", address: " << *contact.address;
  }
};

// The prototype factory creates new employees from the same prototype employee.
class EmployeeFactory
{
public:
  static unique_ptr<Contact> new_main_office_employee(const string& name, const int suite)
  {
    static Contact p{"", new Address{"123 East Road", "London", 0}};
    return new_employee(name, suite, p);
  }
private:
  static unique_ptr<Contact> new_employee(const string&name, int suite, const Contact& prototype)
  {
    // copy
    auto result = make_unique<Contact>(prototype);
    result->name = name;
    result->address->suite = suite;
    return result;
  }
};

int main()
{
  auto john = EmployeeFactory::new_main_office_employee("john", 100);
  cout << *john << endl;
  
  return 0;
}
