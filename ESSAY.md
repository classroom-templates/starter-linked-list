# ESSAY.md — Assignment 5: Linked List

Answer all five questions completely.

Your answers should demonstrate that you understand the design and behavior of the program you submitted. Do not give generic textbook answers. Refer to your own implementation, testing, Git history, and AI use where appropriate. You must provide examples.

---

## 1. Interface-First Development

This assignment began with an existing `main.cpp`, testing framework, and expected `LinkedList` calls, but without `linkedlist.h` or `linkedlist.cpp`.

Explain how you determined the required public interface and how you approached getting the project to compile before fully implementing the LinkedList.

In your answer, discuss:

- what you learned by reading the existing calls;
- how you created and stubbed the missing module;
- why changing the supplied caller to fit your implementation would have defeated the purpose of the assignment;
- one example of a compile-time error or interface mismatch you had to resolve.

---

## 2. Dynamic Memory, Ownership, and Node Lifetime

Explain how dynamic memory is used in your LinkedList implementation.

In your answer, discuss:

- when a new Node is allocated;
- why you should not allocate a Node before you know insertion will succeed;
- which object owns each dynamically allocated Node;
- when Nodes are deleted;
- how `deleteNode()`, `clearList()`, and the destructor differ in purpose;
- how you verified that your program did not leak memory or access deleted memory.

---

## 3. Ordered Insertion and Pointer Rewiring

Describe how your `addNode()` implementation finds the correct insertion position and connects the new Node into the doubly linked list.

Use one specific example from your program where a Node is inserted:

- at the head,
- in the middle, or
- at the tail.

Explain which pointers must change and why the order of those pointer updates matters.

Also explain how your search for the insertion position allows you to detect duplicate IDs without calling `exists()` first.

---

## 4. Testing One Stateful Object

The supplied testing framework intentionally uses one `LinkedList` object through a long sequence of state transitions instead of constructing a new list for each test category.

Explain why this is a stronger test of a stateful ADT.

Then describe the student-written tests you added for:

- deletion transitions;
- clear and reuse;
- scaled stress testing.

Identify at least one bug or weakness that isolated tests on separate fresh LinkedList objects could have missed.

---

## 5. AI Use and Engineering Judgment

Describe one meaningful interaction you had with AI while completing this assignment.

Your answer must include:

- the problem, design question, or debugging issue you gave the AI;
- what the AI suggested;
- what you accepted, changed, or rejected;
- why you made that decision;
- how you verified that the final result was correct.

Do not simply say that AI generated code for you.

The purpose of this question is to show how you used AI as a programming and design tool while still exercising your own engineering judgment.
