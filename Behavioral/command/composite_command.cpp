#include <initializer_list>
#include <iostream>
#include <vector>

using namespace std;

struct BankAccount {
  int balance{0};
  int overdraft_limit{-500};

  void deposit(int amount) {
    balance += amount;
    cout << "deposited " << amount << ", balance is now " << balance << "\n";
  }

  bool withdraw(int amount) {
    if (balance - amount >= overdraft_limit) {
      balance -= amount;
      cout << "withdrew " << amount << ", balance is now " << balance << "\n";
      return true; // Required to know if operation succeeded.
    }
    return false;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const BankAccount &account) {
    os << "balance: " << account.balance;
    return os;
  }
};

struct Command {
  bool succeeded{false};
  virtual void call() = 0;
  virtual void undo() = 0;
};

struct BankAccountCommand : Command {
  BankAccount &account;
  enum Action { deposit, withdraw } action;
  int amount;

  BankAccountCommand(BankAccount &account, Action action, int amount)
      : account{account}, action{action}, amount{amount} {}

  void call() override {
    switch (action) {
    case deposit:
      account.deposit(amount);
      succeeded = true;
      break;
    case withdraw:
      succeeded = account.withdraw(amount);
      break;
    }
  }

  void undo() override {
    if (!succeeded) {
      return;
    }

    switch (action) {
    case deposit:
      account.withdraw(amount);
      break;
    case withdraw:
      // Dealing with this case forces us to break the open-closed principle,
      // as we need information on whether the operation succeeded.
      // This can be done by having access to a boolean value on the account.
      account.deposit(amount);
      break;
    }
  }
};

/**
 * This CompositeBankAccountCommand is equivalent to a macro (vector of
 * commands), which is also a command providing call() and undo() methods.
 */
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command {

  explicit CompositeBankAccountCommand(
      const initializer_list<BankAccountCommand> &items)
      : vector(items) {}

  void call() override {
    for (auto &cmd : *this) {
      cmd.call();
    }
  }

  void undo() override {
    for (auto it = rbegin(); it != rend(); ++it) {
      it->undo();
    }
  }
};

/**
 * This intermediate class with this call() implementation is needed to
 * maintain consistency between multiple commands when failure is possible.
 */
struct DependentCompositeCommand : CompositeBankAccountCommand {
  explicit DependentCompositeCommand(
      const initializer_list<BankAccountCommand> &items)
      : CompositeBankAccountCommand(items) {}

  // This implementation only cares about stopping the pipeline on failure.
  // A better implementation can implement rollback semantics, to undo all
  // operations.
  void call() override {
    bool ok = true;
    for (auto &cmd : *this) {
      // As soon as a command fails:
      // - next commands wont be executed.
      // - next commands are marked as failed.
      if (ok) {
        cmd.call();
        ok = cmd.succeeded;
      } else {
        cmd.succeeded = false;
      }
    }
  }
};

/**
 * Transfer is modeled as a withdrawal + deposit
 */
struct MoneyTransferCommand : DependentCompositeCommand {
  explicit MoneyTransferCommand(BankAccount &from, BankAccount &to, int amount)
      : DependentCompositeCommand({
            BankAccountCommand{from, BankAccountCommand::withdraw, amount},
            BankAccountCommand{to, BankAccountCommand::deposit, amount},
        }) {}
};

int main() {
  BankAccount ba;
  BankAccount ba2;

  ba.deposit(100);
  auto cmd1 = MoneyTransferCommand(ba, ba2, 25);
  cmd1.call();
  cmd1.undo();
  cout << ba << " - " << ba2 << endl;

  cout << endl;

  auto cmd2 = MoneyTransferCommand(ba, ba2, 5000);
  cmd2.call();
  cout << ba << " - " << ba2 << endl;
  cmd2.undo();
  cout << ba << " - " << ba2 << endl;

  return 0;
}
