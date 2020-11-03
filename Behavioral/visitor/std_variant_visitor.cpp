#include <iostream>
#include <string>
#include <variant>

using namespace std;

// Visitor must overload the operator().
struct AddressPrinter {
  void operator()(const string &house_name) const {
    cout << "A house called " << house_name << "\n";
  }

  void operator()(const int house_number) const {
    cout << "House number " << house_number << "\n";
  }
};

int main() {

  // Visitor
  AddressPrinter ap;

  // Visitable: Variant representing a House by number of name
  std::variant<string, int> house;

  house = "Montefiore Castle";
  std::visit(ap, house); // std::visit(visitor, visitable).

  house = 221;
  std::visit(ap, house); // std::visit(visitor, visitable).

  // Construct visitor in-place.
  std::visit(
      [](auto &arg) {
        using T = decay_t<decltype(arg)>;

        // type is unknown so it must be figured out.
        // and checked against valid ones.
        if constexpr (is_same_v<T, string>) {
          cout << "A house called " << arg.c_str() << "\n";
        } else {
          cout << "House number " << arg << "\n";
        }
      },
      house);

  return 0;
}
