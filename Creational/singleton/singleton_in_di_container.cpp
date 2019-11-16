#include <iostream>
#include <memory>
#include <string>

#include <boost/lexical_cast.hpp>
// <boost/di.hpp> from boost experimental
#include "di.hpp"

using namespace std;
using namespace boost;

/* IFoo is the singleton interface */
struct IFoo {
  virtual string name() = 0;
};

/* Foo is the actual singleton
We dont have to define the singleton explicitely by
hiding the constructors and providing get methods.
*/
struct Foo : IFoo {
  // we use this only to show this object is created only once
  static int id;
  Foo() { ++id; }

  string name() override { return "foo "s + lexical_cast<string>(id); }
};
int Foo::id = 0;

/* Bar will get Foo injected automatically as
   a singleton by the di container. */
struct Bar {
  std::shared_ptr<IFoo> foo;
};

int main() {
  // use di container to manage the lifetime of
  // Foo as a singleton.
  auto injector =
      di::make_injector(di::bind<IFoo>().to<Foo>().in(di::singleton));

  // create 2 bars, injecting the singleton to both.
  auto bar1 = injector.create<std::shared_ptr<Bar>>();
  auto bar2 = injector.create<std::shared_ptr<Bar>>();

  cout << bar1->foo->name() << endl;
  cout << bar2->foo->name() << endl;

  // both bar objects have a reference to the same object
  cout << boolalpha << (bar1->foo.get() == bar2->foo.get()) << endl;

  return 0;
}
