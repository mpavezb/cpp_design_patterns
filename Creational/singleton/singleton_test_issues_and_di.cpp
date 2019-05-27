#include <iostream>
#include <string>
#include <map>
#include <fstream>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Database
{
public:
  virtual int get_population(const string& name) = 0;
};

class SingletonDatabase: Database
{
private:
  // private constructor
  SingletonDatabase()
  {
    cout << "Initializing the database" << endl;
    ifstream ifs("capitals.txt");

    string s, s2;
    while (getline(ifs, s))
    {
      getline(ifs, s2);
      int pop = lexical_cast<int>(s2);
      capitals[s] = pop;
    }
  }
  map<string, int> capitals;
public:
  // avoid copies of the singleton
  SingletonDatabase(const SingletonDatabase&) = delete;
  void operator=(const SingletonDatabase&) = delete;

  // provide static method to access the instance.
  static SingletonDatabase& get()
  {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const string& name)
  {
    return capitals[name];
  }
};


class DummyDatabase: public Database
{
  map<string, int> capitals;
public:
  DummyDatabase()
  {
    capitals["alpha"] = 1;
    capitals["beta"] = 2;
    capitals["gamma"] = 3;
  }
  
  int get_population(const string& name) override
  {
    return capitals[name];
  }
};

struct SingletonRecordFinder
{
  int total_population(vector<string> names)
  {
    int result{0};
    for (auto& name: names)
      result += SingletonDatabase::get().get_population(name);
    return result;
  }
};

struct ConfigurableRecordFinder
{
  Database& db;

  ConfigurableRecordFinder(Database& db): db(db) {}

  int total_population(vector<string> names)
  {
    int result{0};
    for (auto& name: names)
      result += db.get_population(name);
    return result;
  }
};



int main()
{
  // cant do this!
  //auto db = SingletonDatabase::get();
  string city = "Tokyo";
  int pop = SingletonDatabase::get().get_population(city);
  cout << city << " has a population of " << pop << endl;

  // Test depends on real resource data
  SingletonRecordFinder rf;
  vector<string> names{"Seoul", "Mexico City"};
  int tp = rf.total_population(names);
  if (tp == 1750000 + 17400000) {
    cout << "Real test passed" << endl;
  }

  // Using DI, test depends on fake data
  DummyDatabase db;
  ConfigurableRecordFinder cf{db};
  if (4 == cf.total_population(vector<string>{"alpha", "gamma"})) {
    cout << "Mock test passed" << endl;
  }
  
  return 0;
}
