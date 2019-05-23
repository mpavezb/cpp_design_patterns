#include <iostream>
#include "Person.hpp"
#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"

using namespace std;

/* 
Overview
--------

Person is a complex class and we do not want to have big constructors.

We want 2 builders: Address and Job builders.
The implementation logic requires the creation of 4 builder classes:
- PersonBuilderBase: Base class helps us to chain different types of builders.

- PersonBuilder: Only purpose is to keep the actual object.
  Other builders work using a reference to it. This way, we avoid
  multiple copies and destructions of the object in the chain.

- PersonJobBuilder: Creates job related fields.
- PersonAddressBuilder: Creates address related fields.
*/

int main()
{
  // We use multiple builders and can change from one to another.
  Person p = Person::create()
    .lives().at("Gudrunstrasse")
            .with_postcode("80364")
            .in("Munich")
    .works().at("TTTech Auto")
            .as_a("Project Engineer")
            .earning(10e6);
  
  cout << p << endl;
  return 0;
}
