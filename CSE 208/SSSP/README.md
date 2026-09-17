# Single-Source Shortest Path (SSSP): Algorithms & Advanced Applications

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Graph%20Shortest%20Paths-purple.svg)

## 📌 Overview

The **Single-Source Shortest Path (SSSP)** problem seeks the shortest paths from a designated source vertex $s \in V$ to all other vertices $v \in V$ in a weighted graph $G = (V, E)$.

This module contains complete solutions to three distinct problem formulations:
1. **[Section A1A2: The Tuition Path Problem (Dijkstra with Waiting-Time Penalties)](file:///home/saif/Documents/DSA/CSE%20208/SSSP/A1A2)**
2. **[Section B1B2: The Shattered Kingdom (Multi-Source Bellman-Ford & Negative Cycles)](file:///home/saif/Documents/DSA/CSE%20208/SSSP/B1B2)**
3. **[Section C1C2: Too Many DSA Labs (Dijkstra + Priority Queue Allocation)](file:///home/saif/Documents/DSA/CSE%20208/SSSP/C1C2)**

---

## 🧠 SSSP Algorithm Selection Guide

```text
                  Are all edge weights non-negative?
                             /          \
                           YES           NO
                           /              \
            Standard Dijkstra Algorithm    Are there negative cycles?
            O((V + E) log V)               /                    \
                                       NO                        YES
                                       /                          \
                     Bellman-Ford Algorithm      Bellman-Ford Reports
                     O(V * E)                    "Negative Cycle Detected"
```

| Dimension | Dijkstra's Algorithm | Bellman-Ford Algorithm |
|---|---|---|
| **Edge Weights** | Strictly non-negative ($w(u, v) \ge 0$) | Arbitrary real numbers (positive or negative) |
| **Strategy** | Greedy with Min-Priority Queue | Dynamic Programming / Edge Relaxation |
| **Time Complexity** | $\mathcal{O}((V + E) \log V)$ | $\mathcal{O}(V \cdot E)$ |
| **Negative Cycles** | Incorrect behavior / infinite loop | Reliably detected in the $V$-th relaxation pass |

---

## 🔍 Problem Analyses & Implementations

### 1. The Tuition Path Problem (`SSSP/A1A2`)
- **Scenario**: A student travels from source city $S$ to destination city $D$.
  - Each bus route $(u, v)$ has travel time $t$ and monetary fare $c$.
  - Earning opportunity loss rate: $K$ per hour.
  - **Transfer Penalty**: If switching buses (using more than 1 bus), an extra **$1$ hour waiting time** is added per transfer.
- **Objective**: Minimize total effective cost:
  $$\text{Total Cost} = \sum c + K \times \text{Total Time}$$
- **State Modeling in Dijkstra**:
  - Priority queue state: `(totalCost, node, timeSpent, edgesUsed)`.
  - When relaxing edge $u \to v$:
    $$\text{newTime} = \text{timeSpent} + t + (1 \text{ if } \text{edgesUsed} > 0 \text{ else } 0)$$
    $$\text{newCost} = \text{totalCost} + c + K \times (\text{newTime} - \text{timeSpent})$$
  - Reconstruct path via parent pointers and report path sequence, total transit hours, and total monetary cost.

### 2. The Shattered Kingdom (`SSSP/B1B2`)
- **Scenario**: A kingdom of cities with directional portals that may reduce travel time (negative edge weights).
- **Constraints**:
  - Blocked cities are inaccessible and must be removed along with incident edges.
  - Multiple capitals act as simultaneous origins.
- **Multi-Source Bellman-Ford**:
  - Distance initialization: $dist[c] = 0$ for each unblocked capital $c$, and $\infty$ otherwise.
  - Relax all active edges $N-1$ times.
  - **Abyss Detection**: If any edge $u \to v$ can still be relaxed on the $N$-th pass ($dist[v] > dist[u] + w$), a reachable negative weight cycle exists $\to$ output **`Abyss Detected`**.
  - Otherwise, output shortest distance to each emergency station.

### 3. Too Many DSA Labs (`SSSP/C1C2`)
- **Scenario**: $K$ students arrive at Lab 1. There are $N$ labs connected by undirected roads. Each lab $i$ has entry fee $F$ and seat capacity $C_i$.
- **Two-Stage Algorithm**:
  1. **Stage 1 (Shortest Paths)**: Run Dijkstra from Lab 1 to find minimum walking distance $dist[i]$ to all labs in $\mathcal{O}((N + M) \log N)$.
  2. **Stage 2 (Greedy Allocation)**:
     - Each lab's total cost is $dist[i] + F$.
     - Push all operational labs into a min-priority queue ordered by total cost.
     - For each student, assign them to the cheapest available lab with $C_i > 0$, decrement its capacity, and reinsert if seats remain.
     - If all labs are full, report `-1`.

---

## 📁 Directory Structure

```text
SSSP/
├── A1A2/
│   ├── main.cpp          # Tuition path Dijkstra with waiting penalty
│   ├── 2.txt .. 5.txt
│   └── 2_ans.txt .. 5_ans.txt
├── B1B2/
│   ├── 2205119.cpp       # Multi-source Bellman-Ford + Abyss detection
│   ├── in1.txt .. in3.txt
│   └── out1.txt .. out3.txt
└── C1C2/
    ├── main.cpp          # Dijkstra + Min-Heap lab assignment
    ├── 2.txt .. 4.txt
    └── 2_ans.txt .. 4_ans.txt
```

---

## 💻 Compilation & Testing

```bash
# SSSP A1A2
cd "A1A2"
g++ -std=c++17 -O2 main.cpp -o sssp_a
./sssp_a < 2.txt | diff -u - 2_ans.txt

# SSSP B1B2
cd "../B1B2"
g++ -std=c++17 -O2 2205119.cpp -o sssp_b
./sssp_b < in1.txt | diff -u - out1.txt

# SSSP C1C2
cd "../C1C2"
g++ -std=c++17 -O2 main.cpp -o sssp_c
./sssp_c < 2.txt | diff -u - 2_ans.txt
```
