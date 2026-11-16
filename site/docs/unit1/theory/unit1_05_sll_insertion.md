# Unit 1: Singly Linked List - Insertion Operations

## 🔗 Insertion Operations (3 Cases)

### Visual Overview
```
Before: head → [10|•] → [20|•] → [30|NULL]
        
Insert 5 at front:
1. Create node with data=5, link=NULL
2. temp->link = head (points to 10)
3. head = temp (points to 5)

After:  head → [5|•] → [10|•] → [20|•] → [30|NULL]
```

---

## 📋 Case 1: Insert at Beginning

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

### Step-by-Step Trace:
| Step | Action | head | temp |
|------|--------|------|------|
| 1 | Create node(5) | [10] | [5|NULL] |
| 2 | temp->link = head | [10] | [5|→10] |
| 3 | head = temp | [5] | [5|→10] |

---

## 📋 Case 2: Insert at End

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

### Trace for Insert 40 at End:
```
Before: head → [10] → [20] → [30] → NULL
                            ↑
                         curr

After:  head → [10] → [20] → [30] → [40] → NULL
```

---

## 📋 Case 3: Insert at Given Position

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

### Position Trace (Insert 15 at pos 3):
```
Before: head → [5] → [10] → [20] → [30] → NULL
                        ↑       ↑
                      prev    curr (i=3)

After:  head → [5] → [10] → [15] → [20] → [30] → NULL
```

---

## 🎯 Complete Insertion Example Program

```c
// sll_insert_all.c - All Insertion Cases
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

void display(NODE *head) {
    printf("List: ");
    while (head) { printf("%d → ", head->data); head = head->next; }
    printf("NULL\n");
}

int main() {
    NODE *head = NULL;
    
    printf("=== Insertion Demo ===\n");
    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);
    display(head);  // 10 → 20 → 30
    
    insert_front(&head, 5);
    display(head);  // 5 → 10 → 20 → 30
    
    insert_at_pos(&head, 15, 3);
    display(head);  // 5 → 10 → 15 → 20 → 30
    
    insert_at_pos(&head, 100, 10);  // Beyond end
    display(head);  // ... → 100
    
    return 0;
}
```

---

## 📊 Insertion Cases Summary

| Case | Time | When to Use |
|------|------|-------------|
| **Front** | O(1) | Stack push, priority insert |
| **End** | O(n) | Queue enqueue, append |
| **Position** | O(n) | Ordered insert, specific location |

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Front Insert** | O(1), update head |
| **End Insert** | O(n), traverse to last |
| **Position Insert** | O(n), track prev & curr |
| **Empty List** | Special case for all |
| **malloc** | Every insert needs new node |

---

## 🧪 Self-Test Questions

1. What is the time complexity of insert at end? Why?
2. In position insert, why do we need both `prev` and `curr`?
3. What happens if position > list length + 1?
4. How would you insert in a sorted linked list?

---

*Next: [Singly Linked List - Deletion Operations →](./unit1_06_sll_deletion.md)*