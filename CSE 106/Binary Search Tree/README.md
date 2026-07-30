# 🌳 Binary Search Tree (BST) Implementation

<div align="center">

**Course:** CSE 106 – Data Structures  
**Author:** Saif Al Islam  
**Student ID:** 2205119  
**Date:** January 2024

</div>

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Assignment 4 – Offline BST Operations](#-assignment-4--offline-bst-operations)
  - [Insert](#insert)
  - [Delete](#delete)
  - [Find](#find)
  - [Traversals](#traversals)
  - [Parentheses Representation](#parentheses-representation)
- [Online Problem A – Lowest Common Ancestor (LCA)](#-online-problem-a--lowest-common-ancestor-lca)
- [Online Problem B – Second Largest Value](#-online-problem-b--second-largest-value)
- [Online Problem C – Count Nodes in Range](#-online-problem-c--count-nodes-in-range)
- [Project Structure](#-project-structure)
- [Complexity Summary](#-complexity-summary)
- [Conclusion](#-conclusion)

---

# 🌲 Overview

A **Binary Search Tree (BST)** is a binary tree that satisfies the following properties:

- Every node in the **left subtree** contains a value **smaller** than the current node.
- Every node in the **right subtree** contains a value **greater** than the current node.
- Both subtrees are themselves Binary Search Trees.
- All keys are **unique**.

BSTs provide efficient searching, insertion, and deletion.

| Operation | Average | Worst |
|-----------|---------|-------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |

---

# 📚 Assignment 4 – Offline BST Operations

## Insert

**Function**

```cpp
Node* insertNode(Node* node, int val);
```

### Algorithm

- Compare `val` with the current node.
- Move left if smaller.
- Move right if greater.
- Create a new node when a `nullptr` is reached.
- Return the updated root.

**Complexity**

```
Average : O(log n)
Worst   : O(n)
```

---

## Delete

**Function**

```cpp
Node* deleteNode(Node* node, int val);
```

### Cases

### 1. Leaf Node

Simply delete the node.

### 2. One Child

Replace the node with its existing child.

### 3. Two Children

- Find the **in-order successor**
- Copy its value
- Delete the successor recursively

**Complexity**

```
Average : O(log n)
Worst   : O(n)
```

---

## Find

**Function**

```cpp
Node* find(Node* node, int val);
```

### Algorithm

- Compare the value.
- Search left if smaller.
- Search right if greater.
- Return the node if found.
- Otherwise return `nullptr`.

**Complexity**

```
Average : O(log n)
Worst   : O(n)
```

---

## Traversals

Three traversal methods are implemented.

### In-order

```
Left → Root → Right
```

Produces the values in **sorted order**.

---

### Pre-order

```
Root → Left → Right
```

Useful for copying the tree.

---

### Post-order

```
Left → Right → Root
```

Useful for deleting the tree.

Each traversal visits every node exactly once.

**Complexity**

```
O(n)
```

---

## Parentheses Representation

**Function**

```cpp
void printTree(Node* root);
```

### Rules

- Empty subtree → `_`
- Non-empty node → `value(left,right)`

Example

```
5 (3 (0, _), 9 (7, 10))
```

This format is printed after every insertion and deletion.

---

# 🌟 Online Problem A – Lowest Common Ancestor (LCA)

## Problem

Given two values already present in the BST, find their **Lowest Common Ancestor (LCA)**.

Example

```
L 7 10
```

Output

```
9
```

---

## Idea

Using BST properties:

- Both values smaller → go left.
- Both values larger → go right.
- Otherwise current node is the LCA.

### Implementation

```cpp
Node* lca(Node* node, int a, int b) {
    if (a < node->val && b < node->val)
        return lca(node->left, a, b);

    if (a > node->val && b > node->val)
        return lca(node->right, a, b);

    return node;
}
```

**Complexity**

```
O(h)
```

where **h** is the height of the tree.

---

# 🌟 Online Problem B – Second Largest Value

## Problem

Find the second largest element in the BST.

Example

BST

```
0 3 5 7 9 10
```

Output

```
9
```

---

## Algorithm

1. Move to the rightmost node.
2. If it has a left subtree:
   - Return the maximum element of that subtree.
3. Otherwise:
   - Return its parent.

### Implementation

```cpp
int getSecondLargest(Node* node) {
    Node* parent = nullptr;
    Node* cur = node;

    while (cur->right) {
        parent = cur;
        cur = cur->right;
    }

    if (cur->left) {
        cur = cur->left;

        while (cur->right)
            cur = cur->right;

        return cur->val;
    }

    return parent->val;
}
```

**Complexity**

```
O(h)
```

---

# 🌟 Online Problem C – Count Nodes in Range

## Problem

Count the number of nodes within an inclusive range.

Example

```
C 7 10
```

Output

```
3
```

---

## Algorithm

Prune unnecessary branches.

- Current value < start → visit right subtree only.
- Current value > end → visit left subtree only.
- Otherwise count the node and search both children.

### Implementation

```cpp
int countInRange(Node* node, int start, int end) {

    if (node == nullptr)
        return 0;

    if (node->val < start)
        return countInRange(node->right, start, end);

    if (node->val > end)
        return countInRange(node->left, start, end);

    return 1
        + countInRange(node->left, start, end)
        + countInRange(node->right, start, end);
}
```

**Complexity**

```
O(h + k)
```

where

- **h** = tree height
- **k** = nodes inside the range

---

# 📂 Project Structure

```text
Binary Search Tree/
│
├── Assignment/
│   ├── bst.h
│   ├── main.cpp
│   ├── input.txt
│   └── output.txt
│
└── Online/
    ├── A1_A2/
    │   ├── bst.h
    │   ├── a1a2.cpp
    │   └── input.txt
    │
    ├── B1_B2/
    │   ├── bst.h
    │   ├── b1b2.cpp
    │   └── input.txt
    │
    └── C1_C2/
        ├── bst.h
        ├── c1c2.cpp
        └── input.txt
```

All online problems reuse the same **bst.h** implementation and extend it with additional functionality.

---

# 📊 Complexity Summary

| Operation | Time Complexity |
|------------|-----------------|
| Insert | O(log n) average |
| Delete | O(log n) average |
| Search | O(log n) average |
| Traversals | O(n) |
| LCA | O(h) |
| Second Largest | O(h) |
| Count in Range | O(h + k) |

---

# ✅ Conclusion

This project provides a complete implementation of a **Binary Search Tree (BST)** along with several advanced operations.

Implemented features include:

- ✅ Insert
- ✅ Delete
- ✅ Search
- ✅ In-order Traversal
- ✅ Pre-order Traversal
- ✅ Post-order Traversal
- ✅ Parentheses Tree Representation
- ✅ Lowest Common Ancestor (LCA)
- ✅ Second Largest Element
- ✅ Count Nodes Within a Given Range

The implementation is modular, reusable, and follows the BST property to achieve efficient average-case performance.

---

<div align="center">

**CSE 106 — Data Structures**  
Made with ❤️ by **Saif Al Islam**

</div>
