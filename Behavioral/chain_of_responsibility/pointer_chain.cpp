#include <iostream>
#include <string>

using namespace std;

struct Creature {
  string name;
  int attack;
  int defense;

  Creature(const string &name, int attack, int defense)
      : name(name), attack(attack), defense(defense) {}

  friend ostream &operator<<(ostream &os, const Creature &creature) {
    os << "name: " << creature.name << ", attack: " << creature.attack
       << ", defense: " << creature.defense;
    return os;
  }
};

class CreatureModifier {
  CreatureModifier *next{nullptr};

protected:
  Creature &creature;

public:
  CreatureModifier(Creature &creature) : creature(creature) {}

  // linked list of modifiers
  void add(CreatureModifier *cm) {
    if (next)
      next->add(cm);
    else
      next = cm;
  }

  // handler is meant to be overrided
  virtual void handle() {
    cout << creature << endl;
    if (next)
      next->handle();
  }
};

class DoubleAttackModifier : public CreatureModifier {
public:
  DoubleAttackModifier(Creature &creature) : CreatureModifier(creature) {}

  void handle() override {
    creature.attack *= 2;
    CreatureModifier::handle(); // !!
  }
};

class IncreaseDefenseModifier : public CreatureModifier {
public:
  IncreaseDefenseModifier(Creature &creature) : CreatureModifier(creature) {}

  void handle() override {
    if (creature.attack <= 2)
      creature.defense++;
    CreatureModifier::handle(); // !!
  }
};

class NoBonusesCurseModifier : public CreatureModifier {
public:
  NoBonusesCurseModifier(Creature &creature) : CreatureModifier(creature) {}

  void handle() override {
    // Break the chain
    // CreatureModifier::handle(); //
  }
};

int main() {
  Creature goblin{"Goblin", 1, 1};
  CreatureModifier root{goblin};
  DoubleAttackModifier d1{goblin};
  DoubleAttackModifier d2{goblin};
  DoubleAttackModifier d3{goblin};
  IncreaseDefenseModifier i1{goblin};
  IncreaseDefenseModifier i2{goblin};
  NoBonusesCurseModifier n1{goblin};

  // a=1, d=1
  root.add(&d1); // a=2, d=1
  root.add(&i1); // a=2, d=2
  root.add(&d2); // a=4, d=2
  root.add(&i2); // a=4, d=2
  root.add(&n1); // a=4, d=2
  root.add(&d3); // a=4, d=2
  root.handle();
  return 0;
}
