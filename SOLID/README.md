# SOLID Design Principles

Useful principles of Obejct Oriented Design. These were introduced by Uncle Bob (Robert C. Martin).

## The SOLID Principles

### Single Responsibility

**Separation of Concerns**: A class should have a single reason to change. 

### Open-Closed

The system should be **open to extension and closed to modification**.

- We want to avoid modifying code that already works.
- Extension can be done by inheritance.

### Liskov Substitution

Subtypes should be inmediatly substitutable by their base types.

- Methods designed to work on the Base class should keep working
  when a Derived instance is used.
- Named after Robert Liskov.

### Interface Segregation

Don't force implementers to code too large interfaces.

- Partial implementers contain dummy methods and extra code.
- Partial implementers give a wrong API to the user.


### Dependency Inversion



