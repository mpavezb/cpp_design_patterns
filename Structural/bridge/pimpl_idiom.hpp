#include <string>

class Person {
public:
  std::string name;

  // impl class hides the real implementation
  class PersonImpl;
  PersonImpl *impl;

  Person();
  ~Person();

  void greet();

  // The pimpl idiom help us hide components of the API
  // we do not want to expose. Even if it is private,
  // the consumer has access to the header file.
private:
  void secret_internal_method();
};
