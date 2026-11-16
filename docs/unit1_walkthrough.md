# Unit 1: Introduction to Data Structures & C Fundamentals

## 📚 Course Overview

**Course:** Data Structures and its Applications (UE25CS52A)  
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

- ADT specifies **WHAT** operations are supported, not **HOW** they are implemented
- Same ADT can be implemented using different data structures
- Example: Stack ADT can be implemented using Array OR Linked List

---

## 💾 Memory Allocation in C

### Static Memory Allocation
- **Allocated by compiler** at compile time
- Exact size and type must be known at compile time
- Memory allocated in **stack area**
- Examples: `int b; int c[10];`

**Disadvantages:**
- Size cannot be altered at runtime
- May lead to under/over utilization of memory
- Memory cannot be deleted explicitly
- Only useful when data size is fixed and known beforehand

### Dynamic Memory Allocation
- Memory allocated and released **during program execution**
- Operates at low level
- Functions defined in `<stdlib.h>`

| Function | Purpose |
|----------|---------|
| `malloc(size)` | Allocate memory (uninitialized) |
| `calloc(n, size)` | Allocate memory (zero-initialized) |
| `realloc(ptr, new_size)` | Resize allocated memory |
| `free(ptr)` | Release allocated memory |

---

## 🔧 Dynamic Memory Functions - Deep Dive

### malloc()
```c
void *malloc(size_t size);
```
- Takes number of bytes to allocate
- Use `sizeof` to determine size of a type
- Returns `void*` (can be assigned to any pointer)
- Returns `NULL` if no memory available

**Example: Allocate space for 100 integers**
```c
int *p;
if ((p = (int*)malloc(100 * sizeof(int))) == NULL) {
    printf("out of memory\n");
    exit(1);
}
// Access as p[0], p[1], ..., p[99] or *p, *(p+1), ...
```

### calloc()
```c
void *calloc(size_t nitem, size_t size);
```
- Allocates memory and **initializes to zero**
- Requires two arguments: number of items and size of each item

**Example:**
```c
int *p = (int*)calloc(100, sizeof(int)); // 100 ints, all zeros
```

### realloc()
```c
void *realloc(void *ptr, size_t new_size);
```
- Resizes previously allocated block
- Two arguments: pointer to existing block, new size

**Example:**
```c
int *ip = (int*)malloc(100 * sizeof(int));
// ... later need twice as much ...
ip = (int*)realloc(ip, 200 * sizeof(int));
```

### free()
```c
void free(void *ptr);
```
- Deallocates memory allocated by malloc/calloc/realloc
- Takes a pointer as argument

**Critical Concepts:**
- **Dangling Pointer**: Pointer to memory that has been freed
- **Memory Leak**: Allocated memory with no pointer to it (cannot be freed)

```c
// DANGEROUS - Dangling pointer
int *p = malloc(sizeof(int));
free(p);
// p now dangles - points to freed memory!
// *p = 10; // UNDEFINED BEHAVIOR!

// DANGEROUS - Memory leak
int *p = malloc(sizeof(int));
*p = 30;
p = malloc(sizeof(int)); // First block lost forever!
```

---

## 🔗 Singly Linked List - Complete Walkthrough

### What is a Linked List?

A **linked list** is a linear data structure where:
- Elements (nodes) are NOT stored in contiguous memory
- Each node contains **data** and a **pointer (link)** to the next node
- Head/start pointer points to the first node
- Last node's link contains `NULL`

### Node Structure
```c
struct node {
    int data;
    struct node *link;
};
typedef struct node NODE;
```

### Creating a Node
```c
// Allocate memory dynamically
NODE *temp = (NODE*)malloc(sizeof(NODE));
if (temp == NULL) { /* handle error */ }

// Set data part
temp->data = user_value;

// Set link part to NULL (will be updated during insertion)
temp->link = NULL;
```

---

### Insertion Operations (3 Cases)

#### Case 1: Insert at Beginning
```c
void insert_front(NODE **head, int value) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    temp->data = value;
    temp->link = NULL;
    
    if (*head == NULL) {
        // Empty list - new node becomes head
        *head = temp;
    } else {
        // List not empty - insert before current head
        temp->link = *head;
        *head = temp;
    }
}
```

**Visual Walkthrough:**
```
Before: head → [10|•] → [20|•] → [30|NULL]
        
Insert 5 at front:
1. Create node with data=5, link=NULL
2. temp->link = head (points to 10)
3. head = temp (points to 5)

After:  head → [5|•] → [10|•] → [20|•] → [30|NULL]
```

#### Case 2: Insert at End
```c
void insert_end(NODE **head, int value) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    temp->data = value;
    temp->link = NULL;
    
    if (*head == NULL) {
        *head = temp;
    } else {
        NODE *curr = *head;
        // Traverse to last node
        while (curr->link != NULL) {
            curr = curr->link;
        }
        // curr is now last node
        curr->link = temp;
    }
}
```

#### Case 3: Insert at Given Position
```c
void insert_at_pos(NODE **head, int value, int pos) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    temp->data = value;
    temp->link = NULL;
    
    if (*head == NULL || pos == 1) {
        // Empty list or insert at front
        temp->link = *head;
        *head = temp;
        return;
    }
    
    NODE *curr = *head;
    NODE *prev = NULL;
    int i = 1;
    
    // Traverse to position
    while (curr != NULL && i < pos) {
        prev = curr;
        curr = curr->link;
        i++;
    }
    
    if (curr == NULL) {
        // Position beyond end - insert at end
        prev->link = temp;
    } else {
        // Insert between prev and curr
        prev->link = temp;
        temp->link = curr;
    }
}
```

---

### Deletion Operations (3 Cases)

#### Case 1: Delete First Node
```c
void delete_front(NODE **head) {
    if (*head == NULL) {
        printf("List empty\n");
        return;
    }
    
    NODE *temp = *head;
    
    if ((*head)->link == NULL) {
        // Only one node
        *head = NULL;
    } else {
        // More than one node
        *head = (*head)->link;
    }
    
    free(temp);
}
```

#### Case 2: Delete Last Node
```c
void delete_end(NODE **head) {
    if (*head == NULL) {
        printf("List empty\n");
        return;
    }
    
    if ((*head)->link == NULL) {
        // Only one node
        free(*head);
        *head = NULL;
        return;
    }
    
    NODE *curr = *head;
    NODE *prev = NULL;
    
    // Traverse to last node, keeping track of previous
    while (curr->link != NULL) {
        prev = curr;
        curr = curr->link;
    }
    
    // curr is last node, prev is second-last
    prev->link = NULL;
    free(curr);
}
```

#### Case 3: Delete at Given Position
```c
void delete_at_pos(NODE **head, int pos) {
    if (*head == NULL) {
        printf("List empty\n");
        return;
    }
    
    if (pos == 1) {
        // Delete first node
        NODE *temp = *head;
        *head = (*head)->link;
        free(temp);
        return;
    }
    
    NODE *curr = *head;
    NODE *prev = NULL;
    int i = 1;
    
    while (curr != NULL && i < pos) {
        prev = curr;
        curr = curr->link;
        i++;
    }
    
    if (curr == NULL) {
        printf("Invalid position\n");
        return;
    }
    
    if (curr->link == NULL) {
        // Last node
        prev->link = NULL;
    } else {
        // Middle node
        prev->link = curr->link;
    }
    
    free(curr);
}
```

---

## 🔄 Doubly Linked List

### Why Doubly Linked List?
| Operation | Singly Linked List | Doubly Linked List |
|-----------|-------------------|-------------------|
| Move Forward | 1 step | 1 step |
| Move Backward | n steps | **1 step** |
| Insert Before | n steps (need prev) | **1 step** |
| Delete Node | n steps (need prev) | **1 step** |
| Search | n steps | n steps |

**Trade-off:** Extra space (prev pointer) for time efficiency

### Node Structure
```c
struct node {
    int data;
    struct node *prev;  // Previous node
    struct node *next;  // Next node
};
typedef struct node NODE;
```

### List Structure
```c
struct DLL {
    NODE *head;  // First node
    NODE *tail;  // Last node
};
typedef struct DLL dll_t;
```

### Key Operations

#### Insert at Beginning
```c
void insert_front_dll(dll_t *list, int value) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    temp->data = value;
    temp->prev = NULL;
    temp->next = list->head;
    
    if (list->head == NULL) {
        // Empty list
        list->head = list->tail = temp;
    } else {
        list->head->prev = temp;
        list->head = temp;
    }
}
```

#### Insert at End
```c
void insert_end_dll(dll_t *list, int value) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    temp->data = value;
    temp->next = NULL;
    temp->prev = list->tail;
    
    if (list->tail == NULL) {
        list->head = list->tail = temp;
    } else {
        list->tail->next = temp;
        list->tail = temp;
    }
}
```

#### Delete Node (with given pointer)
```c
void delete_node_dll(dll_t *list, NODE *temp) {
    if (temp == NULL) return;
    
    if (temp == list->head && temp == list->tail) {
        // Only node
        list->head = list->tail = NULL;
    } else if (temp == list->head) {
        // First node
        list->head = temp->next;
        list->head->prev = NULL;
    } else if (temp == list->tail) {
        // Last node
        list->tail = temp->prev;
        list->tail->next = NULL;
    } else {
        // Middle node
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    
    free(temp);
}
```

---

## 🔵 Circular Linked List

### Concept
- Last node points back to first node
- Forms a cycle
- Head pointer can point to ANY node in the cycle

### Structure (Same as Singly Linked List)
```c
struct node {
    int key;
    struct node *next;
};
typedef struct node node_t;

struct clist {
    node_t *head;  // Points to any node
};
typedef struct clist clist_t;
```

### Key Operations

#### Insert (after head)
```c
void insert_clist(clist_t *list, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key = key;
    
    if (list->head == NULL) {
        // Empty list - node points to itself
        temp->next = temp;
        list->head = temp;
    } else {
        // Insert after head
        temp->next = list->head->next;
        list->head->next = temp;
    }
}
```

#### Display (use do-while!)
```c
void disp_clist(clist_t *list) {
    if (list->head == NULL) {
        printf("List empty\n");
        return;
    }
    
    node_t *temp = list->head;
    printf("Circular List: ");
    do {
        printf("%d ", temp->key);
        temp = temp->next;
    } while (temp != list->head);
    printf("\n");
}
```

### Josephus Problem (Classic Application)
**Problem:** n people in circle, eliminate every k-th person, find survivor.

```c
int josephus(int n, int k) {
    // Create circular list 1..n
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; i++) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key = i;
        if (!head) head = tail = temp;
        else { tail->next = temp; tail = temp; }
    }
    tail->next = head;  // Make circular
    
    node_t *curr = head, *prev = tail;
    while (curr->next != curr) {
        // Count k-1 steps
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }
        // Eliminate curr
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
    }
    int survivor = curr->key;
    free(curr);
    return survivor;
}
```

---

## 📚 Anchor Programs for Unit 1

### Program 1: Complete Singly Linked List
```c
// sll_complete.c - Complete Singly Linked List Implementation
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} NODE;

NODE *create_node(int data) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    if (!temp) { printf("Memory full\n"); exit(1); }
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insert_front(NODE **head, int data) {
    NODE *temp = create_node(data);
    temp->next = *head;
    *head = temp;
}

void insert_end(NODE **head, int data) {
    NODE *temp = create_node(data);
    if (*head == NULL) { *head = temp; return; }
    NODE *curr = *head;
    while (curr->next) curr = curr->next;
    curr->next = temp;
}

void insert_at_pos(NODE **head, int data, int pos) {
    if (pos <= 1 || *head == NULL) { insert_front(head, data); return; }
    NODE *temp = create_node(data);
    NODE *curr = *head, *prev = NULL;
    int i = 1;
    while (curr && i < pos) { prev = curr; curr = curr->next; i++; }
    if (!curr) { prev->next = temp; }
    else { prev->next = temp; temp->next = curr; }
}

void delete_front(NODE **head) {
    if (!*head) return;
    NODE *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void delete_end(NODE **head) {
    if (!*head) return;
    if (!(*head)->next) { free(*head); *head = NULL; return; }
    NODE *curr = *head, *prev = NULL;
    while (curr->next) { prev = curr; curr = curr->next; }
    prev->next = NULL;
    free(curr);
}

void delete_at_pos(NODE **head, int pos) {
    if (!*head) return;
    if (pos <= 1) { delete_front(head); return; }
    NODE *curr = *head, *prev = NULL;
    int i = 1;
    while (curr && i < pos) { prev = curr; curr = curr->next; i++; }
    if (!curr) { printf("Invalid position\n"); return; }
    prev->next = curr->next;
    free(curr);
}

void display(NODE *head) {
    printf("List: ");
    while (head) { printf("%d → ", head->data); head = head->next; }
    printf("NULL\n");
}

int main() {
    NODE *head = NULL;
    
    printf("=== Singly Linked List Demo ===\n");
    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);
    display(head);  // 10 → 20 → 30
    
    insert_front(&head, 5);
    display(head);  // 5 → 10 → 20 → 30
    
    insert_at_pos(&head, 15, 3);
    display(head);  // 5 → 10 → 15 → 20 → 30
    
    delete_front(&head);
    display(head);  // 10 → 15 → 20 → 30
    
    delete_end(&head);
    display(head);  // 10 → 15 → 20
    
    delete_at_pos(&head, 2);
    display(head);  // 10 → 20
    
    return 0;
}
```

### Program 2: Dynamic Memory Demo
```c
// memory_demo.c - Dynamic Memory Allocation Demo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("=== Dynamic Memory Demo ===\n\n");
    
    // 1. malloc
    printf("1. malloc():\n");
    int *p = (int*)malloc(5 * sizeof(int));
    if (!p) { printf("Failed\n"); return 1; }
    for (int i = 0; i < 5; i++) p[i] = (i+1)*10;
    printf("Allocated 5 ints: ");
    for (int i = 0; i < 5; i++) printf("%d ", p[i]);
    printf("\n");
    free(p);
    p = NULL;  // Good practice: set to NULL after free
    
    // 2. calloc (zero-initialized)
    printf("\n2. calloc():\n");
    int *q = (int*)calloc(5, sizeof(int));
    printf("Zero-initialized: ");
    for (int i = 0; i < 5; i++) printf("%d ", q[i]);
    printf("\n");
    free(q);
    
    // 3. realloc
    printf("\n3. realloc():\n");
    int *r = (int*)malloc(3 * sizeof(int));
    r[0] = 1; r[1] = 2; r[2] = 3;
    printf("Before realloc: ");
    for (int i = 0; i < 3; i++) printf("%d ", r[i]);
    r = (int*)realloc(r, 6 * sizeof(int));
    r[3] = 4; r[4] = 5; r[5] = 6;
    printf("\nAfter realloc:  ");
    for (int i = 0; i < 6; i++) printf("%d ", r[i]);
    printf("\n");
    free(r);
    
    // 4. Structure allocation
    printf("\n4. Structure allocation:\n");
    struct student {
        char name[20];
        int roll;
        float marks;
    };
    struct student *s = (struct student*)malloc(sizeof(struct student));
    strcpy(s->name, "Alice");
    s->roll = 101;
    s->marks = 95.5;
    printf("Student: %s, Roll: %d, Marks: %.1f\n", s->name, s->roll, s->marks);
    free(s);
    
    printf("\n=== Dangling Pointer Demo ===\n");
    int *dang = (int*)malloc(sizeof(int));
    *dang = 100;
    printf("Before free: *dang = %d\n", *dang);
    free(dang);
    // dang is now DANGLING - don't use it!
    dang = NULL;  // Always set to NULL after free
    
    printf("\n=== Memory Leak Demo ===\n");
    // BAD: memory leak
    // int *leak = malloc(sizeof(int));
    // leak = malloc(sizeof(int));  // First block lost!
    
    // GOOD: free before reassign
    int *good = malloc(sizeof(int));
    *good = 42;
    free(good);
    good = malloc(sizeof(int));
    *good = 84;
    free(good);
    printf("No leaks!\n");
    
    return 0;
}
```

### Program 3: Circular List & Josephus
```c
// circular_josephus.c - Circular List & Josephus Problem
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} node_t;

node_t* create_node(int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void insert_clist(node_t **head, int key) {
    node_t *temp = create_node(key);
    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
    } else {
        temp->next = (*head)->next;
        (*head)->next = temp;
    }
}

void disp_clist(node_t *head) {
    if (!head) { printf("Empty\n"); return; }
    node_t *temp = head;
    printf("Circular: ");
    do {
        printf("%d ", temp->key);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Josephus Problem
int josephus(int n, int k) {
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; i++) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key = i; temp->next = NULL;
        if (!head) head = tail = (node_t*)malloc(sizeof(node_t));
        else { tail->next = temp; tail = temp; }
    }
    tail->next = head;  // Make circular
    
    node_t *curr = head, *prev = head;
    // Find tail (node before head)
    while (prev->next != head) prev = prev->next;
    
    while (curr->next != curr) {
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
    }
    int survivor = curr->key;
    free(curr);
    return survivor;
}

int main() {
    printf("=== Circular List Demo ===\n");
    node_t *head = NULL;
    for (int i = 1; i <= 5; i++) insert_clist(&head, i*10);
    printf("List: "); disp_clist(head);
    
    printf("\n=== Josephus Problem ===\n");
    printf("n=7, k=3: Survivor = %d\n", josephus(7, 3));  // 4
    printf("n=5, k=2: Survivor = %d\n", josephus(5, 2));  // 3
    printf("n=41, k=3: Survivor = %d\n", josephus(41, 3)); // Historical: 31
    
    return 0;
}
```

---

## 📝 Key Takeaways for Unit 1

| Concept | Key Point |
|---------|-----------|
| **Data Structure** | Organization of data for efficient operations |
| **ADT** | What operations, not how implemented |
| **Static vs Dynamic** | Static: compile-time, stack; Dynamic: runtime, heap |
| **malloc/calloc/realloc/free** | Core dynamic memory functions |
| **Dangling Pointer** | Pointer to freed memory - SET TO NULL! |
| **Memory Leak** | Lost allocated memory - ALWAYS FREE! |
| **Linked List** | Dynamic size, non-contiguous, pointer-based |
| **Insert/Delete Cases** | Empty, single, beginning, middle, end |
| **Doubly Linked List** | Two pointers (prev/next), O(1) insert/delete |
| **Circular List** | Last → First, use do-while for traversal |
| **Josephus Problem** | Classic circular list application |

---

## 🧪 Practice Exercises

1. **Implement** a singly linked list with: insert at position, delete by value, reverse list
2. **Write** a function to find middle element of linked list (slow/fast pointer)
3. **Implement** doubly linked list with: insert before/after given node
4. **Solve** Josephus problem for n=10, k=4 (trace by hand first!)
5. **Find** and fix memory leaks in given code snippets
6. **Compare** time complexity of array vs linked list operations

---

## 📚 Reference Materials

- **Primary:** Unit 1.pdf (Prof. Vandana M L) - 291 pages
- **Notes:** 14 individual lecture documents
- **Slides:** 13 presentations
- **Assignments:** Weeks 1, 2, 3
- **MCQ Bank:** 20 pages with answers

---

*Next: Unit 2 - Circular Lists, Doubly Linked Lists, Queues, Priority Queues, Deques*