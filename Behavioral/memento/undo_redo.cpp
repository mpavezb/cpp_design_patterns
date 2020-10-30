#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Memento {
  int balance;

public:
  explicit Memento(int balance) : balance(balance) {}
  friend class BankAccount;
};

// supports undo/redo
class BankAccount {
  int balance = 0;

  // save every snapshot commit
  vector<shared_ptr<Memento>> changes;
  size_t current;

public:
  explicit BankAccount(const int balance) : balance(balance) {
    changes.emplace_back(make_shared<Memento>(balance));
    current = 0;
  }

  shared_ptr<Memento> deposit(int amount) {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
  }

  void restore(const shared_ptr<Memento> &m) {
    if (m) {
      balance = m->balance;
      changes.push_back(m);
      current = changes.size() - 1;
    }
  }

  shared_ptr<Memento> undo() {
    if (current > 0) {
      --current;
      auto m = changes[current];
      balance = m->balance;
      return m;
    }
    return {};
  }

  shared_ptr<Memento> redo() {
    if (current + 1 < changes.size()) {
      ++current;
      auto m = changes[current];
      balance = m->balance;
      return m;
    }
    return {};
  }

  friend ostream &operator<<(ostream &os, const BankAccount &obj) {
    return os << "balance: " << obj.balance;
  }
};

int main() {
  BankAccount ba{100};
  ba.deposit(50);
  ba.deposit(25); // 125
  cout << ba << "\n";

  ba.undo();
  cout << "Undo 1: " << ba << "\n";
  ba.undo();
  cout << "Undo 2: " << ba << "\n";
  ba.redo();
  cout << "Redo 2: " << ba << "\n";
  ba.undo();
  cout << "Undo 3: " << ba << "\n";
  return 0;
}
