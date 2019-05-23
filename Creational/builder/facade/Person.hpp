#pragma once
#include <string>
#include <iostream>

class PersonBuilder;

class Person
{
  // address
  std::string street_address, post_code, city;

  // employment
  std::string company_name, position;
  int annual_income{0};

  Person()
  {
    std::cout << "[Person Created]" << std::endl;
  }
  
public:
  ~Person()
  {
    std::cout << "[Person Destroyed]" << std::endl;
  }


  Person(Person&& other)
    : street_address{std::move(other.street_address)},
      post_code{std::move(other.post_code)},
      city{std::move(other.city)},
      company_name{std::move(other.company_name)},
      position{std::move(other.position)},
      annual_income{other.annual_income}
  {
    std::cout << "[Person Move Constructed]" << std::endl;
  }

  Person& operator=(Person&& other)
  {
    if (this == &other)
      return *this;
    street_address = std::move(other.street_address);
    post_code = std::move(other.post_code);
    city = std::move(other.city);
    company_name = std::move(other.company_name);
    position = std::move(other.position);
    annual_income = other.annual_income;
    std::cout << "[Person Move Assigned]" << std::endl;
    return *this;
  }
  
  static PersonBuilder create();

  friend std::ostream& operator<<(std::ostream &os, const Person &person)
  {
    return os << "street address: " << person.street_address << std::endl
              << "post code: " << person.post_code << std::endl
              << "city: " << person.city << std::endl
              << "company name: " << person.company_name << std::endl
              << "position: " << person.position << std::endl
              << "annual income: " << person.annual_income << std::endl;
  }
  
  // TODO
  friend class PersonBuilder;
  friend class PersonJobBuilder;
  friend class PersonAddressBuilder;
};
