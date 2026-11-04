# Unit 3: Advanced Trees, Heaps & Graphs

## Topics

| # | Topic | Description |
|---|-------|-------------|
| 3.1 | [General Trees & Binary Search Trees](3.1_trees_bst.md) | Tree fundamentals, BST operations, traversals, deletion, tree reconstruction |
| 3.2 | [Array Implementation of Trees](3.2_array_trees.md) | Implicit vs explicit array mapping, heapify-like operations, free slot management |
| 3.3 | [Expression Trees](3.3_expression_trees.md) | Postfix to tree construction, stack-based evaluation |
| 3.4 | [Threaded Binary Trees](3.4_threaded_trees.md) | Thread concept, insertion, O(1) space iterative inorder |
| 3.5 | [Heaps & Priority Queues](3.5_heaps.md) | Complete binary tree, heapify, build heap, insert/delete max, PQ composition |
| 3.6 | [AVL Trees](3.6_avl_trees.md) | Balance factor, 4 rotation cases (LL/RR/LR/RL), self-balancing BST |
| 3.7 | [Splay Trees](3.7_splay_trees.md) | Self-adjusting, Zig/Zig-Zig/Zig-Zag, amortized O(log n) |
| 3.8 | [Graphs](3.8_graphs.md) | Definitions, representations, Euler/Hamiltonian, applications |

---

## Unit 3 Overview

**Hours:** 14  
**Lab IDs:** Lab 3, Lab 4, Lab 7, Lab 8, Lab 9

This unit covers advanced tree structures, heap-based priority queues, self-balancing trees, and graph fundamentals — core topics for the final exam.

---

## Quick Reference: Tree Types Comparison

| Tree Type | Balance Method | Search | Insert | Delete | Space Overhead |
|-----------|---------------|--------|--------|--------|----------------|
| **BST** | None | O(h) | O(h) | O(h) | 2 pointers |
| **AVL** | Strict (BF ∈ {-1,0,1}) | O(log n) | O(log n) | O(log n) | 2 ptrs + height |
| **Splay** | Amortized (access → root) | O(log n)* | O(log n)* | O(log n)* | 2 ptrs only |
| **Threaded** | Threads replace NULLs | O(h) | O(h) | O(h) | 2 ptrs + 2 bits |
| **Heap** | Complete tree + parental dominance | O(n) | O(log n) | O(log n) | Array only |

*Amortized

---

## Key Algorithms to Master

1. **BST Insert/Delete** (4 cases)
2. **Tree Reconstruction** (Inorder + Postorder)
3. **Array Tree Operations** (explicit indices)
4. **Expression Tree** (postfix → tree → eval)
5. **Threaded Inorder** (iterative, no stack)
6. **Heapify / Build Heap** (O(n))
7. **AVL Rotations** (LL/RR/LR/RL)
8. **Splay Cases** (Zig/Zig-Zig/Zig-Zag)
9. **Graph Representations** (Matrix vs List)
10. **Euler vs Hamiltonian** (Edge vs Vertex)