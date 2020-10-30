#include <iostream>
#include <string>
using namespace std;

/**
 * This is a old school implementation for state machines, relying on
 * fragile constructs:
 * - states have functions to be called.
 * - states do the transition themselves.
 * - usage of delete this.
 */

class LightSwitch;

struct State {
  virtual ~State(){};
  virtual void on(LightSwitch *) { cout << "Light is already on\n"; }
  virtual void off(LightSwitch *) { cout << "Light is already off\n"; }
};

struct OnState : State {
  OnState() { cout << "Light turned on\n"; }

  // Only off() is overriden
  void off(LightSwitch *ls) override;
};

struct OffState : State {
  OffState() { cout << "Light turned off\n"; }

  // Only on() is overriden
  void on(LightSwitch *ls) override;
};

class LightSwitch {
  State *state;

public:
  explicit LightSwitch() { state = new OffState(); }
  void set_state(State *state) { this->state = state; }
  void on() { state->on(this); }
  void off() { state->off(this); }
};

void OnState::off(LightSwitch *ls) {
  cout << "Switching light off...\n";
  ls->set_state(new OffState());
  delete this; // delete self!: red flag!
}

void OffState::on(LightSwitch *ls) {
  cout << "Switching light on...\n";
  ls->set_state(new OnState());
  delete this; // delete self!
}

int main() {
  LightSwitch ls;
  ls.on();
  ls.off();
  ls.off();
  return 0;
}
