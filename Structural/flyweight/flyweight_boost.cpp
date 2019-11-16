#include <boost/flyweight.hpp>
#include <iostream>
#include <string>

using namespace std;

struct User {
  boost::flyweight<string> first_name;
  boost::flyweight<string> last_name;

  User(const string &first_name, const string &last_name)
      : first_name{first_name}, last_name{last_name} {}
};

ostream &operator<<(ostream &os, const User &user) {
  os << "User: " << user.first_name << " " << user.last_name;
}

int main() {
  User user1{"John", "Doe"};
  User user2{"John", "Smith"};

  cout << user1 << endl;
  cout << user2 << endl;

  // compare references to check if they point to same the object.
  cout << boolalpha;
  cout << (&user1.first_name.get() == &user2.first_name.get()) << endl;
  cout << (&user1.last_name.get() == &user2.last_name.get()) << endl;
  return 0;
}
