#include <functional>
#include <iostream>
#include <string>

using namespace std;

class RealSingleton {
private:
  // private constructor
  RealSingleton() { cout << "Creating Real Singleton." << endl; }

public:
  // avoid copies of the singleton
  RealSingleton(const RealSingleton &) = delete;
  void operator=(const RealSingleton &) = delete;

  // provide static method to access the instance.
  static RealSingleton &get() {
    static RealSingleton s;
    return s;
  }
};

class NoSingleton {
public:
  NoSingleton() { cout << "Creating normal object instance." << endl; }
};

struct SingletonTester {
  template <typename T> bool is_singleton(function<T *()> factory) {
    T *_1 = factory();
    T *_2 = factory();
    if (_1 != _2) {
      cout << "Is not singleton." << endl;
      return false;
    }
    cout << "Is singleton." << endl;
    return true;
  }
};

int main() {
  auto singleton_factory = [&]() -> RealSingleton * {
    return &RealSingleton::get();
  };
  auto object_factory = [&]() -> NoSingleton * { return new NoSingleton(); };

  SingletonTester tester;
  tester.is_singleton<RealSingleton>(singleton_factory);
  tester.is_singleton<NoSingleton>(object_factory);

  return 0;
}
