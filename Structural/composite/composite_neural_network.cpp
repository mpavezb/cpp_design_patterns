#include <iostream>
#include <string>
#include <vector>

using namespace std;

// THIS IS SUPPOSED TO COMPILE!

// CRTP: curiously recurring template pattern
template <typename Self> struct Connection {
  template <typename T> void connect_to(T &other) {
    for (Neuron &from : *static_cast<Self *>(this))
      for (Neuron &to : other) {
        from.out.push_back(&other);
        to.in.push_back(&from);
      }
  }
};

struct Neuron : Connection<Neuron> {
  vector<Neuron *> in, out;
  unsigned int id;

  Neuron() {
    static int id{1};
    this->id = id++;
  }

  Neuron *begin() { return this; }
  Neuron *end() { return this + 1; }

  friend ostream &operator<<(ostream &os, const Neuron &neuron) {
    for (auto n : neuron.in)
      os << n->id << "\t-->\t[" << neuron.id << "]" << endl;

    for (auto n : neuron.out)
      os << "[" << neuron.id << "]\t-->\t" << n->id << endl;

    return os;
  }
};

struct Layer : vector<Neuron>, Connection<Layer> {
  Layer(int count) {
    while (count-- > 0)
      emplace_back(Neuron{});
  }

  friend ostream &operator<<(ostream &os, const Layer &layer) {
    for (auto &n : layer)
      os << n;
    return os;
  }
};

int main() {
  // We want to use the same interface for the 4 operations below.
  Neuron n1, n2;
  Layer l1{2}, l2{3};

  n1.connect_to(n2); // 1. neuron to neuron
  n1.connect_to(l1); // 2. neuron to layer
  l1.connect_to(l2); // 3. layer to layer
  l2.connect_to(n2); // 4. layer to neuron

  cout << n1 << n2 << endl;
  cout << l1 << endl;
  return 0;
}
