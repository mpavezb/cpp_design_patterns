# Behavioral Patterns

## Overview

- [Chain of Responsibility](#chain-of-responsibility): Sequence of handlers processing events one after the other.
- [Commmad](#command): Encapsulate commands into separate objects.
- [Interpreter](#interpreter): Lexing and parsing structured data.
- [Iterator](#iterator): Facilitates the traversal of data structures.
- [Mediator](#mediator): Centralized communication between objects.
- [Memento](#memento): Keep a snapshot of an object's state to return later.
- [Observer](#observer): Publish and subscribe to messages.
- [State](#state): Control behavior throgh Finite State Machine.
- [Strategy](#strategy): Select exact behavior of a system at runtime or compile-time (specialization based on composition).
- [Template Method](#template-method): Define skeleton of an algorithm, with specific implementations in subclasses (specialization based on inheritance).
- [Visitor](#visitor): Tool for structure traversal that avoids modifying the whole hierarchy.


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

**Examples:**
- [command](command/command.cpp)
- [command undo](command/command_undo.cpp)
- [composite command (macro)](command/composite_command.cpp)

## Interpreter

**A component that processes structured text data. Does so by turning it into separate lexical tokens (lexing) and then interpreting sequences of said tokens (parsing).**

![UML](interpreter/UML.png)

**Applications:**
- Parsers for compilers, interpreters, IDEs, static analysis tools.
- Matematical tools.
- Regular expressions.

**Examples:** [lexer_parser](interpreter/lexer_parser.cpp).


## Iterator

**A class that facilitates the traversal of a data structure. Keeps a reference to the current element and knows how to move to the next.**

![UML](iterator/UML.png)

**Considerations:**
- Iterator implementation usually requires operations: `operator!=()`, `operator++()`, and `operator*()`.
- Iterators can be used implicitly: range-based for, coroutines.
- Iterators are used a lot in STL containers.
- Iterators can be implemented to own data structures (like a tree).
- As the `operator++()` is called sporadically, so there is no way of preserving a recursion stack. This could lead to complex iterative implementations (e.g., on trees). The coroutine module (c++20) enables the use of the easy recursive approach through generator-yielding functions (yield allows keeping the recursion stack!).

**Examples:**
- [iterators_in_stl](iterator/iterators_in_stl.cpp)
- [binary_tree_iterator](iterator/binary_tree_iterator.cpp)
- [binary_tree_iterator_coroutines](iterator/binary_tree_iterator_coroutines.cpp)
- [boost_iterator_facade](iterator/boost_iterator_facade.cpp)


## Mediator

**Facilitates communication between components, by letting them be unaware of their presence or absence in the system.**

![UML](mediator/UML.png)

**Motivation:**
- Components may go in/out of the system at any time. e.g., chat room, mmorpg.
- It makes no sense to have direct references between participants.
- A mediator component is used to mediate the connections.

**Considerations:**
- Mediator is created and usually injected into every component.
- Mediator is usually a singleton.
- Mediator provides bidirectional communication.

**Examples:**
- [chat room](mediator/main.cpp)
- [soccer_event_broker](mediator/soccer_event_broker.cpp)


## Memento

**Keep a snapshot of an object's state to return later.**

![UML](memento/UML.png)

**Motivation:**
- The command pattern allows undo/redo using commit-semantics, storing every single change!, while the memento simply saves snapshots of the system.

**Considerations:**
- A memento is a token/handler representing the system snapshot, which allows to rollback to that version. 
- This token may or may not contain system information. It may be just a hash returned by the API.
- The memento should be an inmutable object to avoid reverting to invalid states.
- Storing mementos allows using undo/redo.
- An alternative implementation could implement the "snapshot save" in the constructor of the token, and the "restore" in its destructor.

**Examples:**
- [memento snapshot](memento/memento.cpp).
- [memento with undo redo](memento/undo_redo.cpp).


## Observer

**Getting notifications on events: The observer subscribes to event notifications, which are generated by the observable.**

![UML](observer/UML.png)

**Motivation:**
- Get notifications when events happen:
  - Object's field changes.
  - Object does something.
  - External event occurs.

**Considerations**:
- Observable (publisher) implementation is always intrusive.
- Observer (doesn't need to be).
- Issues with multithreading and reentrant cases (Boost signals is not thread safe).

**Terminology:**
- *event* is *published* and received by a *subscriber*.
- *signal* is *fired* and handled by a *slot* (boost, qt, ...).

**Examples:**
- [raw_observer](observer/raw_observer.cpp)
- [boost_observer](observer/boost_observer.cpp)
- [thread_safety](observer/thread_safety.cpp)

## State

**Object behavior is determined by its state. Transitions between states are triggered explicitely or in response to events.**
![UML](state/UML.png)

**Motivation**:
- FSM: Finite State Machines.
- Changes in the state of the system can be explicit or in response to an event.
  - Explicit: FSM has explicit control of the system, quering the user about actions.
  - Responsive: FSM subscribes to events out of their control..

**Considerations**:
- Dont rely on the *old school fsm* implementation (see below). Use instead the handmade or the boost msm library.
- Complex FSM provide functions to define:
  - entry/exit behaviors for states.
  - actions when a particular event causes a transition.
  - guard conditions to enable/disable a transition.
  - default actions when no transitions are found for an event.

**Examples**:
- [old_school_fsm](state/old_school_fsm.cpp)
- [handmade_fsm](state/handmade_fsm.cpp)
- [boost meta sm](state/boost_msm.cpp)

## Strategy

**Select exact behavior of a system at runtime or compile-time.**
![UML](strategy/UML.png)

**Motivation**:
- Abstract component behavior into general (e.g., making a hot beverage) and specific (e.g., put teabag) algorithms. The general component can be reused to support more behaviors, while the specific algorithm is provided by the behavior-specific strategy.
- Specialization is done through composition.
  - High-level algorithm uses an interface.
  - Concrete implementations implement the interface.

**Considerations**:
- Also known as a *policy*.
- The dynamic approach is flexible and based on dynamic polymorphism.
- The static approach is not flexible and based on templates, but avoids pointers and runtime overhead. 

**Examples**:
- [dynamic strategy](strategy/dynamic_strategy.cpp)
- [static strategy](strategy/static_strategy.cpp)

## Template Method

**Defines the skeleton of an algorithm, with concrete implementations in subclasses.**
![UML](template/UML.png)

**Motivation**:
- Algorithms can be decomposed into common and specific components.
- Specialization is done through inheritance.
  - Overall algorithm makes use of an abstract member.
  - Inheritors override the key abstract members.
  - Parent template method is invoked.

**Examples**:
- [template method](template/template_method.cpp)

## Visitor

**A component (visitor) is allowed to traverse the inheritance hierarchy. Implemented by propagating a single visit() method through the hierarchy.**

![UML](visitor/UML.png)

**Motivation**:
- Need to define a new operation on an entire class hierarchy.
- Avoids breaking the open-closed principle: Do not want to open the hierarchy and modify every class. 
- Avoids breaking the single responsibility principle: Brand new concern should be kept separately.
- Trade-Off: Need access to the non-common aspects of classes in the hierarchy.

**Reflective Approach**: Avoid using it:
  - Forces type-checking, multiple if-else statements, and dynamic_cast.
  - Dynamic cast each component is hard and not optimal.
  - New components may not be added to the external tool!.
  - Dynamically typed languages allow using the reflective approach, avoiding its drawbacks, as the overloads are selected at runtime.

**Double Dispatch Approach**:
- The double dispatch implementation is ugly, but is **the only way** to deal with the limitations of statically typed languages in a clean manner.
- When implementing double-dispatch prefer the `accept()/visit()` convention for names.

**Cyclic vs Acyclic Visitor**:
- Cyclic: Based on function overloading, works only on a stable hierarchy.
- Acyclic visitor: based on RTTI (*run-time type information*), no hierarchy limitations, but slower.

**Multimethods - Multiple Dispatch**:
- When requiring multiple arguments for the `visit()` call, the double dispatch is not as easy as before.
- The example uses CRTP and a map between al possible overloads. Its gets complex easily, but is a way to solve multiple dispatch problems.
- See also: https://www.stroustrup.com/multimethods.pdf

**Examples**:
- [intrusive visitor](visitor/intrusive_visitor.cpp): TERRIBLE.
- [reflective visitor](visitor/reflective_visitor.cpp): NOT SO GOOD. But better for dynamically typed languages.
- [double_dispatch visitor](visitor/double_dispatch_visitor.cpp): GOOD!. For statically typed languages.
- [acyclic visitor](visitor/acyclic_visitor.cpp): GOOD when hierarchy is not fixed.
- [multimethod visitor](visitor/multimethod_visitor.cpp).
- [std variant visitor](visitor/std_variant_visitor.cpp).

