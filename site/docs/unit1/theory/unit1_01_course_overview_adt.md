# Unit 1: Course Overview, Data Structures & ADT

## 📚 Course Information

**Course:** Data Structures and its Applications (UE25CS52A)  
**Semester:** 3  
**Instructor:** Prof. Vandana M L (vandanamd@pes.edu)  
**Textbook:** "Data Structures using C & C++" by Yedidyah Langsam, Moshe J. Augenstein, Aaron M. Tenenbaum (Pearson Education, 2nd Edition, 2015)  
**Reference:** "Data Structure and Program Design in C" by Robert Kruse, C.L. Tondo, Bruce P. Leung (Pearson Education, 2nd Edition, 2007)

---

## 🎯 What is a Data Structure?

> **Definition:** A data structure is a scheme of organizing data in the memory of the computer in such a way that various operations can be performed efficiently on this data.

### Why Do We Need Data Structures?

1. **Large amounts of data** - Computers deal with text, images, relational data, etc.
2. **Data is raw material** - For information, analytics, business intelligence, advertising
3. **Organization matters** - The way data is organized in memory plays a key role in deciding time complexity of algorithms
4. **Data Structures & Algorithms go hand in hand** - You can't have efficient algorithms without proper data structures

---

## 📐 Classification of Data Structures

```
                    DATA STRUCTURES
                          |
          +---------------+---------------+
          |                               |
    LINEAR                        NON-LINEAR
          |                               |
    +-----+-----+-----+            +------+------+
    |     |     |     |            |      |      |
 Array Stack Queue Linked      Tree    Graph   Heap
  List                    List
```

### Linear Data Structures
- **Array** - Contiguous memory, fixed size
- **Stack** - LIFO (Last In First Out)
- **Queue** - FIFO (First In First Out)
- **Linked List** - Dynamic size, nodes connected by pointers
- **Linear List using Array**

### Non-Linear Data Structures
- **Tree** - Hierarchical (Binary Tree, BST, AVL, Heap, Trie)
- **Graph** - Network of nodes (vertices) and edges

---

## 🧠 Abstract Data Type (ADT)

> **ADT** is used to represent data and operations associated with an entity from the point of view of user **irrespective of implementation**.

### Key Points:
- ADT specifies **WHAT** operations are supported, not **HOW** they are implemented
- Same ADT can be implemented using different data structures
- Example: Stack ADT can be implemented using Array OR Linked List

### ADT vs Data Structure
| ADT (Interface) | Data Structure (Implementation) |
|-----------------|--------------------------------|
| What operations | How operations are implemented |
| Stack: push, pop, peek | Array-based Stack |
| Stack: push, pop, peek | Linked List-based Stack |
| Queue: enqueue, dequeue | Circular Array Queue |
| Queue: enqueue, dequeue | Linked List Queue |

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Data Structure** | Organization of data for efficient operations |
| **ADT** | What operations, not how implemented |
| **Linear** | Array, Stack, Queue, Linked List |
| **Non-Linear** | Tree, Graph |
| **Implementation Choice** | Same ADT → different implementations |

---

## 🧪 Self-Test Questions

1. What is the difference between a data structure and an ADT?
2. Give two examples of linear and non-linear data structures each.
3. Can a Stack ADT be implemented using both array and linked list? Why?
4. What does "irrespective of implementation" mean in ADT definition?

---

*Next: [Memory Allocation in C →](./unit1_02_memory_allocation.md)*