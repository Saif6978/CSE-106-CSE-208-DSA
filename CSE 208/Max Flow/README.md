# Network Flow & Bipartite Matching: Theory & Practical Reductions

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Network%20Flow%20%26%20Bipartite%20Matching-purple.svg)

## 📌 Overview

Network Flow is one of the most versatile paradigms in combinatorial optimization. This module investigates the **Maximum Flow Problem**, the **Max-Flow Min-Cut Theorem**, and polynomial reductions from graph-theoretic and real-world problems to network flow:

1. **[Section A1A2: Operation Royal Mint (Edge-Disjoint Paths & Path Recovery)](file:///home/saif/Documents/DSA/CSE%20208/Max%20Flow/A1A2)**
2. **[Section B1B2: Owls and Mice (Bipartite Flow with Capacitated Sinks)](file:///home/saif/Documents/DSA/CSE%20208/Max%20Flow/B1B2)**
3. **[Section C1C2: Strategic Partnerships (Max Bipartite Matching with Multi-Attribute Filters)](file:///home/saif/Documents/DSA/CSE%20208/Max%20Flow/C1C2)**

---

## 🌊 Theoretical Principles

### 1. Flow Network Definition
A flow network $G = (V, E)$ is a directed graph with a source vertex $s$, a sink vertex $t$, and non-negative edge capacities $c(u, v) \ge 0$. A valid flow $f: V \times V \to \mathbb{R}$ satisfies:
1. **Capacity Constraint**: $0 \le f(u, v) \le c(u, v)$ for all $(u, v) \in E$.
2. **Flow Conservation**: $\sum_{u \in V} f(u, v) = \sum_{w \in V} f(v, w)$ for all $v \in V \setminus \{s, t\}$.

### 2. Residual Graph & Edmonds-Karp Algorithm
The residual network $G_f$ defines available residual capacities:
$$c_f(u, v) = c(u, v) - f(u, v) \quad \text{and} \quad c_f(v, u) = f(u, v)$$
The **Edmonds-Karp algorithm** implements the Ford-Fulkerson method by finding augmenting paths using **Breadth-First Search (BFS)** (shortest augmenting path in terms of edge count).
- **Time Complexity**: $\mathcal{O}(V \cdot E^2)$
- **Termination Guarantee**: Proven polynomial time, independent of edge capacity magnitudes.

### 3. Max-Flow Min-Cut Theorem
> The maximum value of an $s-t$ flow equals the minimum capacity among all cuts $(S, T)$ separating $s$ and $t$.

---

## 🔍 Problem Reductions & Solutions

### 1. Operation Royal Mint (`Max Flow/A1A2`)
- **Objective**: Find the maximum number of mutually **edge-disjoint escape routes** from the Royal Mint (location 1) to the safe zone (location $N$) through an underground tunnel network.
- **Reduction**:
  - Model every underground corridor $(u, v)$ as a directed edge with **unit capacity** $c(u, v) = 1$.
  - Run Edmonds-Karp BFS to find augmenting paths.
  - Because capacities are integral ($c = 1$), by the **Integrality Theorem**, the resulting flow decomposes into $|f^*|$ edge-disjoint paths.
- **Path Decomposition**:
  - Use DFS on edges where $f(u, v) > 0$ to extract and print the explicit vertex sequences of all independent escape paths.

### 2. Owls and Mice (`Max Flow/B1B2`)
- **Objective**: Given $M$ mice at 2D positions $(x_i, y_i)$, $H$ burrows at $(x_j, y_j)$ each with capacity $C_j$, and maximum running distance $R$, determine the number of mice that cannot reach safety before owls strike.
- **Flow Network Construction**:
  ```text
            [Capacity 1]                [Capacity 1]               [Capacity C_j]
  Source S -------------> Mouse i ------------------------> Hole j --------------> Sink T
                                   (if dist(i, j) <= R)
  ```
  - Total safe mice = $\text{MaxFlow}(S \to T)$.
  - Endangered mice = $M - \text{MaxFlow}(S \to T)$.

### 3. Strategic Partnerships (`Max Flow/C1C2`)
- **Objective**: Form maximum mutually compatible pairs between gang members (Left partition) and business partners (Right partition).
- **Compatibility Criteria**:
  An edge exists between gang member $u$ and business partner $v$ iff all conditions hold:
  - Experience gap $\le$ allowable threshold
  - Age difference criteria
  - Clean criminal record verification
  - Geographic territory overlap
  - Weapon proficiency level
  - Minimum trust rating
  - Common spoken language
- **Algorithm**: **Kuhn's Algorithm** (Augmenting path DFS for maximum bipartite matching) in $\mathcal{O}(|V| \cdot |E|)$ time and $\mathcal{O}(|V|)$ extra space.

---

## 📊 Summary of Problem Reductions

| Problem | Domain | Reduction Technique | Algorithm Used | Complexity |
|---|---|---|---|---|
| **Online A (Royal Mint)** | Edge-Disjoint Paths | Unit-capacity network | Edmonds-Karp + Path DFS | $\mathcal{O}(V \cdot E^2)$ |
| **Online B (Owls and Mice)** | Capacitated Assignment | Bipartite flow with sink capacities | Edmonds-Karp | $\mathcal{O}(V \cdot E^2)$ |
| **Online C (Strategic)** | Maximum Bipartite Matching | Filtered compatibility graph | Kuhn's DFS Matching | $\mathcal{O}(V \cdot E)$ |

---

## 📁 Directory Structure

```text
Max Flow/
├── A1A2/
│   ├── OnlineA_RoyalMint_MaxFlow.cpp        # Edge-disjoint flow + path extraction
│   └── Online A - Problem Statement.pdf
├── B1B2/
│   ├── 2205119.cpp                          # Bipartite matching flow with hole capacities
│   └── Online B - Problem Statement.pdf
└── C1C2/
    ├── OnlineC_StrategicPartnership_MaxFlow.cpp # Kuhn's multi-attribute matching
    └── Online C - Problem Statement.pdf
```

---

## 💻 Compilation & Execution

```bash
# Compile and run Royal Mint
cd "A1A2"
g++ -std=c++17 -Wall -Wextra -O2 OnlineA_RoyalMint_MaxFlow.cpp -o royal_mint
./royal_mint

# Compile and run Owls and Mice
cd "../B1B2"
g++ -std=c++17 -Wall -Wextra -O2 2205119.cpp -o owls_mice
./owls_mice

# Compile and run Strategic Partnership
cd "../C1C2"
g++ -std=c++17 -Wall -Wextra -O2 OnlineC_StrategicPartnership_MaxFlow.cpp -o strategic
./strategic
```
