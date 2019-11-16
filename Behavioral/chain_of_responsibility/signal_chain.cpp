#include <boost/signals2.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost::signals2;

// A query represent a single command in the chain.
// The query affects a specific creature (name) and one attribute.
struct Query {
  string creature_name;
  enum Argument { attack, defense } argument;
  int result;

  Query(const string &creature_name, const Argument argument, const int result)
      : creature_name(creature_name), argument(argument), result(result) {}
};

// User interacts with the game, which keeps all queries (Mediator pattern),
struct Game {
  // game keeps all queries.
  signal<void(Query &)> queries;
};

class Creature {
  Game &game;
  int attack, defense;

public:
  string name;
  Creature(Game &game, const string &name, const int attack, const int defense)
      : game(game), attack(attack), defense(defense), name(name) {}

  // no need for this to be virtual
  int GetAttack() const {
    // A query is made to 'query' for a specific field.
    // Then, the game resolved the query, applying all known modifiers.
    Query q{name, Query::Argument::attack, attack};
    game.queries(q);
    return q.result;
  }

  friend ostream &operator<<(ostream &os, const Creature &obj) {
    return os << "name: " << obj.name
              << " attack: " << obj.GetAttack() // note here
              << " defense: " << obj.defense;
  }
};

class CreatureModifier {
  Game &game;
  Creature &creature;

public:
  CreatureModifier(Game &game, Creature &creature)
      : game(game), creature(creature) {}

  virtual ~CreatureModifier() = default;

  // there is no handle() function
};

class DoubleAttackModifier : public CreatureModifier {
  // save connection, so we can disconnect signal later.
  connection conn;

public:
  DoubleAttackModifier(Game &game, Creature &creature)
      : CreatureModifier(game, creature) {
    // whenever someone wants this creature's attack,
    // we return DOUBLE the value
    conn = game.queries.connect([&](Query &q) {
      if (q.creature_name == creature.name &&
          q.argument == Query::Argument::attack)
        q.result *= 2;
    });
  }

  ~DoubleAttackModifier() { conn.disconnect(); }
};

// similar idea, but Query instead of Command
int main() {
  Game game;
  Creature goblin{game, "Strong Goblin", 2, 2};

  cout << goblin << endl;

  {
    // Register modifier
    DoubleAttackModifier dam{game, goblin};

    // Actually doing the query (creature.get_attack())
    cout << goblin << endl;
  }
  // Modifier disconnects when destroyed

  cout << goblin << endl;

  return 0;
}
