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

int main() {
  BankAccount ba;
  vector<BankAccountCommand> commands{
      BankAccountCommand{ba, BankAccountCommand::deposit, 100},
      BankAccountCommand{ba, BankAccountCommand::withdraw, 200},
  };
  cout << ba << endl;
  for (auto &cmd : commands) {
    cmd.call();
  }

  // execute undo operation in reverse order.
  for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
    it->undo();
  }

  cout << ba << endl;

  return 0;
}
