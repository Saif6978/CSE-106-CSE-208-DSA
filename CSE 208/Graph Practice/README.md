# Directed Graph Operations: Adjacency Matrix vs. Adjacency List

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Java](https://img.shields.io/badge/Language-Java-orange.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Graph%20Data%20Structures-purple.svg)

## 📌 Project Overview

This module provides implementations of a **Directed Graph** ($G = (V, E)$) across two programming languages, comparing two foundational graph representations:
1. **Adjacency Matrix** in C++ (`graph_practice.cpp`)
2. **Adjacency List** in Java (`GraphPractice.java`)

Both implementations support dynamic edge manipulation, vertex removal with restriction propagation, neighborhood queries, and in/out-degree calculations.

---

## 🏛 Graph Representation Trade-offs

| Representation | Memory Complexity | Edge Lookup $(u \to v)$ | Degree Calculation | Best Suited For |
|---|---|---|---|---|
| **Adjacency Matrix** (C++) | $\mathcal{O}(V^2)$ | $\mathcal{O}(1)$ | $\mathcal{O}(V)$ | Dense graphs ($E \approx V^2$), constant-time edge existence queries |
| **Adjacency List** (Java) | $\mathcal{O}(V + E)$ | $\mathcal{O}(\text{deg}(u))$ | In-degree: $\mathcal{O}(V + E)$, Out-degree: $\mathcal{O}(1)$ | Sparse graphs ($E \ll V^2$), memory-constrained environments |

---

## ⚙ Supported Operations & Invariants

1. **`addEdge(u, v)`**:
   - Inserts a directed edge $u \to v$.
   - Validates that $0 \le u, v < V$ and neither vertex is marked as restricted.
2. **`removeEdge(u, v)`**:
   - Deletes directed edge $u \to v$ while retaining all other incident edges.
3. **`removeVertex(u)`**:
   - Marks vertex $u$ as restricted/removed.
   - Clears all incoming edges $(w \to u)$ and outgoing edges $(u \to w)$ for all $w \in V$.
   - Prevents any future edge insertions involving $u$.
4. **`inDegree(u)` / `outDegree(u)`**:
   - Computes number of incoming ($\sum_{w} [w \to u]$) and outgoing ($\sum_{w} [u \to w]$) connections.
   - Rejects queries on restricted or out-of-range vertices safely.
5. **`inNeighbors(u)` / `outNeighbors(u)`**:
   - Returns the list of active vertices that point into $u$ or that $u$ points into.
6. **`printGraph()`**:
   - Prints current adjacency relationships among active vertices.

---

## ⏱ Operation Complexity Comparison

| Operation | C++ (Adjacency Matrix) | Java (Adjacency List) |
|---|---|---|
| `addEdge(u, v)` | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| `removeEdge(u, v)` | $\mathcal{O}(1)$ | $\mathcal{O}(\text{deg}(u))$ |
| `removeVertex(u)` | $\mathcal{O}(V)$ | $\mathcal{O}(V + E)$ |
| `inDegree(u)` | $\mathcal{O}(V)$ | $\mathcal{O}(V + E)$ |
| `outDegree(u)` | $\mathcal{O}(V)$ | $\mathcal{O}(1)$ |
| `printGraph()` | $\mathcal{O}(V^2)$ | $\mathcal{O}(V + E)$ |

---

## 📁 Repository Files

- [`graph_practice.cpp`](file:///home/saif/Documents/DSA/CSE%20208/Graph%20Practice/graph_practice.cpp): C++ directed graph using a 2D `vector<vector<int>>` matrix.
- [`GraphPractice.java`](file:///home/saif/Documents/DSA/CSE%20208/Graph%20Practice/GraphPractice.java): Java directed graph extending an abstract graph class using `ArrayList<LinkedList<Integer>>`.

---

## 💻 Compilation & Execution

### C++
```bash
# Compile with all warnings enabled
g++ -std=c++17 -Wall -Wextra -O2 graph_practice.cpp -o graph_practice

# Run interactively
./graph_practice
```

### Java
```bash
# Compile
javac GraphPractice.java

# Run
java GraphPractice
```

---

## 🧪 Interactive Menu Options

When launched, the programs prompt with an interactive menu:
```text
1. Add Edge
2. Remove Edge
3. Check In-degree
4. Check Out-degree
5. Find In-neighbors
6. Find Out-neighbors
7. Remove Vertex
8. Print Graph
9. Exit
```
Restricted vertices are strictly protected against invalid accesses, preventing segmentation faults and index out-of-bounds exceptions.
