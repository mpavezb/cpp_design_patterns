# Behavioral Patterns

## Overview

- [Chain of Responsibility](#chain-of-responsibility): Sequence of handlers processing events one after the other.
- [Commmad](#command): Encapsulate commands into separate objects.
- [Interpreter](#interpreter): Lexing and parsing structured data.
- [Iterator](#iterator): Facilitates the traversal of data structures.
- [Mediator](#mediator): TODO.
- [Memento](#memento): TODO.
- [Observer](#observer): TODO.
- [State](#state): TODO.
- [Strategy](#strategy): TODO.
- [Template Method](#template-method): TODO.
- [Visitor](#visitor): TODO.


## Chain of Responsibility

**A chain of components who all get a change to process a command, optionally having default implementations and the ability to stop the processing chain.**

![UML](chain_of_responsibility/UML.png)

Example: GUI processing of user input: Button -> Button Container -> Window frame -> Window -> Desktop. 

**(decentralized) Pointer Chain**: Linked List of commands. Each component of the chain works on the object and gives it to the next one, possibly breaking the chain. This is how this pattern used to be implemented in the past.

**(centralized) Signal Chain**: Observer pattern is used to signal components who can participate in the chain. A central component keeps a list of the elements who could be influenced by the chain. The commands are propagated (sent) to the centralized server, and used by each element to traverse the chain and apply modifications when needed.

**Broker Chain:** Chain of Responsibility + Observer + Command Query Separation.

## Command

**Encapsulate all details of an operation in a separate object. The object must define methods to apply the command, and possibly to undo or rollback.**

![UML](command/UML.png)

Example: The encapsulated action can be used to implement features like: multi-level undo/redo, macro recording, undo/redo, and having different GUI buttons generate the same commands.

**Command Query Separation**: This is not part of the Command Design Pattern. This is an architectural pattern allowing the separation of command and query concerns:
- *Command*: Asking for an action (usually a change). No return value. e.g., Please set attack to 12.
- *Query*: Asking for information (usually read-only). Return Value. e.g., Please give me your attack value.
* Both *commands* and *queries* are an instantiation of the command design pattern.

**Composite Command**: By using the composite pattern, commands can be grouped into composed commands like macros. The problem becomes difficult when trying to maintain consistency between operations: if multiple elements are affected, any failure should be properly dealt with (for instance, using rollback semantics).

Examples:
- [command](command/command.cpp)
- [command undo](command/command_undo.cpp)
- [composite command (macro)](command/composite_command.cpp)

## Interpreter

**A component that processes structured text data. Does so by turning it into separate lexical tokens (lexing) and then interpreting sequences of said tokens (parsing).**

![UML](interpreter/UML.png)

Applications:
- Parsers for compilers, interpreters, IDEs, static analysis tools.
- Matematical tools.
- Regular expressions.

Examples: [lexer_parser](interpreter/lexer_parser.cpp).


## Iterator

**A class that facilitates the traversal of a data structure. Keeps a reference to the current element and knows how to move to the next.**

![UML](iterator/UML.png)

Considerations:
- Can be used implicitly: range-based for, coroutines.

Applications:
- STL containers

Examples:
- [iterators_in_stl](iterator/iterators_in_stl.cpp)
- [binary_tree_iterator](iterator/binary_tree_iterator.cpp)
- [binary_tree_iterator_coroutines](iterator/binary_tree_iterator_coroutines.cpp)

## Mediator

**TODO: overview**
![UML](#mediator/UML.png)

Applications:
- a
- b

Examples:
- [](mediator/)

## Memento

**TODO: overview**
![UML](#memento/UML.png)

Applications:
- a
- b

Examples:
- [](memento/)

## observer

**TODO: overview**
![UML](#observer/UML.png)

Applications:
- a
- b

Examples:
- [](observer/)

## State

**TODO: overview**
![UML](#state/UML.png)

Applications:
- a
- b

Examples:
- [](state/)

## Strategy

**TODO: overview**
![UML](#strategy/UML.png)

Applications:
- a
- b

Examples:
- [](strategy/)

## Template Method

**TODO: overview**
![UML](#template/UML.png)

Applications:
- a
- b

Examples:
- [](template/)

## Visitor

**TODO: overview**

![UML](#visitor/UML.png)

Applications:
- a
- b

Examples:
- [](visitor/)
