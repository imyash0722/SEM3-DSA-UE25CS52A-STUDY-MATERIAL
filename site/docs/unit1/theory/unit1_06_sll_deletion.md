# Unit 1: Singly Linked List - Deletion Operations

## 🔗 Deletion Operations (3 Cases)

### Visual Overview
```
Before: head → [5|•] → [10|•] → [15|•] → [20|•] → [30|NULL]

Delete Front (5):
After:  head → [10|•] → [15|•] → [20|•] → [30|NULL]

Delete End (30):
After:  head → [5|•] → [10|•] → [15|•] → [20|NULL]

Delete Position 3 (15):
After:  head → [5|•] → [10|•] → [20|•] → [30|NULL]
```

---

## 📋 Case 1: Delete First Node

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

### Trace for Single Node:
```
Before: head → [10|NULL]
After:  head → NULL (temp freed)
```

### Trace for Multiple Nodes:
```
Before: head → [10] → [20] → [30]
temp = head (10)
head = head->link (20)
free(temp)  // 10 freed
After:  head → [20] → [30]
```

---

## 📋 Case 2: Delete Last Node

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

### Trace:
```
Before: head → [5] → [10] → [15] → [20] → [30] → NULL
                                              ↑      ↑
                                            prev   curr

After:  head → [5] → [10] → [15] → [20] → NULL
```

---

## 📋 Case 3: Delete at Given Position

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

### Trace (Delete Position 3):
```
Before: head → [5] → [10] → [15] → [20] → [30]
                        ↑       ↑
                      prev    curr (i=3)

After:  head → [5] → [10] → [20] → [30]
```

---

## 🎯 Complete Deletion Example Program

```c
// sll_delete_all.c - All Deletion Cases
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

void insert_end(NODE **head, int data) {
    NODE *temp = create_node(data);
    if (*head == NULL) { *head = temp; return; }
    NODE *curr = *head;
    while (curr->next) curr = curr->next;
    curr->next = temp;
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
    prev->link = curr->link;
    free(curr);
}

void display(NODE *head) {
    printf("List: ");
    while (head) { printf("%d → ", head->data); head = head->next; }
    printf("NULL\n");
}

int main() {
    NODE *head = NULL;
    
    printf("=== Deletion Demo ===\n");
    for (int i = 1; i <= 5; i++) insert_end(&head, i*10);
    display(head);  // 10 → 20 → 30 → 40 → 50
    
    delete_front(&head);
    display(head);  // 20 → 30 → 40 → 50
    
    delete_end(&head);
    display(head);  // 20 → 30 → 40
    
    delete_at_pos(&head, 2);
    display(head);  // 20 → 40
    
    return 0;
}
```

---

## 📊 Deletion Cases Summary

| Case | Time | When to Use |
|------|------|-------------|
| **Front** | O(1) | Stack pop, remove first |
| **End** | O(n) | Remove last element |
| **Position** | O(n) | Remove specific element |

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Front Delete** | O(1), update head |
| **End Delete** | O(n), need prev pointer |
| **Position Delete** | O(n), track prev & curr |
| **Single Node** | Special case for all |
| **free()** | Always free deleted node |
| **Order Matters** | Save next before freeing |

---

## 🧪 Self-Test Questions

1. Why do we need a `prev` pointer for end deletion?
2. What happens if you free the node before updating links?
3. What is the time complexity of deleting the last node?
4. How would you delete all nodes with a specific value?

---

*Next: [Doubly Linked List →](./unit1_07_doubly_linked_list.md)*