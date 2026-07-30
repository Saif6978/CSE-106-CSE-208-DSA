# Graph Algorithms - Problem Solving (CSE 106)

> **Course:** CSE 106 – Data Structures & Algorithms  
> **Author:** Saif Al Islam  
> **Student ID:** 2205119

This repository contains my solutions to several graph-related programming problems completed during my **Data Structures & Algorithms** course.

The solutions demonstrate fundamental graph algorithms including **Breadth-First Search (BFS)**, **Depth-First Search (DFS)**, **Connected Components**, **Cycle Detection**, **Topological Sorting**, **Reverse Graph Traversal**, and **Grid Traversal**.

---

# Repository Structure

```
Graphs/
│
├── Assignment/
│   └── Space Stations
│       ├── BFS (Adjacency Matrix)
│       └── DFS (Adjacency List)
│
└── Online/
    ├── A1_A2/
    │   └── Prerequisite Courses
    │
    ├── B1_B2/
    │   └── Prison Escape
    │
    └── C1_C2/
        └── Module Dependencies
```

---

# Topics Covered

- Graph Representations
  - Adjacency Matrix
  - Adjacency List
  - Implicit Grid Graph

- Graph Traversal
  - Breadth-First Search (BFS)
  - Depth-First Search (DFS)

- Connected Components

- Reverse Graph Traversal

- Topological Sorting

- Cycle Detection

- Grid Traversal

- Reachability Analysis

---

# Assignment — Space Stations

## Problem

There are **N** space stations connected by **M** bidirectional tunnels.

Some stations may be isolated. Your task is to determine

- the **minimum number of tunnels** required to connect every station, and
- which stations should be connected.

Two implementations are provided:

- **BFS using an Adjacency Matrix**
- **DFS using an Adjacency List**

---

## Idea

A graph containing **K connected components** can always be connected using exactly

```
K − 1
```

new edges.

Steps:

1. Traverse the graph using BFS or DFS.
2. Find every connected component.
3. Store one representative node from each component.
4. Connect consecutive representatives.

Example

```
Component 1 → 1
Component 2 → 5
Component 3 → 8

New tunnels

1 — 5
5 — 8
```

---

## Algorithm

1. Build the graph.
2. Traverse every unvisited node.
3. Whenever a new traversal starts,
   - store that node as the component representative.
4. After traversal,

```
Answer = Number of Components − 1
```

5. Print edges between consecutive representatives.

---

## Complexity

### BFS (Adjacency Matrix)

| Complexity | Value |
|------------|-------|
| Time | **O(N²)** |
| Space | **O(N²)** |

### DFS (Adjacency List)

| Complexity | Value |
|------------|-------|
| Time | **O(N + M)** |
| Space | **O(N + M)** |

---

# Online A1/A2 — Prerequisite Courses

## Problem

Each directed edge

```
A → B
```

means **A must be completed before B**.

For every query asking about course **C**, determine the total number of distinct prerequisite courses (both direct and indirect).

---

## Idea

Instead of searching forward, construct a **reverse graph**.

Original

```
A → B
```

Reverse

```
B → A
```

Now perform BFS/DFS starting from **C**.

Every reachable node represents a prerequisite.

---

## Algorithm

1. Build the reverse graph.
2. For each query:
   - Start BFS/DFS from the queried course.
   - Count every visited node except the starting node.
3. Output the count.

---

## Complexity

| Complexity | Value |
|------------|-------|
| Graph Construction | **O(N + M)** |
| Per Query | **O(N + M)** |

---

# Online B1/B2 — Prison Escape

## Problem

A prisoner starts at cell **S** inside an **N × M** grid.

The prisoner may move

- Up
- Down
- Left
- Right

Cells marked

```
#
```

are blocked.

Count how many exits (**E**) are reachable.

---

## Idea

Run **one BFS** from the starting position.

Every reachable cell is marked as visited.

Finally, count how many exit cells were visited.

---

## Algorithm

1. Locate the starting cell.
2. Push it into the BFS queue.
3. Visit every reachable cell.
4. Count all visited exit cells.

---

## Complexity

| Complexity | Value |
|------------|-------|
| Time | **O(N × M)** |
| Space | **O(N × M)** |

---

# Online C1/C2 — Module Dependencies

## Problem

Each directed edge

```
A → B
```

means

> Module A must be compiled before Module B.

Determine whether the dependency graph contains a cycle.

Output

```
Yes
```

if a cycle exists.

Otherwise output

```
No
```

---

## Idea

A directed graph contains a cycle **iff** a complete topological ordering does **not** exist.

We use **Kahn's Algorithm**.

---

## Kahn's Algorithm

1. Compute the indegree of every node.
2. Insert all nodes with indegree **0** into a queue.
3. Repeatedly:
   - Remove one node.
   - Decrease the indegree of its neighbors.
   - Push any node whose indegree becomes **0**.
4. Count processed nodes.

If

```
processed == N
```

the graph is acyclic.

Otherwise, a cycle exists.

---

## Complexity

| Complexity | Value |
|------------|-------|
| Time | **O(N + M)** |
| Space | **O(N + M)** |

---

# Compilation

Compile using a C++17 compiler.

```bash
g++ -std=c++17 -O2 filename.cpp -o output
./output < input.txt
```

---

# Graph Algorithms Used

| Algorithm | Used In |
|-----------|----------|
| BFS | Space Stations, Prison Escape, Prerequisite Courses |
| DFS | Space Stations |
| Connected Components | Space Stations |
| Reverse Graph | Prerequisite Courses |
| Grid BFS | Prison Escape |
| Topological Sort | Module Dependencies |
| Kahn's Algorithm | Module Dependencies |

---

# Key Takeaways

### Breadth-First Search (BFS)

- Explores the graph level by level.
- Guarantees the shortest path in an unweighted graph.
- Ideal for reachability and shortest-distance problems.

---

### Depth-First Search (DFS)

- Explores one path as deeply as possible before backtracking.
- Simple recursive implementation.
- Useful for connected components, trees, and graph exploration.

---

### Adjacency Matrix

**Advantages**

- Constant-time edge lookup `O(1)`
- Simple implementation

**Disadvantages**

- Requires `O(N²)` memory
- Inefficient for sparse graphs

---

### Adjacency List

**Advantages**

- Memory efficient
- Traversal runs in `O(N + M)`
- Best choice for sparse graphs

---

### Reverse Graph

Reversing every edge transforms

```
Prerequisite → Course
```

into

```
Course → Prerequisite
```

making ancestor queries straightforward using a single traversal.

---

### Kahn's Algorithm

- Performs Topological Sorting using BFS.
- Detects cycles without recursion.
- Efficient for dependency graphs.

---

## Author

**Saif Al Islam**

**Student ID:** 2205119

**Course:** CSE 106 — Data Structures & Algorithms
