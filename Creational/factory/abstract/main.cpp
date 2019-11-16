#include "DrinkFactory.hpp"
#include <iostream>

using namespace std;

// how would look if no factory is used.
unique_ptr<HotDrink> BAD_make_drink(string type) {
  unique_ptr<HotDrink> drink;
  if (type == "tea") {
    // specific tea preparation logic
    drink = make_unique<Tea>();
    drink->prepare(200);
  } else {
    drink = make_unique<Coffee>();
    drink->prepare(50);
  }
  return drink;
}

int main() {
  DrinkFactory df;
  auto coffee = df.make_drink("coffee");
  return 0;
}
