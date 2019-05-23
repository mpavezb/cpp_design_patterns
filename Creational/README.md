# Creational Patterns

## Overview

- [Builder](#Builder): Provides an API for constructing an object step-by-step.
- [Factories](#Factories):
- [Prototype](#Prototype):
- [Singleton](#Singleton):


## Builder

**The builder provides an API for constructing an object step-by-step.**

*Rationale*: Simple objects can be created in single constructor call, but complex objects require a lot of ceremony. We dont want a constructor with 10 arguments, so we use a piecewise construction.

Instead of building the object from scratch, the builder creates object oriented structures that represent each element involved.

### Fluent Builder

Chains builder calls and avoid extra code.

- Hide object constructors to force the use of the builder.
- Chaining can be done using a reference or a pointer API.
- Use Create and Build methods, before and after chaining.

### Groovy Builder

The builder pattern can be abused to create DSL that let us initialize structures in a codeless way.

### Builder Facade

This pattern help us to split a complex builder into several simpler builder classes, which can also be chained.

## Factories

## Prototype

## Singleton
