# Hash Tables: Collision Resolution, Dynamic Resizing & Multi-Tier Systems

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Hashing%20%26%20Collision%20Resolution-purple.svg)

## 📌 Overview

This directory contains three comprehensive hashing implementations:
1. **[Offline: Collision Resolution & Hash Function Benchmarking](file:///home/saif/Documents/DSA/CSE%20208/Hashing/Offline)** (Separate Chaining with Red-Black Trees, Linear Probing, Double Hashing).
2. **[Online Shift 1: Dynamic Memory Manager with Quadratic Probing](file:///home/saif/Documents/DSA/CSE%20208/Hashing/Hashing_Online_Shift_1)** (Scale-up on probe threshold, scale-down on low load factor, statistics tracking).
3. **[Online Shift 2: Two-Layer Open-Addressing Permission Database](file:///home/saif/Documents/DSA/CSE%20208/Hashing/Hashing_Online_Shift_2)** (Outer table linear probing, inner table quadratic probing, key update mechanics).

---

## 🔬 Collision Resolution Techniques

```text
                                Collision Resolution
                               /                    \
              Closed Addressing (Chaining)          Open Addressing (Probing)
                         |                         /            |            \
                 Red-Black Trees            Linear           Quadratic     Double
                 O(1 + log(L))              Probing          Probing       Hashing
```

### 1. Separate Chaining with Red-Black Trees (`separate_chaining.h`)
Instead of standard singly-linked lists that degrade to $\mathcal{O}(N)$ under high collision clustering, each bucket in this implementation is a **Red-Black Tree**.
- Worst-case search within a bucket: $\mathcal{O}(\log L)$, where $L$ is bucket size.
- Handles load factors $\alpha \ge 1.0$ gracefully without rehashing.

### 2. Linear Probing (`linear_probing.h`)
- Probing Sequence: $h(k, i) = (h_1(k) + i \cdot c) \bmod M$, for $i = 0, 1, 2, \dots$
- Advantages: Excellent cache locality due to sequential memory access.
- Disadvantages: Susceptible to **Primary Clustering** (long contiguous blocks of occupied slots that snowball over time).

### 3. Double Hashing (`double_hashing.h`)
- Probing Sequence: $h(k, i) = (h_1(k) + i \cdot h_2(k)) \bmod M$.
- Step function $h_2(k)$ is coprime to $M$ (guaranteed when $M$ is prime).
- Eliminates both primary and secondary clustering.
- Robust implementation: Computes `idx = (idx1 + 1LL * i * idx2) % tablesize` at iteration $i$, preventing double-probing index 0 and reusing deleted slots safely.

---

## ⚙ Advanced Implementations

### 1. Online Shift 1: Dynamic Memory Manager (`Hashing_Online_Shift_1`)
Simulates an OS fixed-size memory block allocator with dynamic table resizing:
- **Quadratic Probing**: $h(k, j) = (k + j^2) \bmod M$.
- **Slot States**: `EMPTY (0)`, `OCCUPIED (1)`, `DELETED (2)`.
- **Scale-Up Rehash**:
  - Trigger: Insertion probe sequence exceeds $P_{\max}$.
  - Action: Table resizes to next prime $\ge 2 \times M$. All active elements are rehashed (DELETED slots are purged). The pending process is inserted into the new table.
- **Scale-Down Rehash**:
  - Trigger: After every 5 deletions, if $\alpha = \frac{\text{Active}}{M} < 0.2$.
  - Action: Table resizes to closest prime $\le M / 2$ (bounded below by initial size $N$).
- **Statistical Invariants**:
  - Outputs before/after reports of Table Size, Active Processes, Load Factor, and Max Probe Sequence.
  - Running `maxProbe` correctly resets after rehash to accurately reflect post-rehash probe efficiency.

### 2. Online Shift 2: Two-Layer Permission Database (`Hashing_Online_Shift_2`)
A hierarchical permission database:
- **Outer Table (Size $N$)**: Maps `group_id` $\to$ Pointer to `Inner Table` via DJB2 hash + Linear Probing.
- **Inner Table (Size $N$)**: Maps `user_id` $\to$ `permission` via modulo hash + Quadratic Probing.
- **Key Invariants**:
  - Duplicate user insertions under the same group update permissions in-place rather than creating duplicate entries.
  - Probing safely inspects deleted slots and reuses them only if the key is not already present further along the probe chain.
  - Line-based parsing (`getline` + `stringstream`) ensures whitespace-resilient command processing.

---

## ⏱ Complexity Summary

| Strategy / Problem | Average Search | Worst-Case Search | Insertion | Deletion |
|---|---|---|---|---|
| **Separate Chaining (RBT)** | $\mathcal{O}(1)$ | $\mathcal{O}(\log L)$ | $\mathcal{O}(1)$ | $\mathcal{O}(1)$ |
| **Linear Probing** | $\mathcal{O}\left(\frac{1}{1 - \alpha}\right)$ | $\mathcal{O}(M)$ | $\mathcal{O}\left(\frac{1}{(1 - \alpha)^2}\right)$ | $\mathcal{O}(1)$ |
| **Double Hashing** | $\mathcal{O}\left(\frac{1}{\alpha} \ln \frac{1}{1 - \alpha}\right)$ | $\mathcal{O}(M)$ | $\mathcal{O}\left(\frac{1}{1 - \alpha}\right)$ | $\mathcal{O}(1)$ |
| **Dynamic Memory Manager** | $\mathcal{O}(P_{\max})$ | $\mathcal{O}(M)$ | $\mathcal{O}(P_{\max})$ (amortized) | $\mathcal{O}(M)$ |

---

## 📁 Directory Structure

```text
Hashing/
├── Offline/
│   ├── 2205119.cpp              # Benchmarking driver for collision methods
│   ├── double_hashing.h         # Double hashing open addressing
│   ├── linear_probing.h         # Linear probing open addressing
│   ├── separate_chaining.h      # Red-Black Tree separate chaining
│   └── redblack_2205119.h
├── Hashing_Online_Shift_1/
│   ├── main.cpp                 # Quadratic memory manager with dynamic rehash
│   ├── input1.txt, input2.txt
│   └── output1.txt, output2.txt
└── Hashing_Online_Shift_2/
    └── main.cpp                 # Two-layer permission database
```

---

## 💻 Compilation & Testing

```bash
# Shift 1 Online (Exact match verification)
cd "Hashing_Online_Shift_1"
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o shift1
./shift1 < input1.txt | diff -u - output1.txt
./shift1 < input2.txt | diff -u - output2.txt

# Shift 2 Online
cd "../Hashing_Online_Shift_2"
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o shift2
./shift2

# Offline Benchmark
cd "../Offline"
g++ -std=c++17 -Wall -Wextra -O2 2205119.cpp -o benchmark
./benchmark
```
