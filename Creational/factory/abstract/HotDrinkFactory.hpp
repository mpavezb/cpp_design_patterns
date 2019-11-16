#pragma once
#include "HotDrink.hpp"

using namespace std;

// Abstract Factory lets us implement different factories.
struct HotDrinkFactory {
  virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory {
  unique_ptr<HotDrink> make() const override {
    // extra logic should go here
    return make_unique<Tea>();
  }
};

struct CoffeeFactory : HotDrinkFactory {
  unique_ptr<HotDrink> make() const override {
    // same
    return make_unique<Coffee>();
  }
};
