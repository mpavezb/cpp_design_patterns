#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum class Relationship { parent, child, sibling };

struct Person {
  string name;
};

/* Low Level Module: Storage logic/DB */
struct BadRelationships {
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person &parent, const Person &child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }
};

/* High Level Module */
struct BadResearch {
  /* Here we break the Dependency Inversion Principle
     Research (high-level) depends on Relationships (low-level)
     and even access its internal members.

     Bad things will happen if the low-level internals change.
 */
  BadResearch(BadRelationships &relationships) {
    auto &relations = relationships.relations;
    for (auto &&[first, rel, second] : relations)
      if (first.name == "John" && rel == Relationship::parent)
        cout << "John has a child called " << second.name << endl;
  }
};

/* ============================================ */
/* Better Solution                              */
/* ============================================ */
/* Introduce Abstraction and move lookup to low-level. */

struct RelationshipBrowser {
  virtual vector<Person> find_all_children_of(const string &name) = 0;
};

/* Low Level Module */
struct Relationships : RelationshipBrowser {
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person &parent, const Person &child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override {
    vector<Person> result;
    for (auto &&[first, rel, second] : relations)
      if (first.name == name && rel == Relationship::parent)
        result.push_back(second);
    return result;
  }
};

/* High Level Module */
/* Dont depend on low level implementation! */
struct Research {
  Research(RelationshipBrowser &browser) {
    for (auto &child : browser.find_all_children_of("John"))
      cout << "John has a child called " << child.name << endl;
  }
};

int main() {
  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  Relationships r;
  r.add_parent_and_child(parent, child1);
  r.add_parent_and_child(parent, child2);

  Research research(r);
  return 0;
}
