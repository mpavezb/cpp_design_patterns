#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// THE LEGACY CODE:
// three totally incompatible classes with no common base class.
class LegacyA {
public:
  // no hope of polymorphism
  ~LegacyA() { cout << "LegacyA::destructor" << endl; }
  void doThis() { cout << "LegacyA::doThis()" << endl; }
};

class LegacyB {
public:
  ~LegacyB() { cout << "LegacyB::destructor" << endl; }
  void doThat() { cout << "LegacyB::doThat()" << endl; }
};

class LegacyC {
public:
  ~LegacyC() { cout << "LegacyC::destructor" << endl; }
  void doTheOther() { cout << "LegacyC::doTheOther()" << endl; }
};

// ADAPTER INTERFACE
class AdapterInterface {
public:
  virtual ~AdapterInterface() {}
  virtual void execute() = 0;
};

// ADAPTER WRAPPER
typedef shared_ptr<AdapterInterface> Adapter;

template <class T> class AdapterMapper : public AdapterInterface {
public:
  AdapterMapper(shared_ptr<T> object, void (T::*m)()) : object(object) {
    method = m;
  }
  ~AdapterMapper() {}

  // REQUIRED METHOD
  void execute() { (*object.*method)(); }

private:
  // LEGACY METHOD
  shared_ptr<T> object; // Object to wrap
  void (T::*method)();  // Specific function
};

// Helper method creates the complete wrapper of the three classes.
typedef vector<shared_ptr<AdapterInterface>> Adapters;
Adapters initialize() {
  Adapters adapters;
  adapters.emplace_back(make_shared<AdapterMapper<LegacyA>>(
      make_shared<LegacyA>(), &LegacyA::doThis));
  adapters.emplace_back(make_shared<AdapterMapper<LegacyB>>(
      make_shared<LegacyB>(), &LegacyB::doThat));
  adapters.emplace_back(make_shared<AdapterMapper<LegacyC>>(
      make_shared<LegacyC>(), &LegacyC::doTheOther));
  return adapters;
}

int main() {
  auto adapters = initialize();
  for (auto it = adapters.begin(); it != adapters.end(); ++it) {
    (*it)->execute();
  }

  return 0;
}
