# Intractability & NP-Completeness: Rigorous Reduction Proofs

![Course](https://img.shields.io/badge/Course-CSE%20208-green.svg)
![Topic](https://img.shields.io/badge/Topic-NP--Completeness%20%26%20Reductions-purple.svg)
![Type](https://img.shields.io/badge/Type-Theoretical%20Foundations-blue.svg)

## 📌 Overview

This directory provides formal theoretical frameworks and reduction proofs for three canonical NP-complete decision problems from **CSE 208**:
1. **[Section A: Connected Dominating Set (CDS)](file:///home/saif/Documents/DSA/CSE%20208/Intractability/Section_A_CDS_Solution.pdf)** — Reduction from *Vertex Cover*
2. **[Section B: $K$-Coloring Problem](file:///home/saif/Documents/DSA/CSE%20208/Intractability/Section_B_K_Coloring_Solution.pdf)** — Reduction from *3-Coloring*
3. **[Section C: Not-All-Equal 3-SAT (NAE-3-SAT)](file:///home/saif/Documents/DSA/CSE%20208/Intractability/Section_C_NAE3SAT_Solution.pdf)** — Reduction from *3-SAT*

---

## 🏛 The NP-Completeness Proof Blueprint

To establish that a decision problem $L$ is **NP-complete**, the standard Cook-Karp proof framework is applied:
1. **Prove $L \in \mathcal{NP}$**:
   - Provide a polynomial-length **certificate** $C$.
   - Specify a deterministic algorithm that verifies $C$ in polynomial time $\mathcal{O}(|x|^c)$.
2. **Prove $L$ is $\mathcal{NP}$-hard**:
   - Select a known $\mathcal{NP}$-complete problem $L' \in \mathcal{NPC}$.
   - Define a reduction function $f: \Sigma^* \to \Sigma^*$ transforming instances of $L'$ to instances of $L$.
   - **Polynomial Time**: Prove $f(x)$ computes in $\mathcal{O}(|x|^{c'})$.
   - **Correctness ($\iff$)**:
     - *Forward Direction*: If $x \in L'$, then $f(x) \in L$.
     - *Backward Direction*: If $f(x) \in L$, then $x \in L'$.

---

## 🔍 Detailed Problem Analyses & Proofs

### 1. Connected Dominating Set (CDS)
- **Definition**: Given graph $G = (V, E)$ and integer $k$, does there exist a subset $D \subseteq V$ with $|D| \le k$ such that every vertex $v \in V \setminus D$ is adjacent to at least one vertex in $D$, and the induced subgraph $G[D]$ is connected?
- **Proof that $\text{CDS} \in \mathcal{NP}$**:
  - *Certificate*: Vertex subset $D \subseteq V$.
  - *Verification*: Check $|D| \le k$. Verify every $u \in V \setminus D$ has an edge to $D$. Run BFS on $G[D]$ to verify connectivity. Total time: $\mathcal{O}(V + E)$.
- **NP-Hardness via Reduction from Vertex Cover**:
  - Given instance $\langle G = (V, E), k \rangle$ of Vertex Cover:
  - Construct graph $G'$ by replacing each edge $e = (u, v)$ with a path or triangle gadget connecting to $u$ and $v$, and adding a star coordinator vertex adjacent to all original vertices.
  - A vertex cover of size $k$ in $G$ corresponds to a connected dominating set of size $k + 1$ in $G'$, and vice versa.

### 2. $K$-Coloring Problem
- **Definition**: Given graph $G = (V, E)$ and integer $k$, can each vertex be assigned one of $k$ colors such that no two adjacent vertices share the same color?
- **Proof that $K\text{-Coloring} \in \mathcal{NP}$**:
  - *Certificate*: Color assignment array $c: V \to \{1, 2, \dots, k\}$.
  - *Verification*: Iterate through all edges $(u, v) \in E$ and assert $c(u) \ne c(v)$. Runs in $\mathcal{O}(E)$ time.
- **NP-Hardness via Reduction from 3-Coloring**:
  - Given graph $G$ to 3-color:
  - Add $k - 3$ new vertices $w_1, w_2, \dots, w_{k-3}$ that form a clique $K_{k-3}$ with each other.
  - Connect each new vertex $w_i$ to every vertex in $V(G)$.
  - The new vertices must consume $k - 3$ distinct colors; hence, the remaining vertices $V(G)$ can be colored using at most $k - (k - 3) = 3$ colors if and only if $G$ is 3-colorable.

### 3. Not-All-Equal 3-SAT (NAE-3-SAT)
- **Definition**: Given a 3-CNF Boolean formula $\phi$, does there exist a truth assignment such that every clause contains **at least one TRUE** literal and **at least one FALSE** literal (no clause is all-true or all-false)?
- **Proof that $\text{NAE-3-SAT} \in \mathcal{NP}$**:
  - *Certificate*: Truth assignment $\tau: X \to \{\text{True}, \text{False}\}$.
  - *Verification*: For each clause $(l_1 \lor l_2 \lor l_3)$, evaluate literals and verify $\{ \tau(l_1), \tau(l_2), \tau(l_3) \} = \{\text{True}, \text{False}\}$. Runs in $\mathcal{O}(\text{Clauses})$ time.
- **NP-Hardness via Reduction from 3-SAT**:
  - Introduce a global variable $z$.
  - For each original clause $C_i = (x_1 \lor x_2 \lor x_3)$ in 3-SAT, create two 4-variable or 3-variable clauses with auxiliary variables and $z$.
  - Setting $z = \text{False}$ establishes an exact bijection between satisfying assignments of 3-SAT and valid NAE assignments.

---

## 📊 Summary of Reduction Mappings

| Problem | Known NP-Complete Problem | Gadget / Transformation Technique | Verification Cost |
|---|---|---|---|
| **Connected Dominating Set** | Vertex Cover | Edge gadget substitution + Central coordinator | $\mathcal{O}(V + E)$ |
| **$K$-Coloring** | 3-Coloring | Auxiliary $(k-3)$-clique completely connected to $V$ | $\mathcal{O}(E)$ |
| **NAE-3-SAT** | 3-SAT | Anchor literal $z$ + Split clauses | $\mathcal{O}(m)$ |

---

## 📁 Repository Files

- [`Section_A_CDS_Solution.pdf`](file:///home/saif/Documents/DSA/CSE%20208/Intractability/Section_A_CDS_Solution.pdf): Complete handwritten and annotated solution for Connected Dominating Set.
- [`Section_B_K_Coloring_Solution.pdf`](file:///home/saif/Documents/DSA/CSE%20208/Intractability/Section_B_K_Coloring_Solution.pdf): Complete handwritten and annotated solution for K-Coloring.
- [`Section_C_NAE3SAT_Solution.pdf`](file:///home/saif/Documents/DSA/CSE%20208/Intractability/Section_C_NAE3SAT_Solution.pdf): Complete handwritten and annotated solution for NAE-3-SAT.
