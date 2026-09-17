# Approximation Algorithms & FPTAS: Theoretical Bounds & Implementations

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-NP--Hard%20Approximations-purple.svg)

## 📌 Overview

Many real-world optimization problems are **NP-hard**, meaning that no polynomial-time algorithm exists to find exact optimal solutions (unless $\mathcal{P} = \mathcal{NP}$). **Approximation Algorithms** provide mathematically proven performance bounds with polynomial execution time.

This module features three classical approximation algorithms:
1. **[Section A1A2: 2-Approximation for Metric TSP (Triangle Inequality)](file:///home/saif/Documents/DSA/CSE%20208/Approximation/A1A2)**
2. **[Section B1B2: Fully Polynomial-Time Approximation Scheme (FPTAS) for 0-1 Knapsack](file:///home/saif/Documents/DSA/CSE%20208/Approximation/B1B2)**
3. **[Section C1C2: 2-Approximation for Minimum Vertex Cover & Exact Brute-Force Comparison](file:///home/saif/Documents/DSA/CSE%20208/Approximation/C1C2)**

---

## 📐 Approximation Metrics & Guarantees

An algorithm for a problem has **approximation ratio** $\rho$ if for all instances:
- For a **Minimization** problem (e.g., TSP, Vertex Cover):
  $$\frac{\text{ALG}}{\text{OPT}} \le \rho \quad (\rho \ge 1)$$
- For a **Maximization** problem (e.g., Knapsack):
  $$\frac{\text{ALG}}{\text{OPT}} \ge 1 - \epsilon \quad (\epsilon > 0)$$

An **FPTAS** (Fully Polynomial-Time Approximation Scheme) is the strongest approximation guarantee for NP-hard problems, running in time polynomial in both input size $n$ and $\frac{1}{\epsilon}$.

---

## 🔍 Detailed Problem Analysis & Proofs

### 1. 2-Approximation for Metric TSP (`Approximation/A1A2`)
- **Problem**: Given a complete graph where edge weights satisfy the **triangle inequality** ($c(u, w) \le c(u, v) + c(v, w)$), find a Hamiltonian cycle of minimum cost.
- **Algorithm**:
  1. Construct a Minimum Spanning Tree (MST) using Prim's algorithm.
  2. Perform a Depth-First Search (DFS) preorder traversal of the MST.
  3. Form a tour by visiting vertices in preorder and returning to the start node (short-circuiting repeated vertices).
- **Proof of 2-Approximation**:
  - Removing any edge from an optimal TSP tour yields a spanning tree $\implies \text{Cost}(\text{MST}) \le \text{OPT}$.
  - A full walk traversing each MST edge twice has cost $2 \times \text{Cost}(\text{MST}) \le 2 \times \text{OPT}$.
  - By the triangle inequality, bypassing already visited vertices does not increase total cost. Hence, $\text{Cost}(\text{Tour}) \le 2 \times \text{OPT}$.

### 2. FPTAS for 0-1 Knapsack (`Approximation/B1B2`)
- **Problem**: Given $n$ items with weights $w_i$, values $v_i$, capacity $W$, and tolerance $\epsilon > 0$, select a subset of items maximizing total value without exceeding capacity.
- **Algorithm via Value Scaling**:
  1. Find $v_{\max} = \max_i v_i$.
  2. Compute scaling parameter $K = \frac{\epsilon \cdot v_{\max}}{n}$.
  3. Define scaled values $v'_i = \left\lfloor \frac{v_i}{K} \right\rfloor$.
  4. Compute dynamic programming table where $DP[j]$ is the minimum weight needed to achieve scaled value $j$:
     $$DP[j + v'_i] = \min(DP[j + v'_i],\; DP[j] + w_i)$$
  5. Recover item choices and report actual original value.
- **Complexity**:
  $$\text{Total Scaled Value} \le n \cdot \left\lfloor \frac{v_{\max}}{K} \right\rfloor = \frac{n^2}{\epsilon} \implies \text{Time Complexity} = \mathcal{O}\left(\frac{n^3}{\epsilon}\right)$$
- **Approximation Guarantee**: Proven $\text{Value}(\text{ALG}) \ge (1 - \epsilon) \text{OPT}$.

### 3. 2-Approximation for Minimum Vertex Cover (`Approximation/C1C2`)
- **Problem**: Find the smallest subset of vertices $C \subseteq V$ such that every edge $e \in E$ has at least one endpoint in $C$.
- **Greedy Matching Algorithm**:
  1. Start with $C = \emptyset$.
  2. Repeatedly select an uncovered edge $(u, v) \in E$.
  3. Add **both** endpoints $u$ and $v$ to $C$.
  4. Remove (mark covered) all edges incident to $u$ or $v$.
- **Proof of 2-Approximation**:
  - The chosen edges form a maximal matching $M$.
  - Any valid vertex cover must include at least one endpoint of each matching edge $\implies \text{OPT} \ge |M|$.
  - The algorithm adds both endpoints $\implies |C| = 2|M| \le 2 \times \text{OPT}$.
- **Comparative Analysis (`problem2.cpp`)**:
  Computes the exact minimum vertex cover via exhaustive bitmask search for $n \le 25$ to compare empirical approximation ratios against theoretical bounds.

---

## 📊 Summary of Approximations

| Problem | Algorithm Strategy | Approximation Bound | Time Complexity | Class |
|---|---|---|---|---|
| **TSP (Metric)** | MST + DFS Preorder Shortcut | $\le 2 \times \text{OPT}$ | $\mathcal{O}(V^2)$ | 2-Approximation |
| **0-1 Knapsack** | Value Scaling + DP by Value | $\ge (1 - \epsilon) \times \text{OPT}$ | $\mathcal{O}(n^3 / \epsilon)$ | FPTAS |
| **Vertex Cover** | Maximal Matching Edge Pick | $\le 2 \times \text{OPT}$ | $\mathcal{O}(V + E)$ | 2-Approximation |

---

## 📁 Directory Structure

```text
Approximation/
├── A1A2/
│   ├── main.cpp          # Metric TSP 2-approximation (Prim MST + Preorder)
│   └── Approx-Practice-A.pdf
├── B1B2/
│   ├── 2205119.cpp       # Knapsack FPTAS with value scaling DP
│   └── Approx-Practice-B.pdf
└── C1C2/
    ├── main.cpp          # Vertex cover 2-approximation
    ├── problem2.cpp      # Brute-force exact comparison & ratio benchmark
    └── Approx-Practice-C.pdf
```

---

## 💻 Compilation & Execution

```bash
# TSP 2-Approximation
cd "A1A2"
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o tsp_approx
./tsp_approx

# Knapsack FPTAS
cd "../B1B2"
g++ -std=c++17 -Wall -Wextra -O2 2205119.cpp -o knapsack_fptas
./knapsack_fptas

# Vertex Cover 2-Approximation & Comparison
cd "../C1C2"
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o vc_approx
g++ -std=c++17 -Wall -Wextra -O2 problem2.cpp -o vc_comparison
./vc_approx
./vc_comparison
```
