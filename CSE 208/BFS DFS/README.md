# BFS & DFS: Bipartite Graph Verification

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Java](https://img.shields.io/badge/Language-Java-orange.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Graph%20Theory-purple.svg)

## 📌 Problem Overview

Given an undirected graph $G = (V, E)$, determine whether the graph is **bipartite** (2-colorable).

A graph is bipartite if its vertex set $V$ can be partitioned into two disjoint independent sets $V_1$ and $V_2$ ($V = V_1 \cup V_2$ and $V_1 \cap V_2 = \emptyset$) such that every edge $(u, v) \in E$ connects a vertex from $V_1$ to a vertex from $V_2$. Equivalently, by **Kőnig's Theorem (1936)**:
> An undirected graph is bipartite if and only if it contains no odd-length cycles.

---

## 🧠 Core Algorithmic Concept: BFS 2-Coloring

To verify 2-colorability, we perform a Breadth-First Search (BFS) traversal that assigns alternating colors (e.g., `0` and `1`) to adjacent vertices.

### State Representation
- `color[u] = -1`: Vertex $u$ is unvisited.
- `color[u] = 0`: Vertex $u$ belongs to partition $V_1$.
- `color[u] = 1`: Vertex $u$ belongs to partition $V_2$.

### Algorithm Steps
1. Initialize `color[u] = -1` for all $u \in \{0, 1, \dots, V-1\}$.
2. Iterate through each vertex $i \in [0, V-1]$. If `color[i] == -1` (handling disconnected components):
   - Set `color[i] = 0` and enqueue $i$.
   - While the queue is not empty, dequeue vertex $u$:
     - For each neighbor $v$ of $u$:
       - **If unvisited** (`color[v] == -1`): Assign `color[v] = 1 - color[u]` and push $v$ into the queue.
       - **If visited and conflicting** (`color[v] == color[u]`): An odd cycle exists! Immediately terminate and report **`Not Bipartite`**.
3. If all vertices and components are colored without conflicts, output **`Bipartite`**.

```
      (0) [Color 0]
      / \
     /   \
(1) [C 1] (2) [C 1]    ==> Valid 2-Coloring (Bipartite)
     \   /
      \ /
      (3) [Color 0]
```

---

## ⏱ Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $\mathcal{O}(V + E)$ | Every vertex is enqueued once and every edge is traversed at most twice. |
| **Space Complexity** | $\mathcal{O}(V + E)$ | Adjacency list storage + $\mathcal{O}(V)$ queue and color array. |

---

## 📁 Repository Files

- [`BFS_DFS_Solution.cpp`](file:///home/saif/Documents/DSA/CSE%20208/BFS%20DFS/BFS_DFS_Solution.cpp): C++ implementation using STL vectors and queue.
- [`BFS_DFS_Solution.java`](file:///home/saif/Documents/DSA/CSE%20208/BFS%20DFS/BFS_DFS_Solution.java): Java OOP implementation extending an abstract graph template.
- [`BFS DFS Practice.pdf`](file:///home/saif/Documents/DSA/CSE%20208/BFS%20DFS/BFS%20DFS%20Practice.pdf): Original practice problem specification.

---

## 💻 Compilation & Execution

### C++
```bash
# Compile
g++ -std=c++17 -O2 BFS_DFS_Solution.cpp -o bfs_dfs

# Run
./bfs_dfs
```

### Java
```bash
# Compile
javac BFS_DFS_Solution.java

# Run
java BFS_DFS_Solution
```

---

## 🧪 Input & Output Format

### Input Format
- First line: Two integers $V$ (number of vertices) and $E$ (number of edges).
- Next $E$ lines: Two integers $u$ and $v$ representing an undirected edge between $u$ and $v$ ($0 \le u, v < V$).

### Sample 1: Bipartite Graph
**Input:**
```text
4 4
0 2
0 3
1 2
1 3
```
**Output:**
```text
Bipartite
```

### Sample 2: Non-Bipartite Graph (Triangle / Odd Cycle)
**Input:**
```text
3 3
0 1
1 2
2 0
```
**Output:**
```text
Not Bipartite
```
*(Vertices form a cycle of length 3, requiring at least 3 colors).*
