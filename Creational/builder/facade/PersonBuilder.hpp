#pragma once
#include "Person.hpp"

class PersonAddressBuilder;
class PersonJobBuilder;

// We use this class as a base, keeping a reference to the object.
// That is because we do not want the person to be replicated each time.
// So, the actual person is kept in the PersonBuilder, and each builder
// derives from PersonBuilderBase.
class PersonBuilderBase {
protected:
  Person &person;
  PersonBuilderBase(Person &person) : person{person} {}

public:
  operator Person() const { return std::move(person); }

  PersonAddressBuilder lives() const;
  PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
public:
  PersonBuilder() : PersonBuilderBase{p} {}

private:
  Person p;
};
