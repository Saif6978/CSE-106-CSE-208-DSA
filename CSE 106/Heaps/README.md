# 🌲 Heaps – Concepts & Problem Solutions

A collection of **Heap (Priority Queue)** implementations and greedy problem solutions in **C++**.

This repository contains:

- 📚 Heap concepts and theory
- 🛠 Assignment: Custom `MaxHeap` implementation
- 💻 Online Judge problem solutions using heaps
- 📖 Time complexity analysis and explanations

---

# 📌 What is a Heap?

A **Heap** is a specialized **Complete Binary Tree** that satisfies the **Heap Property**.

There are two common types:

## Max Heap

Every parent node is **greater than or equal to** its children.

```
        90
      /    \
    70      60
   /  \    /  \
 50  40  30  20
```

- Root always stores the **largest** element.

---

## Min Heap

Every parent node is **less than or equal to** its children.

```
        10
      /    \
    20      30
   /  \    /  \
 40  50  60  70
```

- Root always stores the **smallest** element.

---

# 📦 Array Representation

Since a heap is a **Complete Binary Tree**, it can be efficiently stored in an array.

For an element at index `i` (0-based indexing):

| Relation | Formula |
|----------|---------|
| Left Child | `2*i + 1` |
| Right Child | `2*i + 2` |
| Parent | `(i-1)/2` |

Example:

```
Heap:

        90
      /    \
    70      60
   /  \    /
 50   40  30

Array:

[90, 70, 60, 50, 40, 30]
```

---

# ⚡ Time Complexity

| Operation | Complexity |
|-----------|------------|
| Insert | **O(log n)** |
| Extract Maximum / Minimum | **O(log n)** |
| Find Maximum / Minimum | **O(1)** |
| Sift Up | **O(log n)** |
| Sift Down | **O(log n)** |
| Build Heap | **O(n)** |

---

# 🚀 Applications of Heaps

Heaps are widely used in:

- Priority Queues
- Heap Sort
- Dijkstra's Shortest Path Algorithm
- Prim's Minimum Spanning Tree
- Huffman Coding
- Scheduling Problems
- Greedy Algorithms
- Finding K Largest / Smallest Elements

---

# 📁 Project Structure

```
Heaps/
│
├── Assignment/
│   ├── MaxHeap.h
│   ├── main.cpp
│   ├── input.txt
│   └── output.txt
│
└── Online/
    ├── A1_A2/
    │   ├── problem.pdf
    │   └── solution.cpp
    │
    ├── B1_B2/
    │   ├── problem.pdf
    │   └── solution.cpp
    │
    └── C1_C2/
        ├── problem.pdf
        └── solution.cpp
```

All solution files use the custom heap implementation:

```cpp
#include "MaxHeap.h"
```

---

# 🛠 Assignment – Custom Max Heap

The assignment requires implementing a `MaxHeap` class from scratch.

## Implemented Functions

- `insert(x)`
- `findMax()`
- `extractMax()`
- `getSize()`
- `isEmpty()`
- `increaseKey(index, value)`
- `deleteKey(index)`
- `printHeap()`
- `isValidMaxHeap()`

Internal helper functions:

- `siftUp()`
- `siftDown()`

---

# 🔍 Implementation Strategy

## Insertion

1. Insert the new value at the end of the array.
2. Repeatedly swap with its parent while it is larger.
3. Heap property is restored.

```cpp
void insert(int x) {
    heap[size] = x;
    siftUp(size);
    size++;
}
```

---

## Extract Maximum

1. Save the root.
2. Replace it with the last element.
3. Decrease heap size.
4. Perform `siftDown()`.

```cpp
int extractMax() {
    int maxValue = heap[0];
    heap[0] = heap[size - 1];
    size--;
    siftDown(0);
    return maxValue;
}
```

---

## Increase Key

When a key increases, it may violate the heap property by becoming larger than its parent.

Solution:

- Update the value.
- Perform `siftUp()`.

---

## Delete Key

Deleting an arbitrary node is simplified by:

1. Increasing it to `INT_MAX`.
2. It automatically moves to the root.
3. Remove it using `extractMax()`.

This avoids implementing a separate delete routine.

---

# 💻 Online Problems

---

# A1 / A2 — Maximum Ticket Sales

## Problem

There are **M** rows of seats.

Each row initially contains `Ki` empty seats.

The price of a ticket equals the **current number of empty seats** in that row.

Exactly **N** customers buy tickets.

Find the **maximum possible revenue**.

---

## Greedy Idea

Always sell a ticket from the row with the **largest number of remaining seats**.

Why?

Selling from the largest row earns the highest possible amount at that moment while preserving optimal future choices.

A **Max Heap** lets us efficiently retrieve that row.

---

## Algorithm

1. Insert all row sizes into the heap.
2. Repeat `N` times:
   - Extract the maximum.
   - Add it to the answer.
   - Decrease it by one.
   - Insert it again if seats remain.

---

## Complexity

```
O((M + N) log M)
```

---

# B1 / B2 — Magical Bags

## Problem

There are `N` bags.

Bag `i` contains `Ai` candies.

Every minute:

- Bob chooses one bag.
- Eats all candies.
- The bag magically refills with `floor(Ai/2)` candies.

After `K` minutes, maximize the total candies eaten.

---

## Greedy Idea

Always choose the bag containing the **most candies**.

The heap ensures the largest bag is always available in `O(log N)` time.

---

## Algorithm

1. Insert every bag into the heap.
2. Repeat `K` times:
   - Extract the largest bag.
   - Add its candies to the answer.
   - Insert `x/2` back.

---

## Complexity

```
O((N + K) log N)
```

---

# C1 / C2 — Product of Three Largest Elements in Every Prefix

## Problem

For every prefix of the array:

```
A[1...i]
```

Output:

- `-1` if fewer than three elements exist.
- Otherwise, print the product of the **three largest elements**.

---

## Greedy Idea

Maintain a Max Heap containing all elements seen so far.

For every new element:

- Insert it.
- If heap size < 3 → print `-1`.
- Otherwise:
  - Extract the three largest values.
  - Compute their product.
  - Reinsert them to preserve the heap.

This keeps every prefix independent without rebuilding the heap.

---

## Complexity

Each prefix performs only three extractions and three insertions.

```
O(N log N)
```

In practice, the extra work per prefix is constant.

---

# ⚠ Common Pitfalls

### Integer Overflow

Products and sums may exceed the range of `int`.

Always use:

```cpp
long long
```

---

### Heap Capacity

`MaxHeap.h` currently uses a fixed-size array.

```cpp
const int MAX_CAPACITY = 100;
```

For larger datasets:

- Increase the capacity, or
- Replace the array with `std::vector`.

---

### Missing Header

`INT_MAX` requires:

```cpp
#include <climits>
```

Without it, compilation may fail.

---

### Reinserting Extracted Elements

In Problem **C1/C2**, after extracting the three largest values, remember to insert them back.

Otherwise, future prefixes will produce incorrect results.

---

# ✅ Conclusion

This repository demonstrates how a custom **Max Heap** can efficiently solve several classic greedy problems.

The heap provides:

- Fast insertion
- Fast removal of the maximum element
- Efficient priority-based processing

All solutions rely exclusively on heap operations, making them both efficient and easy to understand.

---

## 📚 Topics Covered

- Heap Data Structure
- Max Heap
- Priority Queue
- Greedy Algorithms
- Heap Sort Concepts
- Array-Based Binary Trees
- Competitive Programming
- C++

---

⭐ If you found this repository helpful, consider giving it a **star**!
