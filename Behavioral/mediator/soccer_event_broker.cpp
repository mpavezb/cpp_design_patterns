#include <iostream>
#include <string>
#include <vector>
struct Game;
using namespace std;

#include <boost/signals2.hpp>
using namespace boost::signals2;

/**
 * Obserser + Mediator pattern
 * Coach is notified whenever a football player scores.
 */

struct EventData {
  virtual ~EventData() = default;
  virtual void print() const = 0;
};

struct Player;
struct PlayerScoredData : EventData {
  string player_name;
  int goals_scored_so_far;

  PlayerScoredData(const string &player_name, const int goals_scored_so_far)
      : player_name(player_name), goals_scored_so_far(goals_scored_so_far) {}

  void print() const override {
    cout << player_name << " has scored! (their " << goals_scored_so_far
         << " goal)"
         << "\n";
  }
};

// MEDIATOR
struct Game {
  signal<void(EventData *)> events; // observer
};

// PARTICIPANT which sends signals
struct Player {
  string name;
  int goals_scored = 0;
  Game &game; // REFERENCE TO MEDIATOR

  Player(const string &name, Game &game) : name(name), game(game) {}

  void score() {
    goals_scored++;
    PlayerScoredData ps{name, goals_scored};
    game.events(&ps); // SIGNAL MEDIATOR
  }
};

// PARTICIPANT SUBSCRIBED TO THE SIGNAL
struct Coach {
  Game &game;

  explicit Coach(Game &game) : game(game) {
    // celebrate if player has scored <3 goals
    game.events.connect([](EventData *e) {
      PlayerScoredData *ps = dynamic_cast<PlayerScoredData *>(e);
      if (ps && ps->goals_scored_so_far < 3) {
        cout << "coach says: well done, " << ps->player_name << "\n";
      }
    });
  }
};

int main() {
  Game game;
  Player player{"Sam", game};
  Coach coach{game};

  player.score();
  player.score();
  player.score(); // ignored by coach

  return 0;
}
