#include <string>
#include <iostream>
using namespace std;

struct Person
{
  int id;
  string name;

  Person(int id, string name): id(id), name(name)
  {
    cout << "Constructed person #" << id << " - " << name << endl;
  }
};

class PersonFactory
{
public:
  Person create_person(const string& name)
  {
    static int idxs = 0;
    Person p(idxs++, name);
    return p;
  }
};

int main()
{
  PersonFactory pf;
  auto p0 = pf.create_person("A");
  auto p1 = pf.create_person("B");
  auto p2 = pf.create_person("C");
  return 0;
}
