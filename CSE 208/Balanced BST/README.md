# Inventory Management System via Self-Balancing Red-Black Tree

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-Balanced%20Binary%20Search%20Trees-purple.svg)

## 📌 Overview

This project implements a fully featured, high-performance **Inventory Management System** backed by a **Red-Black Tree (RBT)** data structure in modern C++. The Red-Black Tree provides guaranteed $\mathcal{O}(\log N)$ worst-case time complexity for all primary operations (search, insertion, deletion, and updates) by maintaining logarithmic height balance through coloring rules and tree rotations.

The system features cross-platform colored terminal visualization (Windows Console API and Linux ANSI escapes) and robust sentinel-node memory management.

---

## 🌲 Red-Black Tree Invariants

A Red-Black Tree is a binary search tree where each node stores a color bit (`RED` or `BLACK`) satisfying five invariants:
1. **Node Color**: Every node is either `RED` or `BLACK`.
2. **Root Property**: The root node is always `BLACK`.
3. **Leaf Property**: Every leaf (`NIL` sentinel) is `BLACK`.
4. **Red Invariant**: If a node is `RED`, both of its children must be `BLACK` (no two `RED` nodes can be adjacent).
5. **Black Height Invariant**: For every node $x$, all simple paths from $x$ to descendant leaves contain the same number of `BLACK` nodes ($\text{bh}(x)$).

### Height Guarantee
From these invariants, a Red-Black tree with $N$ internal nodes has height at most:
$$h \le 2 \log_2(N + 1)$$
guaranteeing $\mathcal{O}(\log N)$ worst-case search, insertion, and deletion times.

---

## ⚙ System Operations

| Command | Syntax | Functionality | Complexity |
|---|---|---|---|
| **Add Item** | `AI <id> <name> <stock>` | Inserts a new product or updates existing item details if ID exists | $\mathcal{O}(\log N)$ |
| **Buy Item** | `BI <id> <qty>` | Decrements stock; if stock reaches $0$, deletes node and triggers delete fixup | $\mathcal{O}(\log N)$ |
| **Check Item** | `CI <id>` | Queries product availability and prints current stock count | $\mathcal{O}(\log N)$ |
| **Clear Inventory** | `Clr` | Recursively deallocates all nodes and resets tree to empty state | $\mathcal{O}(N)$ |
| **Inventory Size** | `S` | Outputs the current count of active distinct items | $\mathcal{O}(1)$ |
| **Empty Check** | `Em` | Prints `True` if tree is empty, else `False` | $\mathcal{O}(1)$ |
| **List Inventory** | `Itr` | Inorder traversal (`Left` $\to$ `Root` $\to$ `Right`), printing products sorted by ID | $\mathcal{O}(N)$ |

---

## 🔄 Balancing Mechanics & Tree Rotations

### Rotations
Tree rotations preserve binary search tree order while restructuring local tree height:
```text
        y                               x
       / \     Right Rotation (y)      / \
      x   γ   -------------------->   α   y
     / \       <-------------------      / \
    α   β      Left Rotation (x)        β   γ
```

### Insertion Fixup
After inserting a node $z$ (colored `RED` initially like standard BST insertion), red-red violations are resolved:
- **Case 1 (Uncle is RED)**: Recolor parent, uncle, and grandparent; propagate check up to grandparent.
- **Case 2 (Uncle is BLACK, triangle formed)**: Rotate parent to convert triangle into a straight line.
- **Case 3 (Uncle is BLACK, straight line formed)**: Rotate grandparent and recolor parent and grandparent.

### Deletion Fixup
When a `BLACK` node is removed, a "double black" deficiency is introduced at sentinel node $x$:
- **Case 1**: Sibling $w$ is `RED` $\to$ Rotate parent and recolor to make sibling `BLACK`.
- **Case 2**: Sibling $w$ is `BLACK`, both children of $w$ are `BLACK` $\to$ Recolor $w$ to `RED` and push deficiency up.
- **Case 3**: Sibling $w$ is `BLACK`, near child of $w$ is `RED`, far child is `BLACK` $\to$ Rotate sibling.
- **Case 4**: Sibling $w$ is `BLACK`, far child of $w$ is `RED` $\to$ Rotate parent, recolor, remove deficiency.

---

## 📁 Repository Files

- [`2205119.cpp`](file:///home/saif/Documents/DSA/CSE%20208/Balanced%20BST/2205119.cpp): Main driver program managing file streams (`input.txt` $\to$ `output.txt`).
- [`inventory_2205119.h`](file:///home/saif/Documents/DSA/CSE%20208/Balanced%20BST/inventory_2205119.h): `Inventory` business logic wrapper.
- [`redblack_2205119.h`](file:///home/saif/Documents/DSA/CSE%20208/Balanced%20BST/redblack_2205119.h): Complete Red-Black Tree implementation with fixup routines.
- [`color.hpp`](file:///home/saif/Documents/DSA/CSE%20208/Balanced%20BST/color.hpp): Cross-platform terminal color library supporting Windows Console API and Linux ANSI codes.

---

## 💻 Compilation & Execution

```bash
# Compile with all warnings enabled
g++ -std=c++17 -Wall -Wextra -O2 2205119.cpp -o rbt_inventory

# Run using input file
./rbt_inventory
# Outputs are generated in output.txt
```
