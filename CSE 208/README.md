# CSE 208: Data Structures & Algorithms II Laboratory

![C++](https://img.shields.io/badge/C++-17-blue.svg?logo=c%2B%2B)
![Java](https://img.shields.io/badge/Java-11+-orange.svg?logo=java)
![Python](https://img.shields.io/badge/Python-3.8+-yellow.svg?logo=python)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg)
![Tests](https://img.shields.io/badge/Tests-Passing%20(100%25)-brightgreen.svg)

A comprehensive, production-grade repository containing verified implementations, mathematical models, and rigorous proofs for the **CSE 208: Data Structures and Algorithms II** course at BUET.

Every program in this repository adheres to modern C++17/Java best practices, compiles cleanly with `-Wall -Wextra` (0 errors, 0 warnings), handles corner cases safely without undefined behavior or memory leaks, and passes all test suites.

---

## 📚 Table of Contents

| # | Topic | Folder | Core Algorithms & Data Structures | Paradigm |
|---|---|---|---|---|
| 01 | **BFS & DFS** | [`BFS DFS/`](./BFS%20DFS) | BFS 2-Coloring, Odd Cycle Detection, Bipartite Verification | Graph Traversal |
| 02 | **Graph Practice** | [`Graph Practice/`](./Graph%20Practice) | Adjacency Matrix vs. Adjacency List, Dynamic Deletion, Restriction | Graph Structures |
| 03 | **Minimum Spanning Tree** | [`MST/`](./MST) | Kruskal's, DSU, Second-Best MST, Logarithmic Transform, BigInt | Greedy & Disjoint Sets |
| 04 | **All-Pairs Shortest Path** | [`APSP/`](./APSP) | Floyd-Warshall DP, Multi-Source Bellman-Ford, Capacity Assignment | Dynamic Programming |
| 05 | **Single-Source Shortest Path** | [`SSSP/`](./SSSP) | Dijkstra with Waiting Penalties, Abyss/Negative Cycle Detection | Greedy / DP |
| 06 | **Network Flow** | [`Max Flow/`](./Max%20Flow) | Edmonds-Karp, Min-Cut Max-Flow, Edge-Disjoint Paths, Kuhn's Matching | Network Optimization |
| 07 | **Balanced Search Trees** | [`Balanced BST/`](./Balanced%20BST) | Red-Black Tree, Tree Rotations, Fixup Cases, ANSI Color Visualizer | Self-Balancing Trees |
| 08 | **Binomial Heap** | [`Binomial Heap/`](./Binomial%20Heap) | Binomial Trees ($B_k$), Heap Union ($\mathcal{O}(\log N)$), Decrease-Key | Priority Queues |
| 09 | **Hash Tables** | [`Hashing/`](./Hashing) | RBT Separate Chaining, Linear Probing, Double Hashing, Dynamic Rehash | Hashing & Amortization |
| 10 | **Approximation Algorithms** | [`Approximation/`](./Approximation) | Metric TSP 2-Approx, Knapsack FPTAS (Value Scaling), Vertex Cover | Approximation Schemes |
| 11 | **Intractability** | [`Intractability/`](./Intractability) | Reductions for CDS, K-Coloring, and NAE-3-SAT, Certificate Checks | NP-Completeness Proofs |

---

## 🧠 Highlights & Key Implementations

### 1. [BFS & DFS](./BFS%20DFS)
- **Concept**: Verification of graph 2-colorability ($G$ is bipartite $\iff$ no odd cycles).
- **Implementations**: C++ (`BFS_DFS_Solution.cpp`) and Java (`BFS_DFS_Solution.java`).
- **Complexity**: $\mathcal{O}(V + E)$ time, $\mathcal{O}(V)$ space.

### 2. [Graph Practice](./Graph%20Practice)
- **Concept**: Architectural comparison between dense **Adjacency Matrix** (C++) and sparse **Adjacency List** (Java).
- **Features**: Dynamic vertex removal with cascading neighbor restriction and protected degree lookups.

### 3. [Minimum Spanning Tree (MST)](./MST)
- **Multiplicative Product MST (`MST_Online_A`)**: Minimizes $\prod w(e)$ via logarithmic conversion $\sum \ln(w(e))$ with standard Kruskal, computing exact products via a portable standard C++ `BigInt` struct without external Boost dependencies. Computes the strictly second-best MST via DFS cycle search.
- **Graphland Network (`MST_Online_B`)**: Euclidean distance clustering into roads and railroads; counts connected states.
- **Resilient Networks (`MST_Online_C`)**: Two-phase safe-first Kruskal algorithm balancing security penalties.

### 4. [All-Pairs Shortest Path (APSP)](./APSP)
- **National Tuition Lord (`A1A2`)**: Floyd-Warshall $\mathcal{O}(N^3)$ meeting city search minimizing opportunity cost.
- **Shattered Kingdom (`B1B2`)**: Multi-source Bellman-Ford on portal networks with reachable negative cycle ("Abyss") detection. Verified with automated Python evaluator across 10 test suites.
- **Too Few DSA Labs (`C1C2`)**: Filtered Floyd-Warshall excluding maintenance nodes with sequential capacity consumption.

### 5. [Single-Source Shortest Path (SSSP)](./SSSP)
- **Tuition Path (`A1A2`)**: Dijkstra state tracking `(totalCost, node, timeSpent, edgesUsed)` with waiting-time penalty for bus transfers.
- **Shattered Kingdom (`B1B2`)**: Multi-source Bellman-Ford detecting negative cycles.
- **Too Many DSA Labs (`C1C2`)**: Dijkstra shortest-path precomputation combined with min-priority queue student assignment.

### 6. [Network Flow & Matching](./Max%20Flow)
- **Operation Royal Mint (`A1A2`)**: Edge-disjoint escape routes using unit-capacity Edmonds-Karp with explicit path decomposition via DFS.
- **Owls and Mice (`B1B2`)**: Bipartite flow reduction with Euclidean range filtering and capacitated sink burrows.
- **Strategic Partnerships (`C1C2`)**: Kuhn's augmenting path algorithm for maximum bipartite matching across 7 compatibility attributes.

### 7. [Balanced Binary Search Trees](./Balanced%20BST)
- **Red-Black Tree Inventory (`2205119.cpp`)**: Full self-balancing tree with insertion fixup (cases 1–3) and deletion fixup (cases 1–4) with sentinel `NIL` pointer management.
- **Cross-Platform Visualization**: Supports colored tree printing on both Windows console and Linux ANSI terminals via `color.hpp`.

### 8. [Binomial Min-Heap](./Binomial%20Heap)
- **Structure**: Forest of binomial trees $B_k$ satisfying min-heap order and degree uniqueness.
- **Fast Union**: Binomial heap union in $\mathcal{O}(\log N)$ time analogous to binary integer addition with carries.
- **Memory Safety**: Stack-allocated dummy nodes, leak-free pointer splicing, and safe queries on empty heaps.

### 9. [Hash Tables & Dynamic Memory Manager](./Hashing)
- **Offline Benchmarking (`Offline/`)**: Separate Chaining with Red-Black Trees, Linear Probing, and Double Hashing (fixed $i=0$ double-probing bug and enabled safe deleted slot reuse).
- **Dynamic Memory Manager (`Hashing_Online_Shift_1`)**: Quadratic probing ($h(k) + j^2$), automatic scale-up rehash when probes exceed $P_{\max}$, and scale-down rehash when load factor $< 0.2$ after deletions.
- **Two-Tier Permission Database (`Hashing_Online_Shift_2`)**: Outer table (Linear Probing) $\to$ Inner table (Quadratic Probing) with in-place permission updates and whitespace-safe line parsing.

### 10. [Approximation Algorithms](./Approximation)
- **Metric TSP 2-Approximation (`A1A2`)**: Prim's MST + DFS preorder walk shortcutting via triangle inequality.
- **0-1 Knapsack FPTAS (`B1B2`)**: Fully polynomial scheme with scaling $K = \frac{\epsilon \cdot v_{\max}}{n}$ and DP by scaled values in $\mathcal{O}(n^3 / \epsilon)$ time, guaranteed $\ge (1 - \epsilon) \text{OPT}$.
- **Vertex Cover 2-Approximation (`C1C2`)**: Maximal matching greedy selection + brute-force bitmask solver for empirical ratio validation.

### 11. [Intractability & NP-Completeness](./Intractability)
- **Rigorous Proofs**: Formal verification certificates and polynomial-time reduction proofs:
  - **Connected Dominating Set (CDS)** $\le_p$ Vertex Cover
  - **$K$-Coloring** $\le_p$ 3-Coloring
  - **Not-All-Equal 3-SAT (NAE-3-SAT)** $\le_p$ 3-SAT

---

## ⚡ Quick Start & Verification

### Prerequisites
- GCC / G++ (supporting C++17)
- OpenJDK 11+ (`javac`, `java`)
- Python 3.8+

### Compile and Verify All Topics
```bash
# Compile and test APSP B1B2
cd "APSP/B1B2" && python3 evaluator.py 2205119.cpp && cd ../..

# Compile and test MST Online A
cd "MST/MST_Online_A" && g++ -std=c++17 -O2 main.cpp -o mst_a && ./mst_a < test1.txt && cd ../..

# Compile and test Hashing Shift 1
cd "Hashing/Hashing_Online_Shift_1" && g++ -std=c++17 -O2 main.cpp -o h1 && ./h1 < input1.txt && cd ../..

# Compile and test SSSP A1A2
cd "SSSP/A1A2" && g++ -std=c++17 -O2 main.cpp -o sssp_a && ./sssp_a < 2.txt && cd ../..
```

---

## 📊 Algorithmic Complexity Reference

| Algorithm | Problem Context | Worst-Case Time | Auxiliary Space |
|---|---|---|---|
| **BFS 2-Coloring** | Bipartite Checking | $\mathcal{O}(V + E)$ | $\mathcal{O}(V)$ |
| **Kruskal's Algorithm** | MST | $\mathcal{O}(E \log E)$ | $\mathcal{O}(V + E)$ |
| **Prim's Algorithm** | MST / Metric TSP | $\mathcal{O}(V^2)$ or $\mathcal{O}(E \log V)$ | $\mathcal{O}(V)$ |
| **Dijkstra's Algorithm** | SSSP (Non-negative) | $\mathcal{O}((V + E) \log V)$ | $\mathcal{O}(V)$ |
| **Bellman-Ford Algorithm** | SSSP (Negative weights) | $\mathcal{O}(V \cdot E)$ | $\mathcal{O}(V)$ |
| **Floyd-Warshall** | APSP | $\mathcal{O}(V^3)$ | $\mathcal{O}(V^2)$ |
| **Edmonds-Karp** | Maximum Flow | $\mathcal{O}(V \cdot E^2)$ | $\mathcal{O}(V + E)$ |
| **Kuhn's Matching** | Max Bipartite Matching | $\mathcal{O}(V \cdot E)$ | $\mathcal{O}(V)$ |
| **Red-Black Tree** | Balanced BST Search/Insert/Delete | $\mathcal{O}(\log N)$ | $\mathcal{O}(N)$ |
| **Binomial Heap Union** | Merge Priority Queues | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ |
| **Knapsack FPTAS** | $(1 - \epsilon)$ Approximation | $\mathcal{O}(n^3 / \epsilon)$ | $\mathcal{O}(n^2 / \epsilon)$ |


