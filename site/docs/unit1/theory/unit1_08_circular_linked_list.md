# Unit 1: Circular Linked List

## 🔵 Circular Linked List

### Concept
- Last node points back to first node
- Forms a cycle
- Head pointer can point to ANY node in the cycle
- No NULL termination - use do-while for traversal

### Visual:
```
head → [10] → [20] → [30] → [40]
  ↑                        ↓
  └────────────────────────┘
```

---

## 📋 Node Structure (Same as Singly)

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

---

## 🛠️ Key Operations

### Initialize
```c
void init_clist(clist_t *list) {
    list->head = NULL;
}
```

### Insert (after head)
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

### Display (use do-while!)
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

### Why do-while?
- While loop would not execute if we check condition first
- do-while executes at least once, then checks
- Guarantees we visit all nodes exactly once

---

## 🎯 Josephus Problem (Classic Application)

### Problem Statement:
> n people stand in a circle. Starting from a designated person, count k people and eliminate the k-th person. Continue until one survivor remains.

### Algorithm:
1. Create circular list with people 1 to n
2. Count k-1 steps
3. Remove k-th person
4. Repeat until one remains

### Implementation:
```c
int josephus(int n, int k) {
    // Create circular list 1..n
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; i++) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key = i; temp->next = NULL;
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

### Example Trace (n=7, k=3):
```
Initial:  1 2 3 4 5 6 7
Step 1:   Eliminate 3  →  1 2 4 5 6 7
Step 2:   Eliminate 6  →  1 2 4 5 7
Step 3:   Eliminate 2  →  1 4 5 7
Step 4:   Eliminate 7  →  1 4 5
Step 5:   Eliminate 5  →  1 4
Step 6:   Eliminate 1  →  4
Survivor: 4
```

---

## 🎯 Complete Example Program

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

int josephus(int n, int k) {
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; i++) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key = i; temp->next = NULL;
        if (!head) head = tail = temp;
        else { tail->next = temp; tail = temp; }
    }
    tail->next = head;  // Make circular
    
    node_t *curr = head, *prev = tail;
    
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

**Output:**
```
=== Circular List Demo ===
List: Circular: 50 40 30 20 10 

=== Josephus Problem ===
n=7, k=3: Survivor = 4
n=5, k=2: Survivor = 3
n=41, k=3: Survivor = 31
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Circular** | Last → First, no NULL |
| **Head** | Points to any node |
| **Traversal** | Use do-while loop |
| **Insert** | After head (or any position) |
| **Josephus** | Classic circular list application |

---

## 🧪 Self-Test Questions

1. Why do we use do-while instead of while for circular list traversal?
2. What happens if head points to a middle node during traversal?
3. How would you delete a node from a circular list?
4. What is the time complexity of Josephus with circular list?

---

*Next: [Unit 1 Anchor Programs →](./unit1_09_anchor_programs.md)*