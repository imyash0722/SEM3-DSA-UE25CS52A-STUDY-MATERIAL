# DSA Course - Complete Notes Index

## Course Information
- **Course**: Data Structures and its Applications (UE25CS52A)
- **Instructor**: Prof. N S Kumar (nskumar@pes.edu)
- **Textbook**: "Data Structures using C/C++" by Langsum Yedidyah, Moshe J Augenstein, Aaron M Tenenbaum (Pearson, 2nd ed., 2015)
- **Reference**: "Data Structures and Program Design in C" by Robert Kruse et al. (Pearson, 2nd ed., 2019)

---

## Unit 1: Foundations, Lists, Stacks, ADTs

### Topics Covered
1. **Functions & Pointers** - Parameter passing, recursion, pointers, memory model
2. **Arrays** - 1D/2D arrays, pointer arithmetic, parameter passing
3. **Structures** - Definition, padding, initialization, parameter passing, typedef
4. **Dynamic Memory** - malloc/free/calloc/realloc, garbage, dangling pointers, memory leaks
5. **Abstract Data Types** - Interface vs implementation, inversion of dependency
6. **Linked Lists** - Self-referential structures, traversal, insertion, deletion
7. **Ordered Lists** - Sorted insertion with 4 boundary cases
8. **Header Node** - Dummy node simplifies insertion logic
9. **Stacks** - Array & linked list implementations, LIFO
10. **Stack Applications** - Parentheses matching, postfix evaluation, infix→postfix
11. **Skiplists & Multilists** - Multi-level lists, sparse matrices

### Key Concepts
- **ADT**: Specification of operations without implementation details
- **Interface is sacred**: Changes to implementation don't affect clients
- **Self-referential structures**: Basis for linked data structures
- **Header node**: Eliminates special cases in list operations
- **Stack frames**: Function call mechanism using stack

### Example Programs
See: `unit1_02_example_programs.md`

---

## Unit 2: Advanced Lists, Queues, Priority Queues

### Topics Covered
1. **Circular Linked Lists** - Cycle detection, Josephus problem
2. **Doubly Linked Lists** - Bidirectional traversal, easier insert/delete
3. **Queues (Linked List)** - FIFO with front/rear pointers
4. **Queues (Circular Array)** - Modulo arithmetic, O(1) operations
5. **Priority Queues** - 5 implementations compared
6. **Deques** - Double-ended queues, stack/queue composition
7. **Round Robin Scheduling** - Experiential learning project

### Implementation Comparison

| Structure | Insert | Delete | Search | Space |
|-----------|--------|--------|--------|-------|
| Singly LL | O(1)* | O(n) | O(n) | 1 ptr |
| Doubly LL | O(1)* | O(1)* | O(n) | 2 ptr |
| Circular Array Queue | O(1) | O(1) | O(n) | Array |
| PQ Unordered List | O(1) | O(n) | - | List |
| PQ Ordered List | O(n) | O(1) | - | List |
| PQ Unordered Array | O(1) | O(n) | - | Array |
| PQ Ordered Array | O(n) | O(1) | - | Array |
| PQ Heap | O(log n) | O(log n) | - | Array |

*At known position

### Key Concepts
- **Circular list**: Last node points to first; do-while for traversal
- **Doubly linked**: Extra `prev_` pointer enables O(1) insert before/delete
- **Queue design**: Front points to first, rear to last; nodes link forward
- **Priority queue**: Same interface, different implementations
- **Deque**: Generalization of both stack and queue

### Example Programs
See: `unit2_example_programs.md`

---

## Unit 3: Trees, Heaps, Balanced Trees, Graphs

### Topics Covered
1. **General/Binary Trees** - Terminology, properties, traversals
2. **Binary Search Trees** - Dynamic & array implementations
3. **Expression Trees** - Postfix to tree conversion, evaluation
4. **Threaded Binary Trees** - Threads for O(1) successor/predecessor
5. **Heaps** - Complete trees, parental dominance, heapify, heapsort
6. **AVL Trees** - Height-balanced, 4 rotation cases
7. **Splay Trees** - Self-adjusting, amortized O(log n)
8. **Graphs** - Representations, BFS/DFS, Dijkstra, Prim

### Tree Traversals
```
Inorder:   Left → Root → Right    (BST: sorted output)
Preorder:  Root → Left → Right    (Copy tree)
Postorder: Left → Right → Root    (Delete tree)
```

### BST Operations (Recursive on Nodes)
- Insert: O(h), Search: O(h), Delete: O(h) with 4 cases
- **Delete Case 4** (2 children): Use inorder successor

### Heap Operations
- **Build Heap**: O(n) - heapify from n/2 down to 1
- **Insert**: O(log n) - bubble up
- **Delete Max**: O(log n) - move last to root, heapify down
- **Heapsort**: O(n log n) - build + repeated delete max

### AVL Rotations
| Case | Pattern | Rotation |
|------|---------|----------|
| LL | Left-Left | Single Right |
| RR | Right-Right | Single Left |
| LR | Left-Right | Left then Right |
| RL | Right-Left | Right then Left |

**Memory aid**: Same direction = single, Opposite = double

### Graph Algorithms
- **BFS**: Queue, shortest path in unweighted
- **DFS**: Stack, topological sort, cycle detection
- **Dijkstra**: Min-heap, single-source shortest path (weighted)
- **Prim**: Min-heap, Minimum Spanning Tree

---

## Textbook References

### Tenenbaum et al. (Primary)
- Ch 1: Introduction & Overview
- Ch 2: Arrays & Structures
- Ch 3: Stacks & Queues
- Ch 4: Linked Lists
- Ch 5: Trees
- Ch 6: Graphs
- Ch 7: Sorting & Searching

### Kruse et al. (Reference)
- Ch 2: Arrays, Records, Pointers
- Ch 3: Linked Lists
- Ch 4: Stacks & Queues
- Ch 5: Recursion
- Ch 6: Trees
- Ch 7: Graphs
- Ch 8: Sorting

---

## Programming Practices Emphasized

1. **Separate Interface from Implementation**
   - Header files (.h) for declarations
   - Source files (.c) for definitions
   - Client code includes only headers

2. **Use Makefiles**
   - Track dependencies
   - Incremental compilation
   - `make -f makefile`

3. **Memory Management**
   - Always check malloc return
   - Free in correct order (save next before free)
   - Avoid memory leaks and dangling pointers

4. **Recursive Thinking**
   - Base case + recursive step
   - Tree functions: recursive on nodes, not tree
   - Trust the recursion

5. **ADT Design**
   - Opaque types where possible
   - Consistent naming (init, deinit, insert, delete, etc.)
   - Error handling via return values

---

## File Organization

```
notes/
├── INDEX.md                    # This file
├── unit1_01_functions_and_pointers.md
├── unit1_02_example_programs.md
├── unit2_circular_dll_queue_pq.md
├── unit2_example_programs.md
├── unit3_trees_heaps_avl_splay_graphs.md
└── unit3_example_programs.md
```

---

## Study Tips

### For Exams (ISA/ESA)
- **ISA1**: Units 1 & 2 (MCQs - 10×1 + 5×2 marks)
- **ISA2**: Units 3 & 4 (MCQs - 10×1 + 5×2 marks)
- **ESA**: All units (20 marks MCQ + 80 marks subjective)

### Key Programs to Practice
1. Linked list with all operations
2. Stack applications (parentheses, postfix, infix→postfix)
3. Circular array queue
4. Priority queue (all 4 basic implementations)
5. BST insert/search/delete
6. Heap insert/delete/heapsort
7. AVL rotations
8. Graph BFS/DFS/Dijkstra

### Common Pitfalls
- Forgetting `&` in scanf
- Array decaying to pointer (losing size info)
- Not checking malloc return
- Freeing memory twice or not at all
- Off-by-one in circular array queue
- Wrong rotation in AVL
- Missing base case in recursion

---

## Contact
- **Professor**: N S Kumar
- **Email**: nskumar@pes.edu
- **Phone**: 98450 66845

---

*Generated from course materials: slides, notes, assignments, and textbook references*