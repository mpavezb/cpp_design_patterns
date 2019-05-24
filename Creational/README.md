# Creational Patterns

## Overview

- [Builder](#Builder): Provides an API for constructing an object step-by-step.
- [Factory](#Factory):
- [Prototype](#Prototype):
- [Singleton](#Singleton):


## Builder

**The builder provides an API for constructing an object step-by-step.**

*Rationale*: Simple objects can be created in single constructor call, but complex objects require a lot of ceremony. We dont want a constructor with 10 arguments, so we use a piecewise construction.

Instead of building the object from scratch, the builder creates object oriented structures that represent each element involved.

**Tips**:
- You can give the builder a constructor or return it via a static function from the object you are trying to build.
- Hide object constructors to force the use of the builder.

**Fluent Builder**: Chains builder calls and avoid extra code.
- Chaining can be done using a reference or a pointer API.
- Use Create and Build methods, before and after chaining.

**Groovy Builder**: The builder pattern can be abused to create DSL that let us initialize structures in a codeless way.

**Builder Facade**: This pattern help us to split a complex builder into several simpler builder classes, which can also be chained.


## Factory

**A component responsible solely for the wholesale (not piecewise) creation of objects**

Object creation logic is too complex for a single constructor. We want to avoid multiple complex constructors and optional parameters. Outsource object creation logic (non-piecewise, unlike Builder).

**Factory Method**: Provide static methods to build the object.

**Factory**: Provide the factory as a separate class as an alternative for construction.

**Inner Factory**: Force the use of the factory while providing a cleaner API.

**Abstract Factory**: Hierarchy of factories that handle the creation of a hierarchy of objects.



## Prototype

## Singleton
