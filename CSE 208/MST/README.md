# Minimum Spanning Tree (MST): Algorithms & Advanced Variants

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Greedy%20Algorithms%20%26%20DSU-purple.svg)

## 📌 Overview

This repository section explores the theory, mathematical transformations, and practical implementations of the **Minimum Spanning Tree (MST)** problem on connected, weighted graphs $G = (V, E)$.

Three distinct variants are implemented:
1. **[MST Online A: Multiplicative Cost & Second-Best Spanning Tree](file:///home/saif/Documents/DSA/CSE%20208/MST/MST_Online_A)**
2. **[MST Online B: Graphland Transportation Network](file:///home/saif/Documents/DSA/CSE%20208/MST/MST_Online_B)**
3. **[MST Online C: Resilient Networks with Risky Penalties](file:///home/saif/Documents/DSA/CSE%20208/MST/MST_Online_C)**

---

## 🌲 Theoretical Foundations

A **Spanning Tree** $T$ of an undirected, connected graph $G = (V, E)$ is an acyclic subgraph connecting all $|V|$ vertices using exactly $|V| - 1$ edges.

### Fundamental Properties
- **Cut Property**: For any partition (cut) $(S, V \setminus S)$, the edge of minimum weight crossing the cut belongs to an MST.
- **Cycle Property**: For any cycle in $G$, the edge with strictly maximal weight does not belong to any minimum spanning tree.
- **Disjoint Set Union (DSU)**: Kruskal's algorithm utilizes DSU with *path compression* and *union by rank* to achieve nearly linear time $\mathcal{O}(E \cdot \alpha(V))$, where $\alpha$ is the Inverse Ackermann function.

---

## 🔍 Problem Analyses & Algorithmic Solutions

### 1. Multiplicative Costs & Second-Best MST (`MST_Online_A`)
- **Challenge**: The cost of a tree is the **product** of its edge weights: $\text{Cost}(T) = \prod_{e \in T} w(e)$.
- **Mathematical Transformation**: Because the logarithmic function is strictly monotonically increasing:
  $$\arg\min_T \prod_{e \in T} w(e) \iff \arg\min_T \sum_{e \in T} \ln(w(e))$$
  We sort edges by $\ln(w(e))$ (or compare using `log(w1) < log(w2)`), enabling standard Kruskal's algorithm to compute the minimum product spanning tree.
- **Arbitrary-Precision Arithmetic**: Because products grow exponentially and exceed 64-bit integer ranges (`unsigned long long`), a portable, self-contained `BigInt` struct was implemented in standard C++ without external dependencies (no Boost required).
- **Second-Best MST via Cycle Replacement**:
  1. Compute primary MST $T_1$.
  2. For every non-MST edge $e = (u, v) \notin T_1$:
     - Adding $e$ creates a unique cycle in $T_1 \cup \{e\}$.
     - Trace the path between $u$ and $v$ in $T_1$ using DFS.
     - For each edge $e' \in \text{path}(u, v)$, the alternative spanning tree $T' = (T_1 \setminus \{e'\}) \cup \{e\}$ has product $\text{Cost}(T_1) \times w(e) / w(e')$.
     - Track the minimum product that is strictly greater than $\text{Cost}(T_1)$.

### 2. Graphland Transportation System (`MST_Online_B`)
- **Scenario**: $N$ cities with 2D Euclidean coordinates $(x_i, y_i)$.
  - Distance $\le r$: Classified as a **road** (internal state connection).
  - Distance $> r$: Classified as a **railroad** (inter-state connection).
- **Objective**: Build an MST minimizing total length, and calculate the number of disjoint states created.
- **State Counting Invariant**:
  $$\text{Number of States} = (\text{number of railroad edges in MST}) + 1$$
- **Complexity**: $\mathcal{O}(N^2 \log N)$ to construct and sort all $\frac{N(N-1)}{2}$ edges.

### 3. Resilient Networks with Risky Penalties (`MST_Online_C`)
- **Scenario**: Vertices are categorized into *Safe* and *Risky*. Edges connected to risky cities incur additional penalty costs.
- **Two-Phase Greedy Strategy**:
  - **Phase 1 (Safe-First)**: Run Kruskal's algorithm using exclusively safe-to-safe edges to preserve network security without penalty.
  - **Phase 2 (Penalized Connectivity)**: Sort remaining edges by their effective penalized weight:
    $$\text{Cost}_{\text{eff}}(u, v) = w(u, v) + \text{penalty} \times (\text{isRisky}(u) + \text{isRisky}(v))$$
    Add edges via DSU only if they bridge disconnected components.

---

## 📊 Complexity Comparison

| Variant | Edge Sorting | DSU Operations | Secondary Search / Total Time | Space Complexity |
|---|---|---|---|---|
| **MST Online A** | $\mathcal{O}(E \log E)$ | $\mathcal{O}(E \alpha(V))$ | $\mathcal{O}(E \cdot V)$ (DFS cycle swaps) | $\mathcal{O}(V + E)$ |
| **MST Online B** | $\mathcal{O}(V^2 \log V)$ | $\mathcal{O}(V^2 \alpha(V))$ | $\mathcal{O}(V^2 \log V)$ | $\mathcal{O}(V^2)$ |
| **MST Online C** | $\mathcal{O}(E \log E)$ | $\mathcal{O}(E \alpha(V))$ | $\mathcal{O}(E \log E)$ | $\mathcal{O}(V + E)$ |

---

## 📁 Directory Structure

```text
MST/
├── MST_Online_A/
│   ├── main.cpp          # BigInt logarithmic MST + Second-best MST via cycle DFS
│   ├── test1.txt .. test4.txt
│   └── ans1.txt .. ans4.txt
├── MST_Online_B/
│   ├── main.cpp          # Euclidean road/railroad MST classification
│   └── MST_Online_B.html
└── MST_Online_C/
    ├── main.cpp          # Two-phase safe-first penalized Kruskal
    └── 2205119.cpp
```

---

## 💻 Compilation & Execution

```bash
# MST Online A
cd "MST_Online_A"
g++ -std=c++17 -O2 main.cpp -o mst_a
./mst_a < test1.txt

# MST Online B
cd "../MST_Online_B"
g++ -std=c++17 -O2 main.cpp -o mst_b
./mst_b

# MST Online C
cd "../MST_Online_C"
g++ -std=c++17 -O2 main.cpp -o mst_c
./mst_c
```
