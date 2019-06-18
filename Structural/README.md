# Structural Patterns

## Overview

- [Adapter](#adapter): Adapts an interface X to conform with interface Y.
- [Composite](#composite):
- [Decorator](#decorator):
- [Facade](#facade):
- [Flyweight](#flyweight):
- [Proxy](#proxy):


## Adapter

**Getting the interface you want from the interface you have**

![UML](adapter/UML.png)


We cannot modify the whole API to support a specific interface, so we adapt an existing interface X to conform to the required interface Y.

**by inheritance**: The adapter implements the required interface and also privately derives from the Adaptee class.

**by external polymorphism**: When the adaptee functionality is separated into multiple classes, the adapter can be built using pointers to each of the objects and their relevant methods.

**adapter caching**: Sometimes the conversion logic requires the execution of expensive methods to transform static data. If we expect this to be executed many times, we can implement a caché.


## Bridge

**Connecting components together through abstractions. It decouples the interface (hierarchy) from the implementation (hierarchy).**

![UML](bridge/UML.png)

Helps preventing a entity explosion on a *cartesian product*. Example: An object that supports X and Y requirements, each one with 3 different implementations, would end up with 9 versions.

**Pimpl Idiom**: This usage of the pattern helps us hidding implementation details we do not want to expose. As a side feature, as the implementation and internal signatures are hidden, this idiom allows us to change the internal implementation without touching the consumer headers. This way, we do not introduce _binary incompatibility_ and compilation times are faster.


## Composite

**Treating individual components and aggregate objects uniformly.**

Lets us group objects to make compound objects. E.g., nodes and leaves in a tree, groups of shapes. Then the individuals and groups have a common API. Both, singlular and composed objects share a similar behavior and use the same interface.

We can make use of C++ *duck typing*, expecting `begin` and `end` expressions to identify a collection.


## Decorator

**Facilitates the addition of behaviors to individual objects.**

It allows us to extend the class functionality without having to modify the internal code. Decorators can be nested.

**Dynamic Decorator**: Allows adding behavior and nesting decorators by keeping a reference to the decorated object. But, limits the object API only to the interface used by the decorators. However, this decorator is good when we do not know which decorator to use, and we want to pick them at runtime.

**Static Decorator**: When we know the decorator we want at compile time. It allows nesting and also keeping the same interface as the decorated class.

**Functional Decorator**: Applies extra features to functions.


## Façade
