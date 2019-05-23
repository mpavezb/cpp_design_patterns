#include "Person.hpp"
#include "PersonBuilder.hpp"

using namespace std;

PersonBuilder Person::create()
{
  return PersonBuilder();
}

