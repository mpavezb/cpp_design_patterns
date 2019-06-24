#include <string>
#include <iostream>
using namespace std;

template <typename T> struct Property
{
  T value;

  Property(T value)
  {
    // we use this to make a call to the assignment operator.
    *this = value;
  }

  operator T()
  {
    cout << "Reading!" << endl;
    return value;
  }

  T operator=(T new_value)
  {
    cout << "Assignment!" << endl;
    return value = new_value;
  }
};

struct Creature
{
  Property<int> strength{10};
  Property<int> agility{10};
};

int main()
{
  Creature c;
  c.strength = 15;
  int x = c.agility;
  return 0;
}
