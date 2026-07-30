# Divide and Conquer – Assignments & Online Problems

> A collection of **Divide and Conquer** problems implemented in **C++** as part of the **Data Structures and Algorithms (DSA)** course.

The repository contains one offline assignment and three online assessments. Each problem is solved using the **divide-and-conquer paradigm**, emphasizing recursive decomposition, efficient merging of subproblems, and asymptotic analysis.

---

## 👨‍💻 Author

**Saif Al Islam**  
**Student ID:** 2205119

---

# 📂 Repository Structure

```text
Divide and Conquer/
├── Assignment/
│   ├── DSA-1 Assignment - 7 Divide and Conquer.pdf
│   └── 2205119.cpp
│
└── Online/
    ├── A1_A2/
    │   ├── Online A1_A2 Divide and Conquer.pdf
    │   └── a1a2.cpp
    │
    ├── B1_B2/
    │   ├── Online B1_B2 Divide and Conquer.pdf
    │   └── b1b2.cpp
    │
    └── C1_C2/
        ├── Online C1_C2 Divide and Conquer.pdf
        └── c1c2.cpp
```

---

# 📚 Contents

- Assignment – Shortest Hottest Streak (Maximum Subarray)
- Online A – Count Adjacent Inverted Pairs
- Online B – Count Unique Elements in a Sorted Array
- Online C – Count Inversions in an Array

---

# 1️⃣ Assignment – Shortest Hottest Streak

## 📖 Problem

Given an array of integers:

- Positive values represent **points gained**
- Negative values represent **penalties**

Find the **contiguous subarray** whose sum is maximum.

### Tie-breaking Rule

If multiple subarrays have the same maximum sum, return the **shortest** one.

---

## Example

```text
Input
[6, 3, -10, 3, -2, 5, -1, 4]

Output
[6, 3]

Maximum Sum = 9
```

Although

```text
[3, -2, 5, -1, 4]
```

also has sum **9**, its length is **5**, while `[6, 3]` has length **2**, so the shorter streak is selected.

---

# 💡 Divide and Conquer Idea

The maximum subarray must belong to exactly one of three categories:

1. Completely inside the left half
2. Completely inside the right half
3. Crossing the midpoint

Therefore, the array is recursively divided into two halves.

At every recursive call:

- solve the left half
- solve the right half
- compute the best crossing subarray
- choose the best among the three candidates

This guarantees that every possible maximum subarray is considered.

---

# 🔍 Tie-breaking Strategy

The repository extends the classical Maximum Subarray algorithm by introducing an additional comparison rule.

Candidates are compared in the following order:

1. Larger sum
2. If sums are equal, shorter length
3. If both are equal, either solution is acceptable (the implementation returns the rightmost one)

---

# ⚙️ Main Functions

| Function | Purpose |
|----------|---------|
| `cross()` | Computes the best subarray crossing the midpoint |
| `gb()` | Compares two candidate answers using the tie-breaking rules |
| `hot()` | Recursive divide-and-conquer driver |

---

# ✅ Important Correction

The originally submitted solution treated every **non-positive total sum** as an **empty subarray with sum 0**.

However, the problem requires selecting a **non-empty continuous subarray**.

The corrected implementation removes that special case.

Example:

```text
Input
[-2, -5, -1]

Correct Output
[-1]

Maximum Sum = -1
```

---

# ⏱ Complexity

| Metric | Complexity |
|---------|------------|
| Time | **O(n log n)** |
| Space | **O(n)** |

---

# 2️⃣ Online A – Count Adjacent Inverted Pairs

## 📖 Problem

Given a string consisting of lowercase English letters, count the number of **adjacent inverted pairs**.

A pair

```
(s[i], s[i+1])
```

is inverted if

```
s[i] > s[i+1]
```

alphabetically.

---

## Example

```text
Input
abdcbabxawer

Output
5
```

The inverted pairs are

```text
dc
cb
ba
xa
we
```

---

# 💡 Divide and Conquer Idea

Every adjacent pair belongs to exactly one of three cases:

- entirely in the left half
- entirely in the right half
- crossing the midpoint

Notice something interesting:

Only **one adjacent pair** crosses the midpoint:

```text
s[mid], s[mid+1]
```

Therefore,

```
Answer =
Left Answer
+ Right Answer
+ Boundary Pair
```

Since every adjacent pair becomes the boundary pair at exactly one recursive level, each pair is counted exactly once.

---

# Sample Implementation

```cpp
int countAdjacentInverted(const string& s, int l, int r) {
    if (l >= r) return 0;
    if (l + 1 == r)
        return (s[l] > s[r]);

    int mid = l + (r - l) / 2;

    int left = countAdjacentInverted(s, l, mid);
    int right = countAdjacentInverted(s, mid + 1, r);
    int cross = (s[mid] > s[mid + 1]);

    return left + right + cross;
}
```

---

# ⏱ Complexity

| Metric | Complexity |
|---------|------------|
| Time | **O(n)** |
| Space | **O(log n)** |

---

# 3️⃣ Online B – Count Unique Elements in a Sorted Array

## 📖 Problem

Given a **sorted** array (non-decreasing order), determine the number of **distinct values**.

---

## Example

```text
Input
1 2 2 2 3 4

Output
4
```

Distinct values:

```text
1 2 3 4
```

---

## Another Example

```text
Input
4 5 6 7 8

Output
5
```

---

# 💡 Key Observation

Since the array is sorted,

- equal values always appear consecutively.

Instead of counting unique values directly, count the number of **adjacent equal pairs**.

If

```
equalAdjacentPairs = x
```

then

```
Unique Elements = n - x
```

---

# Divide and Conquer Strategy

For every recursive call:

- Count equal pairs in the left half.
- Count equal pairs in the right half.
- Check the midpoint pair only.

```
arr[mid] == arr[mid+1]
```

If true, increment the duplicate counter.

Every adjacent pair is examined exactly once throughout the recursion.

---

# Sample Implementation

```cpp
void sol(vector<int>& arr, int l, int h, int& duplicates) {
    if (l >= h) return;

    int m = l + (h - l) / 2;

    sol(arr, l, m, duplicates);
    sol(arr, m + 1, h, duplicates);

    if (arr[m] == arr[m + 1])
        duplicates++;
}
```

Final answer:

```cpp
cout << n - duplicates << endl;
```

---

# ⏱ Complexity

| Metric | Complexity |
|---------|------------|
| Time | **O(n)** |
| Space | **O(log n)** |

---

# 4️⃣ Online C – Count Inversions in an Array

## 📖 Problem

Given an array,

count the number of pairs

```
(i, j)
```

such that

```
i < j
arr[i] > arr[j]
```

These pairs are called **inversions**.

The inversion count measures how far an array is from being sorted.

---

## Example

```text
Input
1 4 2 3 5

Output
2
```

Inversions:

```
(4,2)
(4,3)
```

---

## Another Example

```text
Input
2 4 1 3 5

Output
3
```

Inversions:

```
(2,1)
(4,1)
(4,3)
```

---

# 💡 Divide and Conquer Idea

The classical solution modifies **Merge Sort**.

The inversion count is composed of three parts:

- inversions in the left half
- inversions in the right half
- inversions crossing the midpoint

The first two are obtained recursively.

Cross inversions are counted while merging.

---

# Counting Cross Inversions

During merge:

- if

```
arr[i] <= arr[j]
```

copy the left element.

Otherwise,

```
arr[i] > arr[j]
```

Since both halves are already sorted,

every remaining element from

```
i ... mid
```

is also greater than `arr[j]`.

Therefore,

```
cross += mid - i + 1
```

This counts all cross inversions in one step.

---

# Sample Merge Function

```cpp
long long merge(vector<int>& arr, int l, int m, int r) {

    vector<int> temp(r - l + 1);

    int i = l;
    int j = m + 1;
    int k = 0;

    long long inv = 0;

    while (i <= m && j <= r) {

        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            inv += (m - i + 1);
            temp[k++] = arr[j++];
        }
    }

    return inv;
}
```

Using `<=` ensures that duplicate values are **not** counted as inversions.

---

# ⏱ Complexity

| Metric | Complexity |
|---------|------------|
| Time | **O(n log n)** |
| Space | **O(n)** |

---

# 📊 Complexity Summary

| Problem | Technique | Time | Space |
|----------|-----------|------|-------|
| Shortest Hottest Streak | Maximum Subarray (Divide & Conquer) | **O(n log n)** | **O(n)** |
| Count Adjacent Inverted Pairs | Boundary Pair Counting | **O(n)** | **O(log n)** |
| Count Unique Elements | Adjacent Equal Pair Counting | **O(n)** | **O(log n)** |
| Count Inversions | Modified Merge Sort | **O(n log n)** | **O(n)** |

---

# 🎯 Key Concepts Demonstrated

This repository showcases several important Divide and Conquer techniques:

- Recursive decomposition of problems
- Solving independent subproblems
- Combining partial solutions efficiently
- Boundary-case handling during merging
- Modified Merge Sort
- Recursive complexity analysis using recurrence relations
- Careful handling of edge cases and tie-breaking rules

---

# 📝 Notes

- All implementations are written in **C++**.
- Every solution strictly follows the **Divide and Conquer** paradigm.
- Edge cases such as duplicate values, all-negative arrays, and equal-answer tie-breaking are handled correctly.
- Each solution includes an efficient recursive strategy with asymptotically optimal complexity for its respective problem.

---

## ⭐ If you found this repository helpful, consider giving it a star!
