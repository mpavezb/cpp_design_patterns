#include <boost/bimap.hpp>
#include <iostream>
#include <string>

using namespace std;

// we store all names into a bidirectional map,
// using a numeric key as reference.
typedef uint16_t key;

struct User {
private:
  static boost::bimap<key, string> names;
  static key seed;

public:
  key first_name, last_name;

  User(const string &first_name, const string &last_name)
      : first_name{add(first_name)}, last_name{add(last_name)} {}

  const string &get_first_name() const {
    return names.left.find(first_name)->second;
  }

  const string &get_last_name() const {
    return names.left.find(last_name)->second;
  }

private:
  static key add(const string &s) {
    auto it = names.right.find(s);
    if (it == names.right.end()) {
      key id = ++seed;
      names.insert({seed, s});
      return id;
    }
    return it->second;
  }
};

key User::seed{0};
boost::bimap<key, string> User::names{};

ostream &operator<<(ostream &os, const User &user) {
  os << "User: " << user.get_first_name() << " " << user.get_last_name() << " ("
     << user.first_name << ", " << user.last_name << ")";
  return os;
}

int main() {
  User user1{"John", "Doe"};
  User user2{"John", "Smith"};

  cout << user1 << endl;
  cout << user2 << endl;
  return 0;
}
