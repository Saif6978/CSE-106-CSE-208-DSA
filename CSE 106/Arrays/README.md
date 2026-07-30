# 📚 Arrays - Online Assignments (A1/A2, B1/B2, C1/C2)

Solutions to the **CSE 106 – Data Structures and Algorithms I** online assignments (January 2024).

These assignments focus on fundamental **array manipulation problems** and are implemented in **C**, following the provided skeleton code. Only the required functions were completed while keeping the rest of the template unchanged.

---

## 📂 Repository Structure

```text
Arrays/
└── Onlines/
    ├── Asgn_1_A1A2/
    │   ├── a1a2.c
    │   ├── input.txt
    │   └── output.txt
    ├── Asgn_1_B1B2/
    │   ├── b1b2.c
    │   ├── input.txt
    │   └── output.txt
    └── Asgn_1_C1C2/
        ├── c1c2.c
        ├── input.txt
        └── output.txt
```

Each assignment folder contains:

* 📄 The original skeleton C program
* 📥 A sample `input.txt`
* 📤 A generated `output.txt`
* ✅ Completed solution for the required function only

---

# Assignment 1 — Maximum Triplet Sum (A1/A2)

## Problem Statement

A **triplet** consists of **three consecutive elements** of an array.

Given an integer array, find the triplet having the **maximum triplet sum**.

If multiple triplets have the same maximum sum, choose the **rightmost** one (largest starting index).

If the array contains fewer than **3 elements**, print:

```text
Invalid input
```

---

## Input Format

```
T
n
array elements
```

* `T` → Number of test cases
* `n` → Size of the array

---

## Sample Input

```text
5
5
5 3 4 6 1
6
12 35 1 10 32 1
1
42
4
1 3 3 1
5
-1 -2 -3 -4 -5
```

## Sample Output

```text
3 4 6
12 35 1
Invalid input
3 3 1
-1 -2 -3
```

---

## Algorithm

1. If `n < 3`, print **Invalid input**.
2. Compute the sum of the first triplet.
3. Traverse all remaining triplets.
4. Whenever a triplet sum is **greater than or equal** to the current maximum:

   * Update the maximum.
   * Store its starting index.
5. Print the triplet beginning at the stored index.

Using `>=` ensures that the **rightmost** triplet is selected in case of a tie.

---

## Complexity

| Time     | Space    |
| -------- | -------- |
| **O(n)** | **O(1)** |

---

## Function

```c
void maxTripletSum(int arr[], int n) {
    if (n < 3) {
        printf("Invalid input\n");
        return;
    }

    int best = 0;
    long long maxSum = (long long)arr[0] + arr[1] + arr[2];

    for (int i = 1; i + 2 < n; i++) {
        long long sum = (long long)arr[i] + arr[i + 1] + arr[i + 2];

        if (sum >= maxSum) {
            maxSum = sum;
            best = i;
        }
    }

    printf("%d %d %d\n",
           arr[best],
           arr[best + 1],
           arr[best + 2]);
}
```

---

# Assignment 2 — Count Inversions (B1/B2)

## Problem Statement

An **inversion** is a pair of indices `(i, j)` such that:

```text
i < j
arr[i] > arr[j]
```

Find the total number of inversions in the array.

If the array contains fewer than **2 elements**, print:

```text
Invalid input
```

---

## Sample Input

```text
5
5
5 3 4 6 1
6
12 35 1 10 32 1
1
42
4
1 3 3 1
5
-1 -2 -3 -4 -5
```

## Sample Output

```text
6
9
Invalid input
2
10
```

---

## Algorithm

1. If `n < 2`, print **Invalid input**.
2. Initialize `count = 0`.
3. Compare every element with every element after it.
4. Whenever:

```text
arr[i] > arr[j]
```

increment the inversion count.

This assignment uses the straightforward **O(n²)** solution. Although a merge-sort-based solution can achieve **O(n log n)**, the brute-force method is sufficient for the assignment constraints.

---

## Complexity

| Time      | Space    |
| --------- | -------- |
| **O(n²)** | **O(1)** |

---

## Function

```c
void countInversion(int arr[], int n) {
    if (n < 2) {
        printf("Invalid input\n");
        return;
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }

    printf("%d\n", count);
}
```

---

# Assignment 3 — Second Largest Element (C1/C2)

## Problem Statement

Find the **second largest distinct element** in the array.

The second largest value must be **strictly smaller** than the largest value.

Special cases:

* If `n < 2`

```text
Invalid input
```

* If all elements are equal

```text
Second largest element not found
```

---

## Sample Input

```text
5
5
5 3 4 6 1
6
12 35 1 10 32 1
1
42
4
4 4 4 4
5
-1 -2 -3 -4 -5
```

## Sample Output

```text
5
32
Invalid input
Second largest element not found
-2
```

---

## Algorithm

1. If `n < 2`, print **Invalid input**.
2. Find the maximum element.
3. Traverse the array again.
4. Track the largest value that is **strictly smaller** than the maximum.
5. If none exists, print:

```text
Second largest element not found
```

Otherwise, print the second largest element.

---

## Complexity

| Time     | Space    |
| -------- | -------- |
| **O(n)** | **O(1)** |

---

## Function

```c
void findSecondLargest(int arr[], int n) {
    if (n < 2) {
        printf("Invalid input\n");
        return;
    }

    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    int second = 0;
    int found = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] < max) {
            if (!found || arr[i] > second) {
                second = arr[i];
                found = 1;
            }
        }
    }

    if (!found)
        printf("Second largest element not found\n");
    else
        printf("%d\n", second);
}
```

---

# 🚀 Compiling & Running

Each program is self-contained.

It reads from `input.txt` and writes the results to `output.txt`.

### Linux / macOS

```bash
gcc a1a2.c -o a1a2
./a1a2
```

Similarly,

```bash
gcc b1b2.c -o b1b2
./b1b2

gcc c1c2.c -o c1c2
./c1c2
```

### Windows

Compile using **MinGW**, **Code::Blocks**, **Visual Studio**, or any C compiler of your choice, then execute the generated program.

---

# 📌 Summary

| Assignment | Problem                | Time Complexity |
| ---------- | ---------------------- | --------------- |
| **A1/A2**  | Maximum Triplet Sum    | **O(n)**        |
| **B1/B2**  | Count Inversions       | **O(n²)**       |
| **C1/C2**  | Second Largest Element | **O(n)**        |

---

# 📝 Notes

* The solutions strictly follow the assignment specifications.
* Tie handling for **Maximum Triplet Sum** selects the **rightmost** triplet.
* The inversion count uses the required **brute-force** approach.
* The **Second Largest** solution searches for the largest value strictly smaller than the maximum.
* Sample `input.txt` files correspond to the assignment examples, and the generated outputs match the expected results.

---

## 👨‍💻 Course Information

**Course:** CSE 106 – Data Structures and Algorithms I
**Semester:** January 2024
**Author:** Saif Al Islam
**Student_ID:** 2205119
