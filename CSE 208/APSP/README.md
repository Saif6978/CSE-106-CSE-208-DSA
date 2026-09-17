# All-Pairs Shortest Path (APSP) Algorithms & Problem Variations

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Python](https://img.shields.io/badge/Language-Python3-yellow.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Dynamic%20Programming%20%26%20Shortest%20Paths-purple.svg)

## 📌 Overview

This section covers the **All-Pairs Shortest Path (APSP)** problem and related graph distance problems. Unlike Single-Source Shortest Path (SSSP) algorithms that compute paths from a fixed origin, APSP determines the shortest distances between every pair of vertices $(u, v) \in V \times V$.

Three real-world problem scenarios are explored and implemented:
1. **[Section A1A2: National Tuition Lord (Optimal Meeting City)](file:///home/saif/Documents/DSA/CSE%20208/APSP/A1A2)**
2. **[Section B1B2: The Shattered Kingdom (Multi-Source Bellman-Ford & Negative Cycles)](file:///home/saif/Documents/DSA/CSE%20208/APSP/B1B2)**
3. **[Section C1C2: Too Few DSA Labs (Capacity-Bounded Assignment)](file:///home/saif/Documents/DSA/CSE%20208/APSP/C1C2)**

---

## 🧠 Algorithmic Core: The Floyd-Warshall Dynamic Program

The **Floyd-Warshall algorithm** solves APSP for directed or undirected weighted graphs with arbitrary (positive or negative) edge weights without negative cycles.

### DP State Formulation
Let $d^{(k)}[i][j]$ denote the shortest path distance from vertex $i$ to vertex $j$ using only intermediate vertices from the set $\{1, 2, \dots, k\}$.
$$d^{(k)}[i][j] = \min\left( d^{(k-1)}[i][j],\; d^{(k-1)}[i][k] + d^{(k-1)}[k][j] \right)$$

- **Base Case ($k=0$)**: Direct edge weights $w(i, j)$, with $d[i][i] = 0$ and $d[i][j] = \infty$ if no edge exists.
- **In-place Optimization**: The $(k)$ index can be dropped, computing over a 2D $N \times N$ matrix in three nested loops.
- **Negative Cycle Detection**: A graph contains a negative cycle iff $d[i][i] < 0$ for any vertex $i$ after completion.

---

## 🛠 Problem Formulations & Solution Techniques

### 1. Section A1A2: National Tuition Lord
- **Goal**: Find an optimal meeting city $m$ among $N$ cities that minimizes the sum of opportunity costs for multiple traveling lords.
- **Model**:
  - Each lord $k$ starts at city $s_k$, has maximum allowed travel time $T_k^{\max}$, and hourly opportunity wage $W_k$.
  - Run Floyd-Warshall to compute travel times $D[i][j]$ between all cities.
  - Candidate city $c$ is feasible if $D[s_k][c] \le T_k^{\max}$ for all lords $k$.
  - Total Opportunity Cost at city $c$:
    $$\text{Cost}(c) = \sum_{k} \left( D[s_k][c] \times W_k \right)$$
  - Choose $c^* = \arg\min_c \text{Cost}(c)$.

### 2. Section B1B2: The Shattered Kingdom
- **Goal**: Compute shortest distances from multiple capitals to emergency posts through a directed portal network, detect negative weight cycles, and ignore blocked cities.
- **Model**:
  - Filter out blocked cities from the active graph.
  - **Multi-Source Bellman-Ford**: Initialize $d[c] = 0$ for all starting capitals $c \in \text{Capitals}$, and $d[v] = \infty$ for others.
  - Relax all edges $N-1$ times.
  - Run an $N$-th relaxation pass: If any distance $d[v] > d[u] + w(u, v)$ improves, output **`Abyss Detected`** and exit.
  - Output shortest distances to requested emergency posts or `INF`.

### 3. Section C1C2: Too Few DSA Labs
- **Goal**: Process student requests sequentially and assign each student to the nearest available lab with remaining seat capacity.
- **Model**:
  - Labs under maintenance cannot be chosen as destinations and cannot be traversed as intermediate path nodes.
  - Initialize bidirectional road weights $d[u][v] = d[v][u] = w(u, v)$ for non-maintenance nodes.
  - Precompute all-pairs shortest paths via Floyd-Warshall in $\mathcal{O}(N^3)$.
  - For each student arriving at entry city $s$, find active destination lab $l$ maximizing capacity and minimizing $d[s][l]$; decrement capacity after allocation.

---

## ⏱ Complexity Summary

| Problem | Core Algorithm | Time Complexity | Space Complexity |
|---|---|---|---|
| **A1A2 (Tuition Lord)** | Floyd-Warshall + Exhaustive Search | $\mathcal{O}(N^3 + L \cdot N)$ | $\mathcal{O}(N^2)$ |
| **B1B2 (Shattered Kingdom)** | Multi-Source Bellman-Ford | $\mathcal{O}(N \cdot M)$ | $\mathcal{O}(N + M)$ |
| **C1C2 (DSA Labs)** | Filtered Floyd-Warshall + Query Assignment | $\mathcal{O}(N^3 + K \cdot N)$ | $\mathcal{O}(N^2)$ |

---

## 📁 Directory Structure

```text
APSP/
├── A1A2/
│   └── main.cpp          # National Tuition Lord Floyd-Warshall
├── B1B2/
│   ├── 2205119.cpp       # Multi-source Bellman-Ford + Abyss detection
│   ├── evaluator.py      # Automated cross-platform test harness (10 tests)
│   ├── in1.txt .. in10.txt
│   └── out1.txt .. out10.txt
└── C1C2/
    ├── main.cpp          # Capacity-bounded Floyd-Warshall lab assignment
    ├── test1.txt .. test3.txt
    └── ans1.txt .. ans3.txt
```

---

## 💻 Compilation & Testing

```bash
# Test B1B2 with automated evaluator
cd "B1B2"
python3 evaluator.py 2205119.cpp

# Compile and test C1C2
cd "../C1C2"
g++ -std=c++17 -O2 main.cpp -o apsp_c
./apsp_c < test1.txt | diff -u - ans1.txt
```
