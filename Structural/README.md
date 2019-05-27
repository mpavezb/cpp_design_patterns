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

![adapter UML](adapter/UML.png)


We cannot modify the whole API to support a specific interface, so we adapt an existing interface X to conform to the required interface Y.

**by inheritance**: The adapter implements the required interface and also privately derives from the Adaptee class.

**by external polymorphism**: When the adaptee functionality is separated into multiple classes, the adapter can be built using pointers to each of the objects and their relevant methods.

**adapter caching**: Sometimes the conversion logic requires the execution of expensive methods to transform static data. If we expect this to be executed many times, we can implement a caché.
