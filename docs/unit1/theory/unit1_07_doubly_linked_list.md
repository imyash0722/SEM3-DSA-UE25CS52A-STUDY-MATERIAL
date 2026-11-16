# Unit 1: Doubly Linked List

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

---

## 📋 Node Structure

```c
struct node {
    int data;
    struct node *prev;  // Previous node
    struct node *next;  // Next node
};
typedef struct node NODE;
```

### Visual:
```
NULL ← [5|•|•] ↔ [10|•|•] ↔ [15|•|•] → NULL
      ↑    ↑      ↑      ↑
     prev data next  prev
```

---

## 📋 List Structure

```c
struct DLL {
    NODE *head;  // First node
    NODE *tail;  // Last node
};
typedef struct DLL dll_t;
```

---

## 🛠️ Key Operations

### Initialize
```c
void init_dll(dll_t *list) {
    list->head = list->tail = NULL;
}
```

### Insert at Beginning
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

### Insert at End
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

### Delete Node (with given pointer)
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

### Traverse Forward
```c
void display_forward(dll_t *list) {
    NODE *curr = list->head;
    printf("Forward: ");
    while (curr) {
        printf("%d ↔ ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}
```

### Traverse Backward
```c
void display_backward(dll_t *list) {
    NODE *curr = list->tail;
    printf("Backward: ");
    while (curr) {
        printf("%d ↔ ", curr->data);
        curr = curr->prev;
    }
    printf("NULL\n");
}
```

---

## 🎯 Complete Example Program

```c
// dll_complete.c - Doubly Linked List
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} NODE;

typedef struct {
    NODE *head, *tail;
} dll_t;

void init_dll(dll_t *list) { list->head = list->tail = NULL; }

NODE* create_node(int data) {
    NODE *n = malloc(sizeof(NODE));
    n->data = data; n->prev = n->next = NULL;
    return n;
}

void insert_front(dll_t *list, int data) {
    NODE *n = create_node(data);
    n->next = list->head;
    if (!list->head) list->head = list->tail = n;
    else { list->head->prev = n; list->head = n; }
}

void insert_end(dll_t *list, int data) {
    NODE *n = create_node(data);
    n->prev = list->tail;
    if (!list->tail) list->head = list->tail = n;
    else { list->tail->next = n; list->tail = n; }
}

void delete_node(dll_t *list, NODE *n) {
    if (!n) return;
    if (n == list->head && n == list->tail) list->head = list->tail = NULL;
    else if (n == list->head) { list->head = n->next; list->head->prev = NULL; }
    else if (n == list->tail) { list->tail = n->prev; list->tail->next = NULL; }
    else { n->prev->next = n->next; n->next->prev = n->prev; }
    free(n);
}

void display_forward(dll_t *list) {
    NODE *c = list->head;
    printf("Forward: ");
    while (c) { printf("%d ", c->data); c = c->next; }
    printf("\n");
}

void display_backward(dll_t *list) {
    NODE *c = list->tail;
    printf("Backward: ");
    while (c) { printf("%d ", c->data); c = c->prev; }
    printf("\n");
}

int main() {
    dll_t list; init_dll(&list);
    
    insert_end(&list, 10);
    insert_end(&list, 20);
    insert_end(&list, 30);
    insert_front(&list, 5);
    
    display_forward(&list);   // 5 10 20 30
    display_backward(&list);  // 30 20 10 5
    
    return 0;
}
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Two Pointers** | `prev` and `next` in each node |
| **Head & Tail** | List tracks both ends |
| **O(1) Insert/Delete** | At both ends, with node pointer |
| **Bidirectional** | Traverse forward and backward |
| **Space Trade-off** | Extra `prev` pointer per node |

---

## 🧪 Self-Test Questions

1. Why does doubly linked list make insert before a node O(1)?
2. What are the 4 cases for deletion in DLL?
3. How does the `tail` pointer simplify end operations?
5. What is the memory overhead compared to singly linked list?

---

*Next: [Circular Linked List →](./unit1_08_circular_linked_list.md)*