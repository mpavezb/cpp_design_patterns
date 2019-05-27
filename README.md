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
  - [Factory](./Creational/README.md#factory)
  - [Prototype](./Creational/README.md#prototype)
  - [Singleton](./Creational/README.md#singleton)
+ [Structural Patterns](./Structural/README.md)
  - [Adapter](./Structural/README.md#adapter)
  - [Composite](./Structural/README.md#composite)
  - [Decorator](./Structural/README.md#decorator)
  - [Facade](./Structural/README.md#facade)
  - [Flyweight](./Structural/README.md#flyweight)
  - [Proxy](./Structural/README.md#proxy)
+ [Behavioral Patterns](./Behavioral/README.md)
  - [Chain of Responsibility](./Behavioral/README.md#chain-of-responsibility)
  - [Command](./Behavioral/README.md#command)
  - [Interpreter](./Behavioral/README.md#interpreter)
  - [Iterator](./Behavioral/README.md#iterator)
  - [Mediator](./Behavioral/README.md#mediator)
  - [Memento](./Behavioral/README.md#memento)
  - [Observer](./Behavioral/README.md#observer)
  - [State](./Behavioral/README.md#state)
  - [Strategy](./Behavioral/README.md#strategy)
  - [Template Method](./Behavioral/README.md#template-method)
  - [Visitor](./Behavioral/README.md#visitor)
  
## Building the code

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../bin && make
ctest --output-on-failure
make install
```
