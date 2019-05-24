#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Address
{
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

struct Contact
{
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


int main()
{
  cout << endl << "Cloning class with ptr: " << endl;
  Contact john{"John Doe", new Address{"123 East Dr", "London", 100}};
  Contact jane = john;
  jane.name = "Jane Smith";
  cout << john << endl;
  jane.address->suite = 99999;
  cout << jane << endl;
  cout << john << endl;
  
  return 0;
}
