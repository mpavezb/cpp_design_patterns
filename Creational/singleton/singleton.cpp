#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class SingletonDatabase {
private:
  // private constructor
  SingletonDatabase() {
    cout << "Initializing the database" << endl;
    ifstream ifs("capitals.txt");

    string s, s2;
    while (getline(ifs, s)) {
      getline(ifs, s2);
      int pop = lexical_cast<int>(s2);
      capitals[s] = pop;
    }
  }
  map<string, int> capitals;

public:
  // avoid copies of the singleton
  SingletonDatabase(const SingletonDatabase &) = delete;
  void operator=(const SingletonDatabase &) = delete;

  // provide static method to access the instance.
  static SingletonDatabase &get() {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const string &name) { return capitals[name]; }
};

int main() {
  // cant do this!
  // auto db = SingletonDatabase::get();
  string city = "Tokyo";
  int pop = SingletonDatabase::get().get_population(city);
  cout << city << " has a population of " << pop << endl;
  return 0;
}
