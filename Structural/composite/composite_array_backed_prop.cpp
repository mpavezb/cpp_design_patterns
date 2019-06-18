#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;

// IF creature has many fields, making aggregation operations
// on them will not scale well without a refactor.
class Creature
{
private:
  // int strength;
  // int agility;
  // int spirit;
  // int cunning;
  // lots of getters, setters and complex aggregations.

  // The enum/array makes it easier to compute data aggregations.
  // The 'count' value automatically refers to the number of fields.
  //
  // The end user does not need to know about this implementation.
  enum Abilities { strength, agility, spirit, cunning, count };
  array<int, count> abilities;

public:
  int get_strength() const { return abilities[strength]; }
  void set_strength(int value) { abilities[strength] = value; }

  int get_agility() const { return abilities[agility]; }
  void set_agility(int value) { abilities[agility] = value; }

  int get_spirit() const { return abilities[spirit]; }
  void set_spirit(int value) { abilities[spirit] = value; }

  int get_cunning() const { return abilities[cunning]; }
  void set_cunning(int value) { abilities[cunning] = value; }

  int sum() const {
    return accumulate(abilities.begin(), abilities.end(), 0);
  }

  double average() const {
    return sum() / (double)count;
  }

  int max() const {
    return *max_element(abilities.begin(), abilities.end());
  }
};

int main()
{
  Creature orc;
  orc.set_strength(16);
  orc.set_agility(10);
  orc.set_spirit(5);
  orc.set_cunning(5);

  cout << "Orc has a (" << orc.sum()
       << ") stat points, with average stat (" << orc.average()
       << ") and max value (" << orc.max()
       << ")"
       << endl;
  return 0;
}
