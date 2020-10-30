#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// Memento Token only stores the balance.
class Memento {
  int balance;

public:
  explicit Memento(int balance) : balance(balance) {}

  // friend class so that private balance can be accessed.
  friend class BankAccount;
};

class BankAccount {
  int balance = 0;

public:
  explicit BankAccount(const int balance) : balance(balance) {}

  // Operation returns the token.
  Memento deposit(int amount) {
    balance += amount;
    return Memento{balance};
  }

  // Apply memento token.
  void restore(const Memento &m) { balance = m.balance; }

  friend ostream &operator<<(ostream &os, const BankAccount &obj) {
    return os << "balance: " << obj.balance;
  }
};

int main() {
  BankAccount ba{100};
  auto m1 = ba.deposit(50); // 150
  auto m2 = ba.deposit(25); // 175
  cout << ba << "\n";

  // undo to m1
  ba.restore(m1);
  cout << ba << "\n";

  // redo
  ba.restore(m2);
  cout << ba << "\n";

  return 0;
}
