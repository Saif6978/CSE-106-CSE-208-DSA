# Data Structures: Queue & Stack
### CSE 106 — Data Structures

**Author:** Saif Al Islam  
**ID:** 2205119  
**Semester:** January 2024

---

## 📚 Table of Contents

1. [Introduction](#1-introduction)
2. [Core Concepts](#2-core-concepts)
   - [Queue — FIFO](#21-queue--fifo)
   - [Stack — LIFO](#22-stack--lifo)
   - [Queue vs Stack](#23-queue-vs-stack)
3. [Implementations](#3-implementations)
   - [Array-Based Queue](#31-array-based-queue)
   - [Linked-List Queue](#32-linked-list-queue)
   - [Stack Using a Queue](#33-stack-using-a-queue)
4. [Project Structure](#4-project-structure)
5. [Offline Assignment](#5-offline-assignment)
6. [Online Problem A1A2 — Interleaving](#6-online-problem-a1a2--interleaving-two-halves-of-a-queue)
7. [Online Problem B1B2 — Palindrome](#7-online-problem-b1b2--palindrome-using-a-queue-and-stack)
8. [Online Problem C1C2 — Queue Sorting](#8-online-problem-c1c2--sorting-a-queue-using-a-stack)
9. [Complexity Summary](#9-complexity-summary)
10. [Key Takeaways](#10-key-takeaways)

---

# 1. Introduction

A **Queue** and a **Stack** are two fundamental linear data structures.

They store elements in a sequence, but they differ in **which element is removed first**:

- A **Queue** removes the element that arrived first → **FIFO**
- A **Stack** removes the element that was added most recently → **LIFO**

This project demonstrates:

- Queue implementation using a dynamic array
- Queue implementation using a linked list
- Stack implementation using a queue
- Queue-based solutions to common algorithmic problems
- Working without STL containers

> **Design principle:** The algorithms operate on the public interface of the data structures (`enqueue`, `dequeue`, `push`, `pop`, etc.) rather than depending on their internal representation.

---

# 2. Core Concepts

## 2.1 Queue — FIFO

**FIFO** means **First In, First Out**.

Think of a line at a ticket counter:

```text
                 enqueue →
        ┌─────────────────────────┐
        │ A │ B │ C │ D │
        └─────────────────────────┘
          ↑                 ↑
        front              rear

        dequeue() → removes A
```

The element at the **front** leaves first, while new elements are added at the **rear**.

### Main operations

| Operation | Purpose | Typical Complexity |
|---|---|---:|
| `enqueue(x)` | Add `x` to the rear | O(1)* |
| `dequeue()` | Remove and return the front | O(1)* |
| `peek()` | Read the front without removing it | O(1) |
| `length()` | Number of elements | O(1) |
| `isEmpty()` | Check whether the queue is empty | O(1) |
| `clear()` | Remove all elements | O(n) |

\* The exact complexity depends on the implementation used in this project.

---

## 2.2 Stack — LIFO

**LIFO** means **Last In, First Out**.

Think of a stack of plates:

```text
          ┌─────┐
          │  D  │ ← top
          ├─────┤
          │  C  │
          ├─────┤
          │  B  │
          ├─────┤
          │  A  │
          └─────┘

          pop() → removes D
```

The most recently inserted element is the first one removed.

### Main operations

| Operation | Purpose | Typical Complexity |
|---|---|---:|
| `push(x)` | Add `x` to the top | O(1)* |
| `pop()` | Remove and return the top | O(1)* |
| `top()` | Read the top without removing it | O(1) |
| `length()` | Number of elements | O(1) |
| `isEmpty()` | Check whether empty | O(1) |
| `clear()` | Remove all elements | O(n) |

\* The stack in this project is implemented **using a queue**, so its operation costs are different from a normal array/linked-list stack.

---

## 2.3 Queue vs Stack

| Property | Queue | Stack |
|---|---|---|
| Rule | FIFO | LIFO |
| Insert at | Rear | Top |
| Remove from | Front | Top |
| Example | Waiting line | Stack of plates |
| Main operations | `enqueue`, `dequeue` | `push`, `pop` |

### Easy way to remember

```text
Queue → First person enters → First person leaves
Stack → Last item placed → First item removed
```

---

# 3. Implementations

This project uses three important implementations:

1. **Dynamic Array → Queue**
2. **Linked List → Queue**
3. **Queue → Stack**

---

## 3.1 Array-Based Queue

File:

```text
QueueArray.h
```

The queue stores its elements inside a dynamically allocated array.

### Dynamic resizing

When the array becomes full:

```text
capacity = capacity × 2
```

When the queue becomes sufficiently small:

```text
if size ≤ capacity / 4
    shrink the array
```

This prevents the data structure from wasting too much memory.

### Enqueue

The implementation adds the new value at the end:

```cpp
void enqueue(int x) {
    if (size == capacity)
        resize(2 * capacity);

    array[size++] = x;
}
```

### Important limitation

The current `dequeue()` implementation shifts every remaining element one position to the left.

For example:

```text
Before dequeue:

[10][20][30][40]
 ↑
front

After dequeue:

[20][30][40]
```

Because elements are shifted, `dequeue()` is **O(n)** in this implementation.

> **Better design:** A circular array queue can avoid shifting and make both `enqueue()` and `dequeue()` amortized O(1).

---

## 3.2 Linked-List Queue

File:

```text
QueueLinkedList.h
```

A linked-list queue stores each element inside a dynamically allocated node.

Conceptually:

```text
front
  ↓
┌─────┐    ┌─────┐    ┌─────┐
│ 10  │ →  │ 20  │ →  │ 30  │ → nullptr
└─────┘    └─────┘    └─────┘
                                  ↑
                                 rear
```

The current implementation maintains a pointer to the front (`peekNode`).

### Enqueue

```cpp
void enqueue(int x) {
    Node* newNode = new Node(x);

    if (!peekNode) {
        peekNode = newNode;
    } else {
        Node* cur = peekNode;

        while (cur->next)
            cur = cur->next;

        cur->next = newNode;
    }

    currentSize++;
}
```

### Complexity note

The implementation traverses the entire list to find the last node:

```text
front → node → node → node → new node
```

Therefore:

- `enqueue()` → **O(n)**
- `dequeue()` → **O(1)** if removing from the front
- `peek()` → **O(1)**

### Possible improvement

Maintain both:

```text
front
rear
```

Then `enqueue()` can directly attach the new node to `rear`, making it **O(1)**.

---

## 3.3 Stack Using a Queue

File:

```text
StackUsingQueue.h
```

The interesting part of this project is implementing a **Stack using Queue operations**.

A queue naturally behaves like:

```text
A → B → C
↑
front
```

But a stack needs:

```text
C
↑
top
```

### Idea

Whenever a new element `x` is pushed:

1. Create a temporary queue.
2. Put `x` into the temporary queue first.
3. Move all existing elements behind `x`.
4. Move everything back.

Example:

```text
Before push(4):

Queue:
1 2 3

Push 4:

Temporary:
4

Move old elements:
4 1 2 3

Move back:
4 1 2 3
↑
front/top
```

Now `4` is at the front, so:

```text
stack.top() == 4
```

### Implementation

```cpp
void push(int x) {
    Queue temp;

    temp.enqueue(x);

    while (!que.isEmpty())
        temp.enqueue(que.dequeue());

    while (!temp.isEmpty())
        que.enqueue(temp.dequeue());
}
```

### Complexity

If the stack contains `n` elements:

- `push()` → **O(n)**
- `pop()` → **O(1)**
- `top()` → **O(1)**

This is a classic example of **changing the behavior of one data structure by building another abstraction on top of it**.

---

# 4. Project Structure

```text
Queue/
├── Assignment/
│   ├── main_array_queue.cpp
│   ├── main_list_queue.cpp
│   ├── main_queue_based_stack.cpp
│   ├── QueueArray.h
│   ├── QueueLinkedList.h
│   ├── StackUsingQueue.h
│   └── Offline_CSE106_Queue.pdf
│
└── Online/
    ├── A1A2/
    │   ├── problem.pdf
    │   └── solution.cpp
    │
    ├── B1B2/
    │   ├── problem.pdf
    │   └── solution.cpp
    │
    └── C1C2/
        ├── problem.pdf
        └── solution.cpp
```

### Dependency relationship

```text
QueueArray.h ───────────────┐
                            │
QueueLinkedList.h ──────────┼──→ Assignment / Online solutions
                            │
StackUsingQueue.h ──────────┘
          │
          └── uses QueueLinkedList.h
```

The header files form the reusable **data-structure layer**, while the `.cpp` files form the **problem-solving layer**.

---

# 5. Offline Assignment

## Objective

The offline assignment focuses on implementing:

1. Queue using a dynamic array
2. Queue using a linked list
3. Stack using a queue

The main programs demonstrate the operations and produce output based on the given input.

---

## 5.1 Array Queue — Core Idea

The array implementation focuses on:

- Dynamic memory
- Growing when full
- Shrinking when under-utilized
- Maintaining queue order

### Example

```text
Initial:

[10][20][30]

enqueue(40):

[10][20][30][40]

dequeue():

[20][30][40]
```

The implementation is straightforward, but the shifting performed during `dequeue()` makes it less efficient than a circular queue.

---

## 5.2 Linked-List Queue — Core Idea

A linked list avoids the fixed capacity limitation of arrays.

```text
10 → 20 → 30 → nullptr
↑
front
```

Adding a new node does not require moving existing elements.

However, because the current implementation searches for the tail during every `enqueue()`, insertion is O(n).

---

## 5.3 Queue-Based Stack — Core Idea

The queue is rearranged after every `push()` so that the newest item is always at the front.

```text
push(1) → [1]
push(2) → [2, 1]
push(3) → [3, 2, 1]
```

Therefore:

```text
pop() → 3
pop() → 2
pop() → 1
```

The queue has effectively been transformed into a stack.

---

# 6. Online Problem A1A2 — Interleaving Two Halves of a Queue

## Problem

Given an even number `n` of integers:

```text
a1 a2 a3 ... an/2 | b1 b2 b3 ... bn/2
```

produce:

```text
a1 b1 a2 b2 a3 b3 ...
```

### Example

```text
Input:
1 2 3 4 5 6

First half:
1 2 3

Second half:
4 5 6

Result:
1 4 2 5 3 6
```

---

## Approach

Use two queues:

```text
q1 = first half
q2 = second half
```

Then repeatedly:

```text
take from q1
take from q2
take from q1
take from q2
...
```

### Complexity

- Time: **O(n)**
- Extra space: **O(n)**

---

## Implementation

```cpp
#include "QueueLinkedList.h"
#include <iostream>

using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        Queue q1, q2;
        int mid = n / 2;

        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;

            if (i < mid)
                q1.enqueue(x);
            else
                q2.enqueue(x);
        }

        while (!q1.isEmpty() && !q2.isEmpty()) {
            cout << q1.dequeue() << " ";
            cout << q2.dequeue() << " ";
        }

        cout << '\n';
    }

    return 0;
}
```

### Sample

**Input**

```text
2
6
1 2 3 4 5 6
4
1 2 3 4
```

**Output**

```text
1 4 2 5 3 6
1 3 2 4
```

---

# 7. Online Problem B1B2 — Palindrome Using a Queue and Stack

## Problem

Determine whether a sequence is a palindrome.

A palindrome reads the same from both directions:

```text
a b c b a  → palindrome
a b b       → not a palindrome
```

The restriction allows:

- The original queue
- One additional stack
- No other data structures

---

## Key Concept

A queue gives us elements from the **front**:

```text
a → b → c → b → a
↑
front
```

A stack gives us elements from the **back**:

```text
a
b
c
b
a
↑
top
```

If we put every queue element onto a stack, the stack reverses the order.

Therefore, comparing:

```text
queue front
      ↓
a b c b a
↑
queue

with

stack top
      ↓
a b c b a
```

allows us to compare the sequence with its reverse.

---

## Preserving the Queue

A simple dequeue operation would destroy the original queue.

Instead, rotate it:

```cpp
int front = q.peek();
s.push(front);
q.enqueue(front);
q.dequeue();
```

This moves:

```text
[A B C D]
```

to:

```text
[B C D A]
```

Repeating this `n` times restores the original order.

At the same time, the stack receives:

```text
A
B
C
D
```

so its top becomes:

```text
D
```

which is exactly what we need for reverse-order comparison.

---

## Implementation

```cpp
#include <iostream>
#include "StackUsingQueue.h"

using namespace std;

bool isPalindrome(Queue& q) {
    Stack s;
    int n = q.length();

    // Store the elements in reverse order in the stack
    // while rotating the queue back to its original order.
    for (int i = 0; i < n; ++i) {
        int front = q.peek();

        s.push(front);

        q.enqueue(front);
        q.dequeue();
    }

    // Compare the original order with the reversed order.
    while (!q.isEmpty()) {
        if (s.top() != q.peek())
            return false;

        s.pop();
        q.dequeue();
    }

    return true;
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        Queue q;

        for (int i = 0; i < n; ++i) {
            char ch;
            cin >> ch;
            q.enqueue(ch);
        }

        cout << (isPalindrome(q) ? "True" : "False") << '\n';
    }

    return 0;
}
```

### Complexity

Because `StackUsingQueue::push()` is O(n):

- Building the stack: **O(n²)**
- Comparison: **O(n)**
- Total: **O(n²)**

Extra space:

- Queue + stack → **O(n)**

---

# 8. Online Problem C1C2 — Sorting a Queue Using a Stack

## Problem

Sort the queue in increasing order while respecting the restriction that only **one stack** may be used as the auxiliary data structure.

This is essentially an **insertion-sort idea expressed through queue and stack operations**.

---

## Important Idea

Process one queue element at a time.

Let:

```text
current = element removed from queue
```

If the stack contains elements smaller than `current`, move those elements back to the queue.

Then push `current` onto the stack.

### Example

Suppose:

```text
Queue: 3 1 2
Stack: empty
```

Process `3`:

```text
Stack:
3
```

Process `1`:

```text
1 < 3

Stack:
3
1
```

Process `2`:

```text
2 < 3
move 3 back to queue

Stack:
2
1
```

The stack is maintained so that its top contains the smallest currently stored element.

---

## Implementation

```cpp
#include <iostream>
#include "StackUsingQueue.h"

using namespace std;

int main() {
    Queue q;
    int x;

    while (cin >> x)
        q.enqueue(x);

    Stack s;

    while (!q.isEmpty()) {
        int current = q.dequeue();

        while (!s.isEmpty() && s.top() < current)
            q.enqueue(s.pop());

        s.push(current);
    }

    // The smallest element is at the top,
    // so popping produces increasing order.
    while (!s.isEmpty())
        q.enqueue(s.pop());

    bool first = true;

    while (!q.isEmpty()) {
        if (!first)
            cout << ' ';

        cout << q.dequeue();
        first = false;
    }

    cout << '\n';

    return 0;
}
```

### Complexity

The nested movement between the queue and stack can cause repeated processing.

In the worst case:

- Time: **O(n²)** plus the cost of `Stack::push()`
- Extra space: **O(n)**

Because the stack itself is implemented using a queue, its `push()` operation is also O(n), making this implementation potentially more expensive than a normal stack-based insertion sort.

> **Conceptual lesson:** Restrictions on available data structures can significantly change the complexity of an otherwise familiar algorithm.

---

# 9. Complexity Summary

| Structure / Algorithm | Time | Extra Space | Main Reason |
|---|---:|---:|---|
| Array `enqueue()` | O(1) amortized | O(n) | Resize only occasionally |
| Array `dequeue()` | O(n) | O(n) | Elements are shifted |
| Linked-list `enqueue()` | O(n) | O(1) per node | Traverses to tail |
| Linked-list `dequeue()` | O(1) | O(1) | Removes front node |
| Queue-based Stack `push()` | O(n) | O(n) | Reorders queue |
| Queue-based Stack `pop()` | O(1) | O(1) | Removes queue front |
| A1A2 — Interleave | O(n) | O(n) | Two queues |
| B1B2 — Palindrome | O(n²) | O(n) | Queue-based stack push |
| C1C2 — Sorting | O(n²)+ | O(n) | Repeated queue/stack movement |

> **Note:** The exact constants and worst-case behavior depend on the supplied header implementations.

---

# 10. Key Takeaways

## 10.1 Abstract Data Types

A **Queue** and a **Stack** are abstract data types.

What matters to the user of the structure is the interface:

```text
Queue:
    enqueue()
    dequeue()
    peek()

Stack:
    push()
    pop()
    top()
```

The internal implementation can change without changing the algorithm that uses the interface.

---

## 10.2 One Structure Can Simulate Another

The stack implementation demonstrates an important data-structure concept:

```text
Queue
  ↓
rearrangement
  ↓
Stack behavior
```

This idea appears frequently in computer science: a powerful abstraction can be constructed from simpler primitives.

---

## 10.3 Implementation Details Matter

Two queues can have the same abstract behavior but different performance.

For example:

```text
Linked-list queue with no tail pointer
    enqueue → O(n)

Linked-list queue with front + rear pointers
    enqueue → O(1)
```

Likewise:

```text
Array queue with shifting
    dequeue → O(n)

Circular array queue
    dequeue → O(1)
```

So **choosing the right representation is part of designing an efficient data structure**.

---

## 10.4 Restrictions Change Algorithms

The online problems demonstrate how constraints affect problem solving.

```text
Normal problem
      ↓
Use convenient data structures
      ↓
Simple algorithm

Restricted problem
      ↓
Only Queue / Stack allowed
      ↓
Need to simulate missing operations
      ↓
More complex algorithm
```

This is one of the most important lessons from these exercises.

---

# Final Summary

This project builds a small data-structure toolkit and then reuses it to solve several problems.

```text
                 DATA STRUCTURES
                       │
          ┌────────────┴────────────┐
          ↓                         ↓
       Queue                      Stack
       FIFO                       LIFO
          │                         │
     ┌────┴────┐                    │
     ↓         ↓                    │
   Array     Linked List             │
     │         │                    │
     └────┬────┘                    │
          │                         │
          └──────────┬──────────────┘
                     ↓
              Problem Solving
                     │
       ┌─────────────┼─────────────┐
       ↓             ↓             ↓
   Interleave     Palindrome      Sort
    Queues       Queue + Stack   Queue + Stack
```

The most important concepts demonstrated are:

- **FIFO vs LIFO**
- Dynamic memory management
- Array-based and linked-list implementations
- Building a stack from a queue
- Queue rotation
- Reversing data using a stack
- Insertion-sort-style processing
- Time and space complexity
- Designing algorithms under data-structure restrictions
