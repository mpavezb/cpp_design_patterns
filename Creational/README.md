# Creational Patterns

## Overview

- [Builder](#Builder): Provides an API for constructing an object step-by-step.
- [Factory](#Factory): Contruct complex objects in a wholesale way.
- [Prototype](#Prototype): Allows deep copy of prototype objects.
- [Singleton](#Singleton): Forces the use of a single instance of an object.


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

**Allows replicating a complex object**

- A prototype is a partially or fully initialized object that we (deep)copy and make use of. 
- The cloning process is made through a convenient tool (e.g., via a Factory).

**Prototype Factory**: Provides a factory that creates objects from a prototype. This can be extended, by forcing the creation of an object through the prototype, hiding the constructors.

**Prototype vie deep copy**: Implements a `deep_copy` or `clone` method on each object.

**Prototype via serialization**: Serialization is an alternative to make deep copies of an object. This way we do not write copy constructors, but we need to provide (de)serialization methods. 
- We get serialization and prototype functionality at once.
- This way, it is imposible to mess up the copy constructors!.

## Singleton

> When discussing which patterns to drop, we found that we
> still love them all. (Not really. I'm in favor of dropping
> Singleton. Its use is almost always a design smell.) 
> -- <cite>Erich Gamma</cite>

**Prevents the creation of additional copies of an instance**

For some components it only makes sense to have one instance in the system (e.g., database, factories). Contructor calls can be expensive, so we provide everyone with the same instance.

**Making a safe singleton**:
- Hide/delete the constructor, copy ctor and copy assignment operators.
- Create a static method that returns a reference to a static member.
- C++11 gives guarantees thread safe initialization of static members.

**Testability Issues**: When using a singleton to manage a resource (e.g., database), we cannot run unit test for that class, because the tests will depend on the real resource, which can change anytime!. This can be fixed with Dependency Injection, creating a interface to mock up the real resource with something suitable for testing.

**Singleton based in a DI Container**: A DI (Dependency Injection) or IoC (Inversion of Control) Container helps us to manage the lifetime of objects inside the application. This is particularily helpful, as we avoid coding the boilerplate constraints.

**Monostate Singleton**: *NOT RECOMMENDED*. The singleton is only implemented partially. The object itself is not a singleton, but only the fields used to manage the resource are kept `static`. This is a bad, because gives a wrong idea to the user of the API about how the object really works. Different instances will manage the same resource.

**Multiton**: Provides a factory to create multiple singletons for a class, based on specific keys. For example, it allows to create singletons based on levels of priority.






