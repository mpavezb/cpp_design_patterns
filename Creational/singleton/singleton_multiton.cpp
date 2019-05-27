#include <map>
#include <memory>
#include <iostream>

using namespace std;

enum class Importance
{
  primary,
  secondary,
  tertiary
};

/* Multiton class is not meant to be instanciated,
  just to be used to generate the singletons.
*/
template <typename T, typename Key = std::string>
class Multiton
{
public:
  static shared_ptr<T> get(const Key& key)
  {
    if (const auto it = instances.find(key);
        it != instances.end())
    {
      return it->second;
    }

    auto instance = make_shared<T>();
    instances[key] = instance;
    return instance;
  }
protected:
  Multiton() = default;
  virtual ~Multiton() = default;
private:
  // map of instances
  static map<Key, shared_ptr<T>> instances;
};

// initialization
template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;


// Wa want multiple singletons for printers.
class Printer
{
public:
  Printer()
  {
    ++Printer::totalInstanceCount;
    cout << "A total of "
         << Printer::totalInstanceCount
         << " instances created so far."
         << endl;
  }
private:
  static int totalInstanceCount;
};
int Printer::totalInstanceCount = 0;

int main()
{
  typedef Multiton<Printer, Importance> mt;

  auto main = mt::get(Importance::primary);
  auto sec1 = mt::get(Importance::secondary);
  auto sec2 = mt::get(Importance::secondary);
  
  return 0;
}
