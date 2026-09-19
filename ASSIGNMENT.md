# Assignment 5 — Linked List

## Overview

In this assignment you will implement an **ordered, doubly linked list** in C++.

This assignment is intentionally different from the previous Stack assignments.

You are being given an existing program and testing framework that **already expects** a particular `LinkedList` interface. Your job is to:

1. create the missing `LinkedList` ADT so the existing program can compile,
2. implement the linked list so it satisfies the existing calls and tests,
3. complete the intentionally unfinished portions of the test suite, and
4. verify that your dynamically allocated structure is correct, stable, and free of memory errors.

The starter project is **supposed to fail to compile when you first receive it** because `linkedlist.h` and `linkedlist.cpp` do not exist yet.

That is part of the assignment and a very common professional programming problem. Something wants to call your ADT and it's not there yet. You have to make it.

Your first task is not to start writing algorithms. Your first task is to determine the required public interface, create the missing module, and make the existing program compile.

---

# Background

This assignment combines several concepts developed across the course. Before beginning, review the following lectures and notes.

- Review the **Pointers, References, and Structured Data** lecture and notes.
- Review the **Dynamic Memory, Ownership, and Lifetime** lecture and notes.
- Review the **Linked Lists** lecture and notes.
- Review the earlier material on **interfaces, headers, implementation, and loose coupling**.
- Review the course material and previous assignments dealing with systematic **testing**.
- Watch the lecture on this assignment, **Assignment 5: Linked Lists**.

---

# Learning Objectives

By completing this assignment, you should be able to:

- implement an Abstract Data Type that conforms to an existing interface;
- distinguish public interface from private implementation;
- dynamically allocate and deallocate individual objects;
- implement and maintain a doubly linked structure;
- correctly manage head, middle, tail, and empty-list transitions;
- preserve object state when an operation fails;
- traverse a linked structure safely;
- maintain ordering and structural invariants;
- work with an existing modular testing framework;
- extend an incomplete test suite with meaningful tests;
- test one stateful object through a long sequence of transitions;
- use AddressSanitizer to detect memory-management errors;
- use Git history to document the development of a nontrivial program.

---

# Starter Files

The repository initially contains:

```text
ASSIGNMENT.md
ESSAY.md
data.h
main.cpp
main.h
test.cpp
test.h
```

You will create:

```text
linkedlist.h
linkedlist.cpp
README.md
.gitignore
```

Do **not** create a replacement `main.cpp`, testing framework, or alternate `Data` definition.

---

# Files You May Modify

## Do Not Modify

Do not modify:

```text
data.h
main.cpp
main.h
test.h
```

These files define part of the existing program you must fit your implementation into.

## `test.cpp`

`test.cpp` contains both instructor-provided tests and clearly marked sections that you are required to complete.

You may modify **only the designated incomplete student test functions**.

Do not rewrite the supplied testing architecture, alter existing instructor tests, remove calls, or change expected behavior to make an incorrect LinkedList appear correct.

## Files You Create

You are responsible for creating and implementing:

```text
linkedlist.h
linkedlist.cpp
```

You are also responsible for completing the required portions of:

```text
README.md
ESSAY.md
.gitignore
```

---

# Part 1 — Make the Existing Program Compile

The starter project will not compile because the `LinkedList` module does not exist.

**That is intentional.**

Before implementing the linked-list algorithms:

1. read `main.cpp`, `test.cpp`, and the supplied headers;
2. identify every public `LinkedList` method the existing code expects;
3. create `linkedlist.h`;
4. declare the required class and public interface;
5. create `linkedlist.cpp`;
6. provide enough stub implementations for the project to compile.

Do **not** solve this by changing the existing calls.

Your `LinkedList` must conform to the program that already exists.

This is an **interface-first** development exercise.

---

# Required Public Interface

Your `LinkedList` class **must** provide the following public interface and **no more or less**:

```cpp
LinkedList();
~LinkedList();

bool addNode(int, std::string&);
bool deleteNode(int);

bool getNode(int, Data&) const;
bool exists(int) const;

int getCount() const;
bool isEmpty() const;
bool validate() const;

void clearList();
void printList(bool = false) const;
```

Parameter names should be omitted from declarations in the header.

The exact public interface matters. Existing code already calls these methods.

---

# Required Data Type

`data.h` is provided and must not be modified.

It defines:

```cpp
struct Data {
    int id;
    std::string information;
};
```

Your linked list stores `Data` records.

---

# Required Linked-List Structure

Your implementation must be an **ordered, doubly linked list**.

Each Node must contain:

```cpp
Data data;
Node* next;
Node* prev;
```

`Node` is an implementation detail of `LinkedList`.

It must not be exposed through the public interface.

The caller works with `Data`.

The caller does **not** receive pointers or references to internal Nodes.

---

# Required Private State

The `LinkedList` object must contain **exactly one** persistent data attribute:

```cpp
Node* head;
```

Do not store:

- a node count;
- a tail pointer;
- an array of Nodes;
- an STL container;
- any other persistent representation of the list.

If a count or tail location is needed, determine it by traversal.

Private helper methods are encouraged when they improve the design, but they must not change the required public interface.

---

# Ordering Rules

Nodes must always be stored in **ascending order by `id`**.

For example, if Nodes are added in this order:

```text
30
10
50
20
40
```

the internal list must become:

```text
10 <-> 20 <-> 30 <-> 40 <-> 50
```

The caller does not choose an insertion position.

`addNode()` determines the correct position.

---

# Valid Data Rules

A Node may be added only when:

```text
id > 0
```

and the information string is not empty.

IDs must be unique.

Therefore, `addNode()` must return `false` when:

- the ID is zero;
- the ID is negative;
- the information string is empty;
- the ID already exists.

A failed insertion must not modify the existing list.

---

# Constructor

The constructor must create an empty list.

An empty list is represented by:

```cpp
head == nullptr
```

---

# Destructor

The `LinkedList` owns every Node that it dynamically allocates.

The destructor must release every remaining Node.

No Node allocated by the list may remain allocated after the `LinkedList` is destroyed.

---

# `addNode()`

```cpp
bool addNode(int, std::string&);
```

`addNode()` must:

- validate the input;
- reject duplicate IDs;
- dynamically allocate one new Node when insertion succeeds;
- place the Node in ascending ID order;
- correctly maintain both `next` and `prev` links;
- correctly handle insertion into:
  - an empty list,
  - the head position,
  - a middle position,
  - the tail position;
- return `true` only when a Node is successfully added;
- return `false` without changing the list when insertion fails.

A successful insertion must allocate an individual Node dynamically.

**Note**: You **may not** use exists() to determine if an id already exists. Using exists is redundant/inefficient logic and doubles processing for no reason. You should first look for a place to insert a node, and the act of looking for the place to insert will tell you if there is a duplicate. **Do not** allocate a node until you know you need one, and you do not know that until after you search for a position. Do not allocate a node and then delete it if you don't need it. Allocate only when you know you need a node, after you find its position and determine it is not a duplicate, and do not use exists to do this.

---

# `deleteNode()`

```cpp
bool deleteNode(int);
```

`deleteNode()` must search for the requested ID and, when found:

- reconnect neighboring Nodes correctly;
- correctly update `head` when deleting the first Node;
- correctly handle middle deletion;
- correctly handle tail deletion;
- correctly handle deletion of the only Node;
- deallocate the removed Node exactly once;
- return `true`.

If the ID does not exist:

- return `false`;
- do not modify the list.

**Note**: You **may not** use exists() to determine if an id exists. Using exists is redundant/inefficient logic and doubles processing for no reason.

---

# `getNode()`

```cpp
bool getNode(int, Data&) const;
```

`getNode()` searches by ID.

When the ID exists:

- copy the Node's `Data` into the caller-owned `Data` object;
- return `true`.

When the ID does not exist:

- return `false`;
- do **not** modify the caller's `Data` object.

Do not return a pointer or reference to internal list storage.

**Note**: You **may not** use exists() to determine if an id exists. Using exists is redundant/inefficient logic and doubles processing for no reason.

---

# `exists()`

```cpp
bool exists(int) const;
```

Return `true` when a Node with the requested ID exists.

Return `false` otherwise.

---

# `getCount()`

```cpp
int getCount() const;
```

Return the number of Nodes currently in the list.

The count must be determined by traversal.

Do not add a persistent count attribute to the class.

---

# `isEmpty()`

```cpp
bool isEmpty() const;
```

Return `true` when the list contains no Nodes.

Return `false` otherwise.

---

# `validate()`

```cpp
bool validate() const;
```

`validate()` is a structural invariant check.

It must return `true` only when the list is structurally valid.

At minimum it must verify:

1. IDs are in strictly increasing order;
2. no duplicate IDs exist;
3. every `prev` link agrees with forward traversal.

For example, if traversal reaches:

```text
A -> B
```

then:

```text
B->prev
```

must point back to `A`.

For a valid head Node:

```cpp
head->prev == nullptr
```

An empty list is valid.

This method is intentionally useful during testing. A list can appear to contain the correct Data while still having corrupted links.

---

# `clearList()`

```cpp
void clearList();
```

`clearList()` must:

- deallocate every Node;
- leave the list empty;
- leave `head == nullptr`;
- work correctly on an already empty list;
- allow the same `LinkedList` object to be used again afterward.

Calling `clearList()` does not end the lifetime of the `LinkedList` object.

---

# `printList()`

```cpp
void printList(bool = false) const;
```

When called with the default argument:

```cpp
list.printList();
```

print the list from head to tail.

When called with:

```cpp
list.printList(true);
```

print the list from tail to head.

The supplied program performs a visual verification of the output.

The expected format is demonstrated by the starter code.

`printList()` must not modify the list.

---

# Dynamic Memory Requirements

This assignment is specifically about dynamically linked objects.

Each successful insertion must dynamically allocate one Node.

Example conceptually:

```cpp
Node* node = new Node;
```

Each dynamically allocated Node must eventually be released with :

```cpp
delete
```

This assignment must **not** be implemented with:

- arrays;
- dynamically allocated arrays;
- `std::vector`;
- `std::list`;
- `std::deque`;
- another STL container;
- a collection of `Data*` objects that replaces the required Node structure.

The purpose is to implement the links yourself.

---

# Encapsulation Requirements

The public interface must deal only with normal values, references, and `Data`.

Do not expose internal memory.

The public interface must not return:

```cpp
Node*
Node&
```

or any other pointer or reference to private Node storage.

`Node` is owned by and belongs to `LinkedList`.

---

# Testing Architecture

The starter code contains a modular testing framework.

There is one especially important design rule:

> **One LinkedList object is created in `main()` and passed through the complete test suite.**

Do not replace this with a new LinkedList inside each test function.

The purpose is to test one stateful object through a long sequence of transitions.

The supplied framework begins approximately like this:

```text
new empty list
        ↓
initial-state tests
        ↓
ordered insertion and retrieval
        ↓
rejected operations against the populated list
        ↓
visual forward/reverse traversal
        ↓
student deletion tests
        ↓
student clear/reuse tests
        ↓
student stress tests
        ↓
final empty state
```

Later test groups depend on the state produced by earlier test groups.

Do not change that sequence.

---

# Instructor-Provided Tests

The supplied tests already demonstrate how to test:

- a newly constructed empty list;
- failed operations on an empty list;
- preservation of caller-owned output data after failed retrieval;
- empty-to-populated transitions;
- insertion at different structural locations;
- ordered Data retrieval;
- `exists()`;
- `getCount()`;
- invalid and duplicate insertions;
- preservation of state after failed insertion;
- repeated use of `validate()`;
- visual forward and reverse traversal.

Study these tests.

They are examples of the testing architecture you are expected to continue.

---

# Student-Written Tests

Several test functions in `test.cpp` are intentionally incomplete.

You must implement them.

Do not create a new testing system.

Extend the existing one.

**Student-written test functions that return `TestResult` must not print.** Use the supplied testing helpers and return `TestResult`. Reporting and the supplied visual `printList()` verification are handled separately by the testing framework.

Use the supplied testing helpers and return `TestResult`.

---

## Deletion Transition Tests

Complete the designated deletion test function.

The same LinkedList already contains:

```text
10 20 30 40 50
```

Your tests must take that same object through a deliberate sequence that includes:

- deleting the head;
- deleting a middle Node;
- deleting the tail;
- reaching a one-Node state;
- deleting the only remaining Node;
- reaching the empty state;
- attempting a deletion from the empty list;
- rebuilding the same object afterward.

After meaningful transitions, verify appropriate combinations of:

- return value;
- count;
- expected records;
- removed records;
- `isEmpty()`;
- `validate()`.

Do not create a replacement LinkedList.

---

## Clear and Reuse Tests

Complete the designated clear/reuse test function.

You must test a complete lifecycle transition:

```text
populated
    ↓
clear
    ↓
empty
    ↓
clear again
    ↓
still empty
    ↓
repopulate the same object
```

Verify:

- count;
- existence/nonexistence;
- empty state;
- retrieval;
- `validate()`.

The same object must remain usable after being cleared.

---

## Scaled Stress Tests

Complete the designated stress test function.

This section must be algorithmic.

Do not write dozens or hundreds of nearly identical statements.

Your test code should generate many operations **using loops**.

At minimum:

- generate many valid IDs;
- generate information values algorithmically;
- insert IDs in an order that is not already sorted;
- verify count;
- verify retrieval;
- verify existence;
- repeatedly call `validate()`;
- attempt operations that should fail;
- confirm failed operations preserve state;
- delete the records in a different order;
- return the same LinkedList object to a valid empty state.

The amount of source code should remain approximately constant even if the number of test operations is increased.

---

# Testing Philosophy

A failed operation can represent a **passed test**.

For example:

```cpp
!list.deleteNode(999)
```

is correct when ID `999` does not exist.

Testing must evaluate whether observed behavior matches expected behavior.

Do not equate:

```text
operation returned false
```

with:

```text
test failed
```

Those are different concepts.

---

# State Transitions Matter

Do not test only isolated method calls.

A linked list is a stateful object.

Your tests should ask questions such as:

- Does insertion still work after previous insertions?
- Does deletion preserve the remaining links?
- Does the list remain valid after repeatedly changing size?
- Can an object be emptied and then reused?
- Does a failed operation leave a populated list unchanged?
- Does the same object still behave correctly after many previous operations?

The complete testing sequence should **beat up one LinkedList object**, not repeatedly start over with new ones.

---

# Memory Verification

Passing functional tests is not enough.

This assignment uses dynamic memory, so your final program must also be checked for memory errors.

First compile normally:

```bash
g++ -Wall -Wextra -pedantic main.cpp linkedlist.cpp test.cpp -o linkedlist
```

Run:

```bash
./linkedlist
```

Then build with AddressSanitizer:

```bash
g++ -Wall -Wextra -pedantic -g \
    -fsanitize=address \
    main.cpp linkedlist.cpp test.cpp -o linkedlist
```

Run again:

```bash
./linkedlist
```

Your final program must complete without AddressSanitizer reporting memory errors.

Memory errors include, but are not limited to:

- leaks;
- use-after-free;
- invalid reads;
- invalid writes;
- double deletion.

---

# Course Programming Standards

All normal course programming standards apply.

In particular:

- one clear entry and exit path per ordinary function;
- one `return` statement per ordinary function where practical under the course standard;
- constructors and destructors follow normal C++ rules;
- no `while (true)`;
- no unnecessary `break`;
- no unnecessary `continue`;
- meaningful names;
- explicit logic;
- no clever shortcuts that obscure ownership or state changes;
- declarations belong in the appropriate scope;
- do not repeatedly declare the same conceptual working variable inside loop bodies;
- normal loop-control declarations such as `for (int i = ... )` are fine;
- header files define interfaces;
- implementation belongs in `.cpp` files;
- parameter names are omitted from function declarations in headers;
- modules must include their own required dependencies;
- source files include their own header.

---

# Header / Source Separation

`linkedlist.h` must define the interface.

`linkedlist.cpp` must define the implementation.

Do not place ordinary method implementations in the header.

Do not make implementation details public merely because doing so is easier.

The caller should know **what** a LinkedList can do without knowing **how** the links are managed.

---

# AI Use

AI use is required in this course.

Use AI as:

- a tutor;
- a design reviewer;
- a debugging partner;
- a source of alternative approaches;
- a critic of your testing;
- a tool for explaining behavior you do not understand.

AI does not replace your responsibility to understand the program.

You are responsible for every line you submit.

If AI suggests code or a design:

1. understand it;
2. evaluate whether it conforms to the assignment;
3. test it;
4. reject or modify it when appropriate.

Your `ESSAY.md` will require you to discuss specific AI use during this assignment.

---

# Git Requirements

Use Git throughout development.

Your history must show the development of the program over time.

Make **at least 20 meaningful program-development commits**.

Examples of meaningful commits include:

```text
Create LinkedList public interface
Stub LinkedList methods
Implement node allocation
Implement ordered insertion
Handle duplicate insertion
Implement retrieval
Implement deletion
Fix head deletion links
Implement clearList
Add structural validation
Complete deletion tests
Add clear and reuse tests
Add scaled stress tests
Fix memory error in deletion
Verify AddressSanitizer clean run
```

Do not satisfy this requirement by making meaningless commits such as:

```text
update
more work
fix
again
final
final2
```

README, ESSAY, formatting, and `.gitignore`-only commits do not substitute for the required program-development history.

Commit incrementally as the program develops.

---

# Development Strategy

A recommended development order is:

```text
1. Inspect the existing program.
2. Determine the required LinkedList interface.
3. Create linkedlist.h and linkedlist.cpp.
4. Stub the complete interface.
5. Get the entire project compiling.
6. Implement constructor / basic state.
7. Implement insertion.
8. Implement retrieval and existence.
9. Implement count / empty checks.
10. Implement deletion.
11. Implement clearList and destructor behavior.
12. Implement reverse traversal / printing.
13. Implement structural validation.
14. Make all supplied tests pass.
15. Complete the required student test groups.
16. Run the expanded test suite.
17. Run AddressSanitizer.
18. Complete README.md and ESSAY.md.
19. Review Git history.
20. Push the final repository.
```

Do not wait until the entire class is written before compiling.

---

# Final Verification

Before submitting, verify all of the following:

- `linkedlist.h` exists;
- `linkedlist.cpp` exists;
- the required public interface is exact;
- `Node` is private implementation detail;
- `head` is the only persistent LinkedList attribute;
- IDs remain ordered;
- duplicates are rejected;
- invalid data is rejected;
- both forward and backward links remain valid;
- all dynamically allocated Nodes are eventually deleted;
- supplied instructor tests pass;
- all required student test functions are complete;
- no test group reports `INCOMPLETE`;
- the same LinkedList object survives the complete test sequence;
- visual forward traversal is correct;
- visual reverse traversal is correct;
- AddressSanitizer reports no memory errors;
- no prohibited STL container is used;
- no internal Node pointer/reference is exposed publicly;
- README.md is complete;
- ESSAY.md is complete;
- `.gitignore` is appropriate;
- at least 20 meaningful program-development commits exist;
- the final repository is pushed.
- You have made a proper **README.md** and **.gitignore**.
- **There are no GitHub autograding test for this assignment. Testing is part of the assignment.**

---

# Submission

Submit the URL of your Classroom 50 / GitHub repository through Blackboard.

Your repository is the submission.

The repository must contain your final code and complete Git history.
