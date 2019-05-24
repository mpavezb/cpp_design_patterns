# udemy_cpp_design_patterns

Code for the Design Patterns in Modern C++ course from Udemy.

Design patterns are common architectural approaches. They were popularized by the Gang of Four book (1994) for Smalltalk and C++.

## Gamma Categorization

They are tipically split into three categories. This is called *Gamma Categorization* after Erich Gamma, one of the GoF authors.

### Creational Patterns

- Deal with the creation of objects.
- Explicit vs. Implicit: Constructor vs. [Dependency Injection, reflection, ...].
- Wholesale vs. piecewise initialization.

### Structural Patterns

- Concerned with the structure (e.g., class members).
- Many patterns are wrapers that mimic the underlying class interface.
- Stress the importance of godd API design. **Make API usable for other people**.

### Behavioral Patterns

- They are all different; no central theme.
- They solve particular problems.

## Principles and Patterns

+ [SOLID Principles](./SOLID/README.md)
  - [Single Responsibility](./SOLID/README.md#single-responsibility)
  - [Open-Closed](./SOLID/README.md#open-closed)
  - [Liskov Substitution](./SOLID/README.md#liskov-substitution)
  - [Interface Segregation](./SOLID/README.md#interface-segregation)
  - [Dependency Inversion](./SOLID/README.md#dependency-inversion)
+ [Creational Patterns](./Creational/README.md)
  - [Builder](./Creational/README.md#builder)
  - Factories
  - Prototype
  - Singleton
+ [Structural Patterns](./Structural/README.md)
  - Adapter
  - Composite
  - Decorator
  - Facade
  - Flyweight
  - Proxy
+ [Behavioral Patterns](./Behavioral/README.md)
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
  
## Building the code

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../bin && make
ctest --output-on-failure
make install
```
