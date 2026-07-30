# Stack Data Structure – Implementation & Applications

> **Author:** Saif Al Islam
> **Student ID:** 2205119

---

## 📚 Overview

This project demonstrates the **Stack** data structure, its implementation in C++, and several practical applications of stacks.

A stack follows the **Last-In-First-Out (LIFO)** principle: the element inserted last is the first element removed.

The project contains:

* Two stack implementations:

  * Array-based stack
  * Linked-list-based stack
* An offline assignment for testing stack operations
* Three online problems:

  * Sorting a stack
  * Counting recursive Fibonacci calls
  * Finding buildings visible from the right

The implementations use only the stack operations provided by the Stack ADT. No STL containers such as `vector`, `stack`, or other auxiliary data structures are used.

---

## 📁 Project Structure

```text
Stack/
│
├── Assignment/
│   ├── StackArray.h
│   ├── StackLinkedList.h
│   ├── main_array_stack.cpp
│   ├── main_list_stack.cpp
│   ├── input.txt
│   └── output.txt
│
└── Onlines/
    │
    ├── Online_A1A2/
    │   ├── online_a1a2.cpp
    │   ├── input.txt
    │   └── output.txt
    │
    ├── Online_B1B2/
    │   ├── online_b1b2.cpp
    │   ├── input.txt
    │   └── output.txt
    │
    └── Online_C1C2/
        ├── online_c1c2.cpp
        ├── input.txt
        └── output.txt
```

---

# 1. Stack – Core Concepts

A **stack** is a linear data structure in which insertion and deletion take place at the same end, called the **top**.

The stack follows the:

> **LIFO — Last-In, First-Out**

principle.

A simple analogy is a stack of plates. When a new plate is placed on top, it is also the first plate that can be removed.

### Fundamental Operations

| Operation   | Description                                    |
| ----------- | ---------------------------------------------- |
| `push(x)`   | Inserts `x` at the top of the stack.           |
| `pop()`     | Removes and returns the top element.           |
| `top()`     | Returns the top element without removing it.   |
| `isEmpty()` | Checks whether the stack contains no elements. |
| `length()`  | Returns the number of elements.                |
| `clear()`   | Removes all elements from the stack.           |

---

## LIFO Example

Consider the following sequence:

```text
push(5)
```

```text
[5]
```

Then:

```text
push(10)
```

```text
[5, 10]
```

The top is `10`.

Now:

```text
pop()
```

returns:

```text
10
```

and the stack becomes:

```text
[5]
```

Next:

```text
push(3)
```

gives:

```text
[5, 3]
```

Therefore:

```text
top()      → 3
isEmpty()  → false
clear()    → []
```

The important idea is that **the most recently inserted element is always removed first**.

---

# 2. Stack Implementation in C++

Two different implementations of the Stack ADT are provided:

1. **Array-based Stack**
2. **Linked-list-based Stack**

Both implementations expose the same basic interface, allowing the same algorithms to work with either implementation.

---

# 2.1 Array-Based Stack

The array implementation maintains:

* A dynamic array
* `size` — the current number of elements
* `capacity` — the amount of allocated storage

When the array becomes full, its capacity is increased.

### Dynamic Resizing

When:

```text
size == capacity
```

the capacity is doubled.

For example:

```text
capacity = 1
    ↓
capacity = 2
    ↓
capacity = 4
    ↓
capacity = 8
    ↓
...
```

When elements are removed and the stack becomes sufficiently empty, the array can also be reduced to save memory.

The implementation shrinks the array when:

```text
size <= capacity / 4
```

while ensuring that the capacity never becomes smaller than `1`.

### Important Operations

```cpp
void push(int x) {
    if (size == capacity)
        resize(capacity * 2);

    array[size++] = x;
}
```

The `push()` operation first checks whether there is enough space. If the array is full, it is resized before inserting the new element.

```cpp
int pop() {
    if (size == 0)
        return -1;

    int x = array[--size];

    if (size <= capacity / 4)
        resize(capacity / 2);

    return x;
}
```

The `pop()` operation removes the element at the top of the stack and may reduce the array's capacity if there is too much unused space.

### Advantages

* Simple implementation
* Good memory locality
* `push()` and `pop()` are normally `O(1)`
* Dynamic resizing allows the stack to grow as needed

### Disadvantages

* Resizing requires copying elements
* The array needs a contiguous block of memory

---

# 2.2 Linked-List-Based Stack

The linked-list implementation uses a singly linked list.

Each node contains:

```text
+---------+----------+
|  data   |   next   |
+---------+----------+
```

The first node represents the **top of the stack**.

The stack maintains a pointer:

```cpp
topNode
```

which points to the first node.

### Push Operation

A new node is created and inserted at the beginning of the list.

```cpp
void push(int x) {
    Node* newNode = new Node(x, topNode);
    topNode = newNode;
    currentSize++;
}
```

Because insertion takes place at the front, the operation takes `O(1)` time.

### Pop Operation

The first node is removed:

```cpp
int pop() {
    if (isEmpty())
        return -1;

    Node* temp = topNode;
    int value = temp->data;

    topNode = topNode->next;

    delete temp;
    currentSize--;

    return value;
}
```

The `delete` operation is important because it prevents a **memory leak**.

### Advantages

* No fixed capacity
* No array resizing is required
* `push()` and `pop()` are `O(1)`
* Memory is allocated as elements are added

### Disadvantages

* Each element requires additional memory for a pointer
* Nodes are dynamically allocated
* Memory is not necessarily contiguous

---

# 3. Offline Assignment – Stack Implementation

## Objective

The offline assignment requires a complete integer Stack ADT implemented using:

* A dynamic array
* A singly linked list

Both implementations are tested using driver programs.

The driver programs read commands from `input.txt` and write the results to `output.txt`.

---

## Supported Commands

| Command | Operation                        |
| ------- | -------------------------------- |
| `1 x`   | Push `x` onto the stack          |
| `2`     | Pop and print the top element    |
| `3`     | Print the top element            |
| `4`     | Print the stack length           |
| `5`     | Check whether the stack is empty |
| `6`     | Clear the stack                  |

After every operation, the current stack is printed from **bottom to top**.

---

## Example Input

```text
1 10
1 20
2
3
4
5
6
```

## Example Output

```text
Pushed 10 onto the stack.
Current stack: 10
-------------------
Pushed 20 onto the stack.
Current stack: 10 20
-------------------
Popped value: 20
Current stack: 10
-------------------
Top value: 10
Current stack: 10
-------------------
Current stack length: 1
Current stack: 10
-------------------
Is stack empty? No
Current stack: 10
-------------------
Cleared the stack.
Current stack:
-------------------
```

### Edge Cases

The implementations also handle situations such as:

* Popping from an empty stack
* Calling `top()` on an empty stack
* Clearing an already-empty stack
* Array expansion
* Array shrinking
* Repeated push/pop operations
* Proper deletion of linked-list nodes

---

# 4. Online A1A2 – Sorting a Stack

## Problem

Given a stack of integers, sort it so that the **smallest element is at the top**.

The restriction is that only **one auxiliary stack** may be used.

No arrays or other data structures are allowed.

---

## Approach

The algorithm is similar to **Insertion Sort**, but instead of using an array, it uses a second stack.

Let:

* `stack` = original stack
* `aux` = auxiliary stack

The algorithm repeatedly:

1. Pops an element `x` from the original stack.
2. Moves larger elements from `aux` back to the original stack.
3. Places `x` into its correct position in `aux`.
4. Repeats until the original stack becomes empty.
5. Moves all elements from `aux` back to the original stack.

### Implementation

```cpp
void sortStack(Stack &stack, FILE *outputFile) {
    Stack aux;

    while (!stack.isEmpty()) {
        int x = stack.pop();

        while (!aux.isEmpty() && aux.top() > x) {
            stack.push(aux.pop());
        }

        aux.push(x);
    }

    while (!aux.isEmpty()) {
        stack.push(aux.pop());
    }

    printStack(stack, outputFile);
}
```

### Why It Works

The auxiliary stack maintains a sorted order while elements are inserted.

Whenever a new element is smaller than the elements currently at the top of `aux`, those larger elements are temporarily moved back to the original stack.

Once the correct position is reached, the new element is pushed onto `aux`.

Finally, moving everything from `aux` back to the original stack reverses the order, placing the **smallest element at the top**.

---

## Example

Suppose the stack contains:

```text
Bottom → 4 10 3 6 4 8 3 5 ← Top
```

After sorting:

```text
Bottom → 10 8 6 5 4 4 3 3 ← Top
```

Therefore, when printed from bottom to top:

```text
10 8 6 5 4 4 3 3
```

and the top element is:

```text
3
```

This satisfies the requirement that the **smallest element is at the top**.

### Complexity

The worst-case time complexity is:

```text
O(n²)
```

because elements may need to be repeatedly moved between the two stacks.

The auxiliary space used is:

```text
O(n)
```

---

# 5. Online B1B2 – Counting Fibonacci Calls

## Problem

The goal is to determine how many times the recursive Fibonacci function is called during its execution, **without actually using recursion**.

Instead, a stack is used to simulate the recursive call tree.

---

## Fibonacci Definition

For this problem, the base cases are treated as:

```text
fib(1) = 1
fib(2) = 1
```

and for:

```text
n > 2
```

we have:

```text
fib(n) = fib(n-1) + fib(n-2)
```

Every invocation of `fib()` counts as one function call, including calls that reach the base cases.

---

## Recursive Call Tree

For example:

```text
fib(5)
├── fib(4)
│   ├── fib(3)
│   │   ├── fib(2)
│   │   └── fib(1)
│   └── fib(2)
└── fib(3)
    ├── fib(2)
    └── fib(1)
```

Counting every function invocation gives:

```text
fib(5) → 9 calls
```

---

## Stack-Based Simulation

Two stacks are used:

* `st` — stores every function call
* `temp` — stores calls that still need to be expanded

Initially:

```text
st.push(n)
temp.push(n)
```

Then, while `temp` is not empty:

1. Pop a value from `temp`.
2. If it is a base case (`1` or `2`), do nothing further.
3. Otherwise, generate its two recursive calls:

   * `curr - 1`
   * `curr - 2`
4. Push both calls onto `st`.
5. Push non-base calls onto `temp` so they can be expanded later.

### Implementation

```cpp
int countFibCalls(int n) {
    Stack st, temp;

    st.push(n);
    temp.push(n);

    while (!temp.isEmpty()) {
        int curr = temp.pop();

        if (curr == 1 || curr == 2)
            continue;

        int a = curr - 1;
        int b = curr - 2;

        st.push(a);
        st.push(b);

        if (a > 2)
            temp.push(a);

        if (b > 2)
            temp.push(b);
    }

    return st.length();
}
```

### Why It Works

Every function invocation in the recursive version corresponds to exactly one node in the recursion tree.

The `st` stack records every such call.

The `temp` stack acts as a work stack and allows the recursion tree to be explored without using actual recursive function calls.

---

## Sample Results

| `n` | Number of Calls |
| --: | --------------: |
|   5 |               9 |
|   8 |              41 |
|   9 |              67 |
|  10 |             109 |

These values match the expected number of calls for the Fibonacci definition used by the assignment.

---

# 6. Online C1C2 – Finding Visible Buildings

## Problem

Given an array of building heights from left to right, determine which buildings are visible when looking at them from the **right side**.

A building is visible if it is **strictly taller than every building to its right**.

---

## Example

Consider:

```text
4 10 3 6 4 8 3 5
```

Looking from the right:

* `5` is visible because nothing is to its right.
* `3` is blocked by `5`.
* `8` is visible because `8 > 5`.
* `4` is blocked by `8`.
* `6` is blocked by `8`.
* `3` is blocked by `8`.
* `10` is visible because `10 > 8`.
* `4` is blocked by `10`.

Therefore, the visible buildings are:

```text
5 8 10
```

in the order encountered from the right.

When printed from left to right, the result is:

```text
10 8 5
```

---

## Stack-Based Approach

The array is traversed from **right to left**.

A stack stores the buildings that are visible.

For each building height `h`:

* If the stack is empty, `h` is visible.
* Otherwise, if `h > stack.top()`, it is taller than every currently known visible building to its right, so it is also visible.
* Otherwise, it is blocked and is ignored.

### Implementation

```cpp
void findVisibleBuildings(int heights[], int n, FILE *outputFile) {
    Stack stack;

    for (int i = n - 1; i >= 0; --i) {
        if (stack.isEmpty() || heights[i] > stack.top()) {
            stack.push(heights[i]);
        }
    }

    fprintf(outputFile, "Visible buildings: ");
    printStack(stack, outputFile);
}
```

---

## Why It Works

When scanning from right to left, the stack contains the buildings that have been determined to be visible.

The top of the stack represents the nearest visible building on the right.

If the current building is taller than that building, it must also be visible because it is taller than every building that could block it.

This creates a **monotonic stack**.

The visible heights stored in the stack are increasing from bottom to top.

For:

```text
4 10 3 6 4 8 3 5
```

the final stack is:

```text
Bottom → 10 8 5 ← Top
```

Thus the left-to-right output is:

```text
10 8 5
```

### Complexity

Each building is processed once:

```text
Time Complexity:  O(n)
Space Complexity: O(n)
```

---

# 7. Comparison of the Two Stack Implementations

| Feature              | Array Stack                            | Linked-List Stack           |
| -------------------- | -------------------------------------- | --------------------------- |
| Storage              | Dynamic array                          | Singly linked list          |
| `push()`             | `O(1)` amortized                       | `O(1)`                      |
| `pop()`              | `O(1)` amortized                       | `O(1)`                      |
| `top()`              | `O(1)`                                 | `O(1)`                      |
| Memory resizing      | Required                               | Not required                |
| Extra pointer memory | No                                     | Yes                         |
| Contiguous memory    | Yes                                    | No                          |
| Memory allocation    | During resizing                        | Per node                    |
| Maximum size         | Limited by available contiguous memory | Limited by available memory |

Both implementations provide the same Stack ADT interface, so the application programs can use either implementation without changing their core algorithms.

---

# 8. Applications Demonstrated

This project demonstrates that stacks are useful for more than simple insertion and deletion.

### 🔹 Sorting

**Online A1A2** uses an auxiliary stack to perform a stack-based version of insertion sort.

### 🔹 Simulating Recursion

**Online B1B2** uses stacks to simulate the recursive Fibonacci call tree without using recursion.

### 🔹 Monotonic Stack

**Online C1C2** uses a stack to efficiently determine which buildings are visible from the right.

These examples demonstrate how the LIFO property of a stack can be used to solve a wide range of algorithmic problems.

---

# 9. Conclusion

The Stack data structure is a simple but powerful linear data structure based on the **Last-In-First-Out (LIFO)** principle.

In this project, the Stack ADT was implemented in two different ways:

1. **Dynamic array**
2. **Singly linked list**

Both implementations support the fundamental operations:

```text
push()
pop()
top()
isEmpty()
length()
clear()
```

The implementations were then used to solve three different problems:

* **Sorting a stack** using an auxiliary stack
* **Counting Fibonacci function calls** by simulating recursion
* **Finding visible buildings** using a monotonic stack

The project also demonstrates important programming concepts such as:

* Dynamic memory management
* Array resizing
* Linked-list manipulation
* Memory deallocation
* Stack-based algorithm design
* Simulation of recursion
* Monotonic stack techniques
* Time and space complexity analysis

Overall, these problems show how a relatively simple data structure can be adapted to solve many different computational problems efficiently.

---

## 👨‍🎓 Author

**Saif Al Islam**
**Student ID:** 2205119

---

