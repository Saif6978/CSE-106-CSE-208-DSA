# Binomial Min-Heap: Data Structure & Amortized Priority Queue

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Advanced%20Data%20Structures-purple.svg)

## 📌 Overview

A **Binomial Heap** is an advanced priority queue data structure composed of a forest of **Binomial Trees**. While standard binary heaps require $\mathcal{O}(N)$ time to merge two heaps, Binomial Heaps support heap union in $\mathcal{O}(\log N)$ worst-case time, making them foundational in applications requiring frequent priority queue merges (e.g., parallel graph algorithms, minimum spanning forests).

This implementation provides a memory-safe, leak-free C++ Binomial Min-Heap supporting insertion, priority extraction, arbitrary key decrease, key deletion, and multi-level tree visualization.

---

## 🌲 Structural Properties of Binomial Trees

A **Binomial Tree of order $k$** (denoted $B_k$) is defined recursively:
- Order $0$ ($B_0$): A single node.
- Order $k$ ($B_k$): Formed by linking two $B_{k-1}$ trees, where the root of one becomes the leftmost child of the root of the other.

```text
B_0:   o

B_1:   o        B_2:     o             B_3:        o
       |                / \                      / | \
       o               o   o                    o  o  o
                       |                       / \ |
                       o                      o   o o
                                              |
                                              o
```

### Mathematical Invariants of $B_k$
1. **Node Count**: Exactly $2^k$ nodes.
2. **Height**: Exactly $k$.
3. **Root Degree**: Exactly $k$ children.
4. **Binomial Distribution**: The number of nodes at depth $d$ is given by the binomial coefficient $\binom{k}{d}$.

### Binomial Heap Properties
A Binomial Heap $H$ with $N$ elements satisfies:
- **Min-Heap Order**: For every tree in $H$, $\text{key}(\text{parent}) \le \text{key}(\text{child})$.
- **Uniqueness of Degree**: For any integer $k \ge 0$, there is at most one $B_k$ in $H$.
- **Binary Representation Analogy**: If $N = \sum_{i=0}^{\lfloor \log_2 N \rfloor} b_i 2^i$, then tree $B_i$ is present in $H$ if and only if bit $b_i = 1$. Consequently, $H$ contains at most $\lfloor \log_2 N \rfloor + 1$ trees.

---

## ⚙ Supported Operations & Algorithm Details

### 1. Heap Union / Merge (`merge_heap`) — $\mathcal{O}(\log N)$
The core operation of binomial heaps is structurally analogous to adding two binary numbers:
1. Merge the root lists of two heaps in monotonically non-decreasing order of degree.
2. Walk the merged list and resolve equal degrees (like handling a binary carry):
   - When two adjacent trees have the same degree $k$, compare root keys: the tree with the larger root becomes a child of the tree with the smaller root, producing a single tree of degree $k+1$.

### 2. Insert (`Insert`) — $\mathcal{O}(\log N)$ worst-case, $\mathcal{O}(1)$ amortized
Construct a single-node binomial heap $H'$ consisting of a single $B_0$, then perform `Union(H, H')`.

### 3. Find Minimum (`Find_Min`) — $\mathcal{O}(\log N)$
Scan the roots of all trees in the root list ($\le \log_2 N + 1$ roots) and return the minimum key. (Safe against empty heap queries).

### 4. Extract Minimum (`Extract_Min`) — $\mathcal{O}(\log N)$
1. Locate the root $x$ with minimum key in the root list and unlink it.
2. The children of $x$ form a collection of binomial trees $B_0, B_1, \dots, B_{k-1}$.
3. Reverse the linked list of children to form a valid binomial heap $H'$.
4. Compute `Union(H, H')` to absorb children back into the heap.

### 5. Decrease Key (`Decrease_Key`) — $\mathcal{O}(\log N)$
Decrease the key of a targeted node and bubble the value upward toward the root using parent pointers until the min-heap property is restored.

### 6. Delete Key (`Delete`) — $\mathcal{O}(\log N)$
Decrease the node's key to $-\infty$, percolating it to the root of its tree, and invoke `Extract_Min`.

---

## ⏱ Time Complexity Summary

| Operation | Binomial Heap | Standard Binary Heap | Fibonacci Heap (Amortized) |
|---|---|---|---|
| **Find Min** | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| **Extract Min** | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ |
| **Insert** | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ |
| **Union / Merge** | $\mathcal{O}(\log N)$ | $\mathcal{O}(N)$ | $\mathcal{O}(1)$ |
| **Decrease Key** | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | $\mathcal{O}(1)$ |
| **Delete** | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ |

---

## 📁 Repository Files

- [`2205119/2205119.h`](file:///home/saif/Documents/DSA/CSE%20208/Binomial%20Heap/2205119/2205119.h): Binomial Heap core class implementation with memory-leak-free pointer manipulation.
- [`2205119/2205119.cpp`](file:///home/saif/Documents/DSA/CSE%20208/Binomial%20Heap/2205119/2205119.cpp): Interactive command-line driver with null-safe lookups.
- [`2205119/2205119_file.cpp`](file:///home/saif/Documents/DSA/CSE%20208/Binomial%20Heap/2205119/2205119_file.cpp): File-based batch execution driver (`input.txt` $\to$ `output.txt`).

---

## 💻 Compilation & Execution

```bash
cd "2205119"

# Compile interactive driver
g++ -std=c++17 -Wall -Wextra -O2 2205119.cpp -o binomial_heap

# Compile batch file driver
g++ -std=c++17 -Wall -Wextra -O2 2205119_file.cpp -o binomial_heap_file

# Run interactive driver
./binomial_heap
```

### Commands in Interactive Mode
- `I <key>`: Insert integer key into heap.
- `F`: Find and print current minimum.
- `E`: Extract and remove minimum node.
- `D <old_key> <new_key>`: Decrease key from `old_key` to `new_key`.
- `R <key>`: Remove `key` from heap.
- `P`: Print structure of all binomial trees level by level.
