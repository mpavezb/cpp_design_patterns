# udemy_cpp_design_patterns

Code for the Design Patterns in Modern C++ course from Udemy.

## Overview

- Design patterns are common architectural approaches.
- Popularized by the Gang of Four book (1994) for Smalltalk and C++.

## Contents

+ [SOLID Principles](SOLID/README.md)
  - Single Responsibility Principle
  - Open-Closed Principle
  - Liskov Substitution Principle
  - Interface Segregation Principle
  - Dependency Inversion Principle
+ [Creational Patterns](creational/README.md)
  - Builder
  - Factories
  - Prototype
  - Singleton
+ [Structural Patterns](structural/README.md)
  - Adapter
  - Composite
  - Decorator
  - Facade
  - Flyweight
  - Proxy
+ [Behavioral Patterns](behavioral/README.md)
  - Chain of Responsibility
  - Command
  - Interpreter
  - Iterator
  - Mediator
  - Memento
  - Observer
  - State
  - Strategy
  - Template Method
  - Visitor
  
## Building

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install && make
ctest --output-on-failure
make install
```
