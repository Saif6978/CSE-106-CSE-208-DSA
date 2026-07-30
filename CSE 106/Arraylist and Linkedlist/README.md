# 📚 CSE 106 – List ADT Implementation (Array List & Linked List)

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/badge/Data%20Structures-Array%20List%20%7C%20Linked%20List-success.svg" />
  <img src="https://img.shields.io/badge/Course-CSE%20106-orange.svg" />
  <img src="https://img.shields.io/badge/Institution-BUET-red.svg" />
</p>

Implementation of the **List Abstract Data Type (ADT)** using two different data structures:

- 📦 Dynamic Array (Array List)
- 🔗 Doubly Linked List

The repository contains the complete **Offline Assignment** along with **three Online Problems** that extend the base List ADT with additional operations.

---

# 👨‍💻 Author

**Saif Al Islam**  
**Student ID:** 2205119

---

# 📖 Overview

The project implements the **List ADT** twice:

- **Array List**
  - Dynamic array
  - Automatic resizing
  - Fast random access

- **Linked List**
  - Doubly linked implementation
  - Efficient insertion and deletion
  - No capacity limitation

The implementation follows the specifications of the **CSE 106 (Data Structures & Algorithms Sessional)** course offered at **Bangladesh University of Engineering and Technology (BUET)**.

---

# 📂 Repository Structure

```text
Arraylist and Linkedlist/
│
├── Assignment/
│   ├── arraylist.h
│   ├── linkedlist.h
│   ├── main.c
│   ├── in.txt
│   └── out.txt
│
├── online/
│   │
│   ├── A1A2/
│   │   ├── arraylist.h
│   │   ├── linkedlist.h
│   │   ├── A1A2.c
│   │   └── books.txt
│   │
│   ├── B1B2/
│   │   ├── arraylist.h
│   │   ├── linkedlist.h
│   │   ├── main.c
│   │   └── books.txt
│   │
│   └── C1C2/
│       ├── arraylist.h
│       ├── linkedlist.h
│       ├── C1C2.c
│       └── books.txt
│
└── README.md
```

---

# 📑 Contents

- Assignment (Offline)
- Online A1A2 – Reverse the Bookshelf
- Online B1B2 – Right-to-Left Rearrangement
- Online C1C2 – Left-to-Right Rearrangement
- Compilation
- Implementation Details

---

# 📝 Assignment (Offline)

## Objective

The objective of the offline assignment is to implement a complete **List Abstract Data Type (ADT)** that supports insertion, deletion, searching, traversal, and cursor manipulation.

The list stores integers while maintaining a **current position (cursor)** that can move throughout the list.

Two separate implementations are provided:

- **Array List**
  - Dynamic array
  - Automatic expansion and shrinking

- **Linked List**
  - Doubly linked list
  - Uses `prev` and `next` pointers

---

## Supported Operations

| No. | Function | Parameter | Description |
|----:|----------|-----------|-------------|
| 1 | `insert(value)` | int | Insert element at current position |
| 2 | `remove_at_current()` | — | Remove current element |
| 3 | `find(value)` | int | Return first occurrence index or `-1` |
| 4 | `move_to_start()` | — | Move cursor to beginning |
| 5 | `move_to_end()` | — | Move cursor to end |
| 6 | `prev()` | — | Move cursor one step left |
| 7 | `next()` | — | Move cursor one step right |
| 8 | `get_current_position()` | — | Return cursor position |
| 9 | `move_to_position(pos)` | int | Move cursor to given index |
| 10 | `get_size()` | — | Return current size |
| 11 | `get_current_element()` | — | Return element at cursor |
| 12 | `append(value)` | int | Append element at end |
| 13 | `clear()` | — | Remove all elements |
| 0 | Exit | — | Free memory and terminate |

---

## Input Format

```text
N C
element1 element2 ... elementN
F1 P1
F2 P2
...
0 0
```

Where

- **N** = Initial number of elements
- **C** = Initial capacity (ignored for Linked List)
- **F** = Function number
- **P** = Function parameter (ignored when unnecessary)

---

## Output

After every operation the program prints

- A descriptive log message
- The updated list
- The current cursor position represented by `|`

Example

```text
< 20 13 |5 7 >
```

---

# 🟦 Array List Implementation

### Features

- Dynamic array implementation
- Capacity doubles when full
- Capacity shrinks when utilization falls below 25%
- Resize operations print informative messages
- Constant-time random access

Example resize log

```text
Resized array from 10 to 20
```

---

# 🟩 Linked List Implementation

### Features

- Doubly linked nodes
- Uses

```
head
tail
current_node
current_position
```

- Efficient insertion and deletion
- Proper pointer manipulation
- No fixed capacity

---

# 📚 Online A1A2 — Reverse the Bookshelf

## Problem Description

A bookshelf contains **n** books represented by integer IDs.

The books are arranged in arbitrary order.

The objective is to **reverse the entire bookshelf** so that

- first book becomes last
- second becomes second-last
- and so on.

The cursor position is not important in this problem.

---

## New Function

```c
reverse(list)
```

---

## Implementation

### Array List

Reverse is performed by swapping elements from both ends until the middle.

Time Complexity

```
O(n)
```

---

### Linked List

The linked list is reversed by

- swapping every node's `prev` and `next`
- swapping `head` and `tail`

The cursor is restored to the same logical position after reversal.

Time Complexity

```
O(n)
```

---

## Sample

Input

```text
4
0 2 3 1
```

Output

```text
< |0 2 3 1 >

Reversed List

< |1 3 2 0 >
```

---

# 📚 Online B1B2 — Right-to-Left Rearrangement

## Problem Description

Processing starts from the **rightmost** book.

For every book exactly one operation is performed.

Available operations

- Skip
- Swap With
- Discard

After each operation the cursor moves **towards the left**.

---

## New Functions

```c
skip(list)

swap_with(list, position)

discard(list)
```

---

## Operations

### Skip

Move to the next book on the left.

---

### Swap With

Swap the current book with the book located at a specified index.

---

### Discard

Remove the current book from the shelf.

The cursor then points to the next book on the left.

---

## Cursor Direction

```text
← ← ← ←
```

Processing always moves from

```
Right → Left
```

---

## Sample

```text
< 1 3 0 |2 >

Skipped

< 1 3 |0 2 >

Swapped with position 3

< 1 3 |2 0 >

Discarded

< 1 3 |0 >
```

---

# 📚 Online C1C2 — Left-to-Right Rearrangement

## Problem Description

This problem is the opposite of **B1B2**.

Processing starts from the **leftmost** book.

Three operations are available

- Skip
- Move and Shift
- Discard

After every operation the cursor moves **towards the right**.

---

## New Functions

```c
skip(list)

move_and_shift(list, position)

discard(list)
```

---

## Operations

### Skip

Move one step to the right.

---

### Move and Shift

Remove the current element and insert it at another position.

All intermediate elements are shifted accordingly.

After insertion the cursor continues with the element that originally followed the removed one.

---

### Discard

Remove the current element.

The cursor moves to the next element on the right.

---

## Cursor Direction

```text
→ → → →
```

Processing always moves from

```
Left → Right
```

---

## Sample

```text
< |1 3 0 2 >

Skipped

< 1 |3 0 2 >

Moved to position 3

< 1 0 2 |3 >

Discarded

< 1 0 |2 >
```

---

# ⚙️ Common Implementation Details

## Cursor Management

Both implementations maintain a movable cursor.

### Array List

The cursor is stored as an integer index.

---

### Linked List

The cursor is represented using

- current node pointer
- current position

---

Whenever an operation changes the list, the cursor is updated to remain consistent.

---

## Dynamic Resizing (Array List)

Expansion

```text
size == capacity
```

```
capacity = capacity × 2
```

---

Shrinking

```text
size < capacity / 4
```

```
capacity = capacity / 2
```

The capacity never shrinks below the initial capacity.

---

## Memory Management

Before program termination,

```c
free_list();
```

is called to release all dynamically allocated memory.

---

## Switching Between Implementations

Each driver program can be compiled with either implementation.

Simply include the desired header file:

```c
#include "arraylist.h"
```

or

```c
#include "linkedlist.h"
```

No other source code changes are required.

---

# 📊 Summary

| Problem | Focus | Cursor Direction | Additional Functions |
|----------|------|-----------------|---------------------|
| Assignment | Complete List ADT | Both directions | Standard ADT operations |
| A1A2 | Reverse bookshelf | Not applicable | `reverse()` |
| B1B2 | Rearrangement | Right → Left | `skip()`, `swap_with()`, `discard()` |
| C1C2 | Rearrangement | Left → Right | `skip()`, `move_and_shift()`, `discard()` |

---

# ▶️ Compilation

## Assignment

```bash
gcc -o assignment main.c
./assignment < in.txt
```

---

## A1A2

```bash
gcc -o A1A2 A1A2.c
./A1A2
```

---

## B1B2

```bash
gcc -o B1B2 main.c
./B1B2
```

---

## C1C2

```bash
gcc -o C1C2 C1C2.c
./C1C2
```

---

# 💡 Concepts Demonstrated

- Abstract Data Types (ADT)
- Dynamic Arrays
- Array Resizing
- Doubly Linked Lists
- Pointer Manipulation
- Cursor-based Traversal
- Memory Management
- Generic Data Structure Design
- In-place List Rearrangement

---

# 📚 Course Information

| | |
|---|---|
| **Course** | CSE 106 – Data Structures & Algorithms Sessional |
| **Institution** | Bangladesh University of Engineering and Technology (BUET) |
| **Language** | C |
| **Semester** | January 2024 |

---

# 👨‍💻 Author

**Saif Al Islam**  
**Student ID:** **2205119**

---

> This repository contains my solutions for the **CSE 106 List ADT** offline assignment and online exercises. The implementations demonstrate the same abstract data type using both **Dynamic Arrays** and **Doubly Linked Lists**, highlighting the trade-offs and design considerations of each approach.
