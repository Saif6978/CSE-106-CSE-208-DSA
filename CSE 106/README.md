# CSE 106: Data Structures & Algorithms I Sessional

![C](https://img.shields.io/badge/Language-C11-blue.svg?logo=c)
![C++](https://img.shields.io/badge/Language-C++17-blue.svg?logo=c%2B%2B)
![Course](https://img.shields.io/badge/Course-CSE%20106-orange.svg)
![Institution](https://img.shields.io/badge/Institution-BUET-red.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg)
![Compilation](https://img.shields.io/badge/Compilation-100%25%20Passing%20(0%20warnings)-brightgreen.svg)

A complete, production-grade repository containing all laboratory assignments, online assessments, and data structure implementations for **CSE 106: Data Structures and Algorithms I Sessional** at the **Bangladesh University of Engineering and Technology (BUET)**.

Every implementation is written in clean, idiomatic C/C++, compiles without errors or warnings (`-Wall -Wextra`), manages dynamic memory safely (zero leaks, protected boundary conditions), and includes comprehensive documentation.

---

## 📚 Master Table of Contents

| # | Topic | Folder | Core Concepts & Data Structures | Language | Paradigm |
|---|---|---|---|---|---|
| 01 | **List ADT** | [`Arraylist and Linkedlist/`](./Arraylist%20and%20Linkedlist) | Dynamic Resizing Array, Doubly Linked List, Cursor Navigation | C | Abstract Data Types |
| 02 | **Array Algorithms** | [`Arrays/`](./Arrays) | Triplet Sums, Inversion Counting, Second Largest Distinct Elements | C | Linear Scanning |
| 03 | **Binary Search Tree** | [`Binary Search Tree/`](./Binary%20Search%20Tree) | BST Insert, Delete (3 Cases), LCA, Range Query, Parentheses Tree | C++ | Hierarchical Trees |
| 04 | **Divide & Conquer** | [`Divide and Conquer/`](./Divide%20and%20Conquer) | Maximum Subarray Streak, Boundary Crossings, Inversions (Merge Sort) | C++ | Divide & Conquer |
| 05 | **Dynamic Programming** | [`Dynamic Programming/`](./Dynamic%20Programming) | Regex Matching, Knapsack + House Robber, Edit Distance, LCS | C++ | Dynamic Programming |
| 06 | **Graph Algorithms** | [`Graphs/`](./Graphs) | Adjacency Matrix BFS, Adjacency List DFS, Grid Traversal, Kahn's Algo | C++ | Graph Traversal |
| 07 | **Greedy Algorithms** | [`Greedy/`](./Greedy) | Manhattan Distance MST, Prim's Algorithm on Complete Graphs | C++ | Greedy Optimization |
| 08 | **Binary Heaps** | [`Heaps/`](./Heaps) | Custom Max-Heap, Sift-Up/Down, Priority Queues, Prefix Max Products | C++ | Tree-Based Queues |
| 09 | **Queue ADT** | [`Queue/`](./Queue) | Circular/Dynamic Array Queue, Linked Queue, Stack-via-Queue | C++ | FIFO Structures |
| 10 | **Stack ADT** | [`Stack/`](./Stack) | Array/List Stacks, Monotonic Stack, Auxiliary Sort, Recursion Sim | C++ | LIFO Structures |

---

## 🧠 Comprehensive Topic & Problem Summaries

### 1. [Arraylist and Linkedlist](./Arraylist%20and%20Linkedlist)
- **Core Concept**: Dual implementation of the **List Abstract Data Type (ADT)**.
  - **Array List**: Dynamic continuous memory, doubles on full (`size == capacity`), shrinks when utilization drops below 25% (`size < capacity / 4`). Constant-time indexing $\mathcal{O}(1)$.
  - **Linked List**: Doubly linked nodes (`prev`, `next`, `head`, `tail`) with bidirectional cursor navigation. Insertion/deletion at cursor takes $\mathcal{O}(1)$ pointer operations.
- **Problem Variations**:
  - **Assignment**: Full 13-function interactive driver (`insert`, `remove_at_current`, `find`, `move_to_position`, `append`, etc.).
  - **Online A1A2**: Bookshelf reversal in $\mathcal{O}(n)$ time by pointer swapping (`prev` $\leftrightarrow$ `next`) in linked list and two-pointer swap in array list.
  - **Online B1B2**: Right-to-left rearrangement supporting `skip`, `swap_with(pos)`, and `discard` with backward cursor propagation.
  - **Online C1C2**: Left-to-right rearrangement supporting `skip`, `move_and_shift(pos)`, and `discard` with forward cursor preservation.

### 2. [Arrays](./Arrays)
- **Core Concept**: Fundamental sequential data access, in-place traversals, and dynamic heap allocation in C.
- **Problem Variations**:
  - **Online A1A2 (Maximum Triplet Sum)**: Finds the contiguous 3-element window with maximum sum in $\mathcal{O}(n)$ time and $\mathcal{O}(1)$ space; tie-breaking chooses the rightmost triplet using `>=`.
  - **Online B1B2 (Count Inversions)**: Counts pairs $(i, j)$ with $i < j$ and $arr[i] > arr[j]$ using brute-force comparison.
  - **Online C1C2 (Second Largest Element)**: Two-pass linear search finding the maximal element strictly smaller than the absolute maximum; handles identical elements safely.

### 3. [Binary Search Tree](./Binary%20Search%20Tree)
- **Core Concept**: Ordered binary tree where for every node $x$, $\text{keys}(\text{left}) < \text{key}(x) < \text{keys}(\text{right})$.
- **Key Mechanics**:
  - **Deletion (3 Cases)**: Leaf deletion, single-child splice, and two-child substitution via in-order successor.
  - **Tree Serialization**: Custom parentheses representation `value(left, right)` with `_` for null subtrees.
- **Problem Variations**:
  - **Assignment**: Complete BST with traversals (In-order, Pre-order, Post-order), insertion, deletion, and formatted printing.
  - **Online A1A2 (Lowest Common Ancestor)**: Exploits BST order to find LCA of values $u, v$ in $\mathcal{O}(h)$ time without auxiliary storage.
  - **Online B1B2 (Second Largest Node)**: Locates the rightmost node; returns its in-order predecessor (either the largest node in its left subtree or its parent).
  - **Online C1C2 (Count in Range)**: Pruned branch search counting nodes in $[low, high]$ in $\mathcal{O}(h + k)$ time.

### 4. [Divide and Conquer](./Divide%20and%20Conquer)
- **Core Concept**: Recursive problem decomposition into independent subproblems, conquering subproblems recursively, and recombining solutions across boundaries.
- **Problem Variations**:
  - **Assignment (Shortest Hottest Streak)**: Maximum Subarray Problem solved in $\mathcal{O}(n \log n)$ via divide-and-conquer; custom tie-breaking favors shorter streaks.
  - **Online A1A2 (Adjacent Inverted Pairs)**: Counts boundary inversions $(s[i] > s[i+1])$ by splitting recursively and testing the single midpoint pair $s[mid] > s[mid+1]$ in $\mathcal{O}(n)$ total time.
  - **Online B1B2 (Unique Elements in Sorted Array)**: Counts identical adjacent pairs across the recursion boundary to determine distinct count ($n - \text{duplicates}$) in $\mathcal{O}(n)$ time.
  - **Online C1C2 (Inversion Count via Merge Sort)**: Counts global inversions in $\mathcal{O}(n \log n)$ time by tallying cross-inversions (`mid - i + 1`) during the merge phase.

### 5. [Dynamic Programming](./Dynamic%20Programming)
- **Core Concept**: Overcoming exponential recursion through memoization (top-down) and tabulation (bottom-up) by identifying optimal substructure and overlapping subproblems.
- **Problem Variations**:
  - **Assignment (Regular Expression Matching)**: Top-down 2D memoized matcher supporting literal characters, wildcard `.`, Kleene star `*` (zero-or-more), and plus `+` (one-or-more) in $\mathcal{O}(|s| \times |p|)$ time.
  - **Online A1A2 (Knapsack + House Robber)**: 0/1 Knapsack optimization with the non-adjacent house constraint ($DP[i][w] = \max(DP[i-1][w], DP[i-2][w - wt_i] + val_i)$).
  - **Online B1B2 (Edit Distance / Levenshtein)**: Computes minimum insertions, deletions, and substitutions converting string $X \to Y$ in $\mathcal{O}(|X| \times |Y|)$ time.
  - **Online C1C2 (Longest Common Subsequence)**: Classical 2D DP finding length and elements of the longest common subsequence in $\mathcal{O}(n \times m)$ time.

### 6. [Graphs](./Graphs)
- **Core Concept**: Modeling entities and relationships; exploring traversals, connectivity, reachability, and topological ordering.
- **Problem Variations**:
  - **Assignment (Space Stations)**: Connected components detection using both Adjacency Matrix (BFS) and Adjacency List (DFS); minimum bridges required to connect all components is $K - 1$.
  - **Online A1A2 (Prerequisite Courses)**: Reverse graph construction ($B \to A$) allowing a single BFS/DFS from target course $C$ to discover all transitive prerequisites in $\mathcal{O}(N + M)$ time.
  - **Online B1B2 (Prison Escape)**: 2D grid graph traversal from starting cell $S$ navigating around obstacles `#` to count reachable exit cells $E$.
  - **Online C1C2 (Module Dependencies)**: Cycle detection in directed graphs using **Kahn's Algorithm** (in-degree tracking queue) in $\mathcal{O}(N + M)$ time.

### 7. [Greedy Algorithms](./Greedy)
- **Core Concept**: Making locally optimal choices at each step to reach a global optimum; leveraging the **Cut Property** of Minimum Spanning Trees.
- **Problem**: **Connecting Points with Manhattan Distance**:
  - Vertices are 2D points $(x_i, y_i)$; edge weights are Manhattan distances $|x_1 - x_2| + |y_1 - y_2|$.
  - Models the problem as an implicit complete graph with $\frac{n(n-1)}{2}$ edges.
  - Applies **Prim's Algorithm** with an active distance array, computing weights on the fly to achieve $\mathcal{O}(n^2)$ time with only $\mathcal{O}(n)$ space without materializing all edges.

### 8. [Binary Heaps](./Heaps)
- **Core Concept**: Complete binary tree maintaining the **Heap Property** ($parent \ge child$ for max-heap), stored compactly in an array with 0-based indexing ($left = 2i+1, right = 2i+2, parent = \lfloor (i-1)/2 \rfloor$).
- **Key Operations**: `siftUp` and `siftDown` in $\mathcal{O}(\log n)$, `insert` in $\mathcal{O}(\log n)$, `extractMax` in $\mathcal{O}(\log n)$, `deleteKey` via `increaseKey(i, INT_MAX)` + `extractMax`.
- **Problem Variations**:
  - **Assignment**: Custom `MaxHeap` implementation with heap validation and file stream logging.
  - **Online A1A2 (Ticket Sales Revenue)**: Greedy revenue maximization using max-heap to repeatedly pick the seat row with the maximum remaining seats.
  - **Online B1B2 (Magical Candy Bags)**: Greedy candy maximization using max-heap to consume the largest bag and reinsert $\lfloor A_i / 2 \rfloor$.
  - **Online C1C2 (Prefix Top-3 Product)**: Maintains running prefix elements in a max-heap, extracting and restoring the 3 largest elements to output their product in $\mathcal{O}(N \log N)$ time.

### 9. [Queue ADT](./Queue)
- **Core Concept**: **FIFO (First-In, First-Out)** linear data structure where elements are enqueued at the rear and dequeued from the front.
- **Implementations**:
  - Dynamic Array Queue (`QueueArray.h`) with automatic geometric resizing.
  - Singly Linked Queue (`QueueLinkedList.h`) with dynamic node allocation.
  - Stack implemented using a Queue (`StackUsingQueue.h`) demonstrating data structure emulation.
- **Problem Variations**:
  - **Assignment**: Full queue drivers and stack-via-queue simulation.
  - **Online A1A2 (Interleaving Queue Halves)**: Splits queue into two equal halves ($Q_1, Q_2$) and alternates dequeue operations to produce $a_1, b_1, a_2, b_2, \dots$ in $\mathcal{O}(n)$ time.
  - **Online B1B2 (Palindrome Checking)**: Uses queue rotation and auxiliary stack push/pop to verify palindromes without extra memory arrays.
  - **Online C1C2 (Queue Sorting with Stack)**: Sorts queue elements in non-decreasing order using an auxiliary stack and queue rotations.

### 10. [Stack ADT](./Stack)
- **Core Concept**: **LIFO (Last-In, First-Out)** linear data structure where insertions and deletions occur strictly at the top.
- **Implementations**:
  - Dynamic Array Stack (`StackArray.h`) with doubling/halving resize policy.
  - Linked List Stack (`StackLinkedList.h`) with $\mathcal{O}(1)$ push/pop and zero capacity limit.
- **Problem Variations**:
  - **Assignment**: Stack driver testing with formatted bottom-to-top stream visualization.
  - **Online A1A2 (Stack Sort via Auxiliary Stack)**: Sorts a stack in $\mathcal{O}(n^2)$ time using only one additional stack (simulating insertion sort).
  - **Online B1B2 (Simulating Fibonacci Calls)**: Uses an explicit stack to simulate the recursive call tree of $Fib(n)$, counting function calls non-recursively.
  - **Online C1C2 (Visible Buildings / Monotonic Stack)**: Scans building heights from right to left using a monotonic stack to determine buildings visible without occlusion in $\mathcal{O}(n)$ time.

---

## 📁 Repository Directory Structure

```text
CSE 106/
├── README.md                            # Master Course Documentation
│
├── Arraylist and Linkedlist/
│   ├── README.md                        # List ADT documentation
│   ├── Assignment/                      # Offline List ADT (arraylist.h, linkedlist.h, main.c)
│   └── Online/                          # Online problems (A1A2, B1B2, C1C2)
│
├── Arrays/
│   ├── README.md                        # Array operations documentation
│   └── Onlines/                         # Triplet sum, Inversions, Second largest (A1A2, B1B2, C1C2)
│
├── Binary Search Tree/
│   ├── README.md                        # BST documentation
│   ├── Assignment/                      # Offline BST operations (bst.h, main.cpp)
│   └── Online/                          # LCA, Second largest, Range count (A1A2, B1B2, C1C2)
│
├── Divide and Conquer/
│   ├── README.md                        # Divide and conquer documentation
│   ├── Assignment/                      # Shortest hottest streak (2205119.cpp)
│   └── Online/                          # Inverted pairs, Unique count, Inversions (A1A2, B1B2, C1C2)
│
├── Dynamic Programming/
│   ├── README.md                        # DP theory and problem documentation
│   ├── Assignment/                      # Regex matcher (2205119.cpp)
│   └── Online/                          # Knapsack robber, Edit distance, LCS (A1A2, B1B2, C1C2)
│
├── Graphs/
│   ├── README.md                        # Graph algorithms documentation
│   ├── Assignment/                      # Space stations connectivity (bfs.cpp, dfs.cpp)
│   └── Online/                          # Prerequisites, Prison escape, Kahn's sort (A1A2, B1B2, C1C2)
│
├── Greedy/
│   ├── README.md                        # Manhattan MST documentation
│   └── greedy.cpp                       # Prim's algorithm on complete Manhattan graph
│
├── Heaps/
│   ├── README.md                        # Heap theory and applications documentation
│   ├── Assignment/                      # Custom MaxHeap class (MaxHeap.h, main.cpp)
│   └── Online/                          # Ticket sales, Magical bags, Top-3 product (A1A2, B1B2, C1C2)
│
├── Queue/
│   ├── README.md                        # Queue and stack-via-queue documentation
│   ├── Assignment/                      # ArrayQueue, ListQueue, StackUsingQueue drivers
│   └── Online/                          # Interleaving, Palindrome check, Queue sort (A1A2, B1B2, C1C2)
│
└── Stack/
    ├── README.md                        # Stack ADT and applications documentation
    ├── Assignment/                      # StackArray, StackLinkedList drivers
    └── Onlines/                         # Stack sort, Fibonacci calls, Monotonic buildings
```

---

## ⚡ Quick Start: Compilation & Execution

All C programs are compiled using standard `gcc -std=c11`, and all C++ programs are compiled using `g++ -std=c++17`:

```bash
# 1. Array List & Linked List Assignment
cd "Arraylist and Linkedlist/Assignment"
gcc -std=c11 -Wall -Wextra main.c -o list_test && ./list_test < in.txt

# 2. Binary Search Tree Assignment
cd "Binary Search Tree/Assignment"
g++ -std=c++17 -Wall -Wextra main.cpp -o bst_test && ./bst_test

# 3. Divide & Conquer Assignment (Maximum Subarray)
cd "Divide and Conquer/Assignment"
g++ -std=c++17 -Wall -Wextra 2205119.cpp -o dc_test && ./dc_test

# 4. Dynamic Programming Assignment (Regex Matcher)
cd "Dynamic Programming/Assignment"
g++ -std=c++17 -Wall -Wextra 2205119.cpp -o dp_test && ./dp_test

# 5. Graph Assignment (Space Stations BFS & DFS)
cd "Graphs/Assignment"
g++ -std=c++17 -Wall -Wextra bfs.cpp -o bfs_test && ./bfs_test
g++ -std=c++17 -Wall -Wextra dfs.cpp -o dfs_test && ./dfs_test

# 6. Greedy Manhattan MST
cd "Greedy"
g++ -std=c++17 -Wall -Wextra greedy.cpp -o greedy_test && ./greedy_test

# 7. Heaps Assignment
cd "Heaps/Assignment"
g++ -std=c++17 -Wall -Wextra main.cpp -o heap_test && ./heap_test

# 8. Queue Assignment
cd "Queue/Assignment"
g++ -std=c++17 -Wall -Wextra main_array_queue.cpp -o queue_test && ./queue_test

# 9. Stack Assignment
cd "Stack/Assignment"
g++ -std=c++17 -Wall -Wextra main_array_stack.cpp -o stack_test && ./stack_test
```

---

## 📊 Asymptotic Complexity Cheat Sheet

| Data Structure / Algorithm | Operation / Problem | Average Time | Worst-Case Time | Space Complexity |
|---|---|---|---|---|
| **Array List** | Access / Append / Remove | $\mathcal{O}(1) / \mathcal{O}(1)^* / \mathcal{O}(n)$ | $\mathcal{O}(1) / \mathcal{O}(n) / \mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **Doubly Linked List** | Cursor Insert / Delete / Lookup | $\mathcal{O}(1) / \mathcal{O}(1) / \mathcal{O}(n)$ | $\mathcal{O}(1) / \mathcal{O}(1) / \mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **Binary Search Tree** | Search / Insert / Delete | $\mathcal{O}(\log n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |
| **Binary Search Tree** | Tree Traversals (In/Pre/Post) | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(h)$ call stack |
| **Max Heap** | Insert / Extract Max / Find Max | $\mathcal{O}(\log n) / \mathcal{O}(\log n) / \mathcal{O}(1)$ | $\mathcal{O}(\log n) / \mathcal{O}(\log n) / \mathcal{O}(1)$ | $\mathcal{O}(n)$ |
| **Queue (Circular Array / List)**| Enqueue / Dequeue / Peek | $\mathcal{O}(1)^* / \mathcal{O}(1) / \mathcal{O}(1)$ | $\mathcal{O}(n) / \mathcal{O}(1) / \mathcal{O}(1)$ | $\mathcal{O}(n)$ |
| **Stack (Array / List)** | Push / Pop / Top | $\mathcal{O}(1)^* / \mathcal{O}(1) / \mathcal{O}(1)$ | $\mathcal{O}(n) / \mathcal{O}(1) / \mathcal{O}(1)$ | $\mathcal{O}(n)$ |
| **Divide & Conquer** | Maximum Subarray Streak | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ |
| **Divide & Conquer** | Inversion Counting (Merge Sort) | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ |
| **Dynamic Programming** | Regex Matching / Edit Distance | $\mathcal{O}(n \cdot m)$ | $\mathcal{O}(n \cdot m)$ | $\mathcal{O}(n \cdot m)$ |
| **BFS / DFS** | Graph Traversal (Adj. List) | $\mathcal{O}(V + E)$ | $\mathcal{O}(V + E)$ | $\mathcal{O}(V)$ |
| **Kahn's Algorithm** | Topological Sort / Cycle Check | $\mathcal{O}(V + E)$ | $\mathcal{O}(V + E)$ | $\mathcal{O}(V)$ |
| **Prim's Algorithm** | Manhattan Distance MST | $\mathcal{O}(n^2)$ | $\mathcal{O}(n^2)$ | $\mathcal{O}(n)$ |
| **Monotonic Stack** | Visible Buildings from Right | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ | $\mathcal{O}(n)$ |

*\* Denotes amortized time complexity.*

---

## 👨‍💻 Author & Course Details

- **Author**: Saif Al Islam
- **Student ID**: 2205119
- **Course**: CSE 106 – Data Structures and Algorithms I Sessional
- **Department**: Department of Computer Science and Engineering (CSE)
- **Institution**: Bangladesh University of Engineering and Technology (BUET)
- **Semester**: January 2024

---

## 📄 License & Academic Disclaimer

This repository is maintained for personal study, academic reference, and algorithmic benchmarking. All work adheres to ethical academic practices and is structured for clarity, modularity, and educational reproducibility.
