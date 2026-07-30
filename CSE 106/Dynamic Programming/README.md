# 📘 Dynamic Programming Repository

<div align="center">

### **Author:** Saif Al Islam  
**Student ID:** 2205119  
**Course:** CSE 106 – Data Structures & Algorithms  
**Semester:** January 2024

</div>

---

## 📌 Overview

This repository contains solutions to several classic **Dynamic Programming (DP)** problems completed as part of the **CSE 106 coursework**. The repository includes one offline assignment and three online assessments.

Each problem demonstrates how Dynamic Programming transforms computationally expensive recursive solutions into efficient polynomial-time algorithms through:

- **Memoization (Top-Down DP)**
- **Tabulation (Bottom-Up DP)**

The problems covered include:

- Regular Expression Matching
- Knapsack with House Robber Constraints
- Edit Distance
- Longest Common Subsequence (LCS)

---

# 📚 Table of Contents

1. [Theory of Dynamic Programming](#-theory-of-dynamic-programming)
2. [Repository Structure](#-repository-structure)
3. [Problems Included](#-problems-included)
4. [Solution Approaches](#-solution-approaches)
5. [Complexity Analysis](#-complexity-analysis)
6. [How to Run](#-how-to-run)
7. [Conclusion](#-conclusion)

---

# 🧠 Theory of Dynamic Programming

Dynamic Programming (DP) is an algorithmic technique used to solve optimization and counting problems efficiently by storing previously computed results.

A problem is suitable for DP if it satisfies two important properties:

## 1️⃣ Optimal Substructure

The optimal solution of a problem can be constructed from optimal solutions of smaller subproblems.

Example:

```
LCS(A, B) =
    1 + LCS(A-1, B-1)   if characters match
    max(...)            otherwise
```

---

## 2️⃣ Overlapping Subproblems

The same subproblems appear repeatedly during computation.

Without DP:

```
Time Complexity → Exponential
```

With DP:

```
Time Complexity → Polynomial
```

---

## DP Approaches

### 🔹 Top-Down (Memoization)

- Uses recursion
- Stores already computed states
- Avoids repeated calculations

Example:

```cpp
if(dp[i][j] != -1)
    return dp[i][j];
```

---

### 🔹 Bottom-Up (Tabulation)

- Uses iterative computation
- Builds solutions from smaller states

Example:

```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        dp[i][j] = ...
```

---

# 📂 Repository Structure

```text
Dynamic Programming/
│
├── Assignment/
│   ├── Assignment 8_ Dynamic Programming.pdf
│   └── 2205119.cpp
│
└── Online/
    │
    ├── A1_A2/
    │   ├── Online A1_A2.pdf
    │   └── 2205119.cpp
    │
    ├── B1_B2/
    │   ├── Online B1_B2.pdf
    │   └── 2205119.cpp
    │
    └── C1_C2/
        ├── Online C1_C2.pdf
        └── 2205119.cpp
```

---

# 📖 Problems Included

---

## 1️⃣ Regular Expression Matching

📄 **File:** `Assignment/2205119.cpp`

### Problem Description

Given:

- Text string `s`
- Pattern `p`

Determine whether the entire text matches the pattern.

### Special Symbols

| Symbol | Meaning |
|----------|----------|
| `.` | Matches any single character |
| `*` | Zero or more occurrences |
| `+` | One or more occurrences |

Example:

```text
Text: aaab
Pattern: a+b

Result: Match
```

---

## 2️⃣ Knapsack + House Robber

📄 **File:** `Online/A1_A2/2205119.cpp`

### Problem Description

A robber wants to steal from houses while obeying two constraints:

### Constraints

✅ Total weight ≤ carrying capacity

✅ Adjacent houses cannot both be robbed

Goal:

```text
Maximize total value
```

This problem combines:

- 0/1 Knapsack
- House Robber DP

---

## 3️⃣ Edit Distance

📄 **File:** `Online/B1_B2/2205119.cpp`

### Problem Description

Find the minimum number of operations needed to convert one string into another.

Allowed operations:

| Operation | Cost |
|------------|-------|
| Insert | 1 |
| Delete | 1 |
| Replace | 1 |

Example:

```text
horse → ros

horse
↓ delete h
orse
↓ replace o→r
rrse
↓ delete e

Distance = 3
```

This is also known as:

> **Levenshtein Distance**

---

## 4️⃣ Longest Common Subsequence (LCS)

📄 **File:** `Online/C1_C2/2205119.cpp`

### Problem Description

Find the longest subsequence common to two strings.

Example:

```text
ABCBDAB
BDCABA

LCS = BCBA
Length = 4
```

Unlike substrings:

✅ Characters must preserve order

❌ Need not be contiguous

---

# ⚙️ Solution Approaches

---

## 🔹 Regular Expression Matching

### Method

✅ Top-Down Memoization

### DP State

```cpp
dp[i][j]
```

Meaning:

```text
Does s[0...i] match p[0...j]?
```

### Transitions

#### Character Match

```cpp
s[i] == p[j]
```

or

```cpp
p[j] == '.'
```

---

### `*`

Two possibilities:

```text
1. Ignore previous character
2. Use previous character repeatedly
```

---

### `+`

Two possibilities:

```text
1. Use exactly once
2. Use multiple times
```

---

## 🔹 Knapsack + House Robber

### DP State

```cpp
dp[i][w]
```

Meaning:

```text
Maximum value using first i houses
with capacity w
```

Transition:

```cpp
Skip house
Take house (using i-2)
```

Because:

```text
Adjacent houses cannot be selected.
```

---

## 🔹 Edit Distance

### DP State

```cpp
dp[i][j]
```

Meaning:

```text
Minimum operations to convert
X[0...i] → Y[0...j]
```

Transition:

```cpp
Insert
Delete
Replace
```

Formula:

```text
dp[i][j] =
1 + min(
    Insert,
    Delete,
    Replace
)
```

---

## 🔹 Longest Common Subsequence

### DP State

```cpp
dp[i][j]
```

Meaning:

```text
LCS length of first i characters
and first j characters.
```

Transition:

If equal:

```cpp
dp[i][j] = dp[i-1][j-1] + 1
```

Otherwise:

```cpp
dp[i][j] =
max(
    dp[i-1][j],
    dp[i][j-1]
)
```

---

# 📊 Complexity Analysis

| Problem | Time Complexity | Space Complexity |
|----------|----------------|-----------------|
| Regex Matching | O(n × m) | O(n × m) |
| Knapsack + House Robber | O(n × W) | O(n × W) |
| Edit Distance | O(n × m) | O(n × m) |
| LCS | O(n × m) | O(n × m) |

Where:

- `n` = length of first string / number of houses
- `m` = length of second string / pattern
- `W` = maximum carrying capacity

---

# ▶️ How to Run

Compile:

```bash
g++ 2205119.cpp -o output
```

Run:

```bash
./output
```

---

# 🎯 Conclusion

This repository demonstrates the application of **Dynamic Programming** to solve multiple optimization and string-processing problems efficiently.

The implemented solutions illustrate:

✅ Memoization

✅ Tabulation

✅ State Design

✅ Transition Formulation

✅ Constraint Handling

By reducing exponential recursion into polynomial-time solutions, Dynamic Programming provides elegant and efficient approaches for solving complex computational problems.

---

<div align="center">

⭐ If you find this repository useful, consider giving it a star!

</div>
