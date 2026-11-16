## 2.1 Circular Linked List


### Concept
- Last node points back to first node
- No NULL termination - cycle continues
- Head pointer can point to ANY node in the cycle
- Useful for: Round-robin scheduling, music playlists, token passing

### Structure
```c
struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

struct clist {
    node_t *head_;  // Points to any node in cycle
};
typedef struct clist clist_t;
```

### Operations

#### Initialize
```c
void init_list(clist_t* ptr_clist) {
    ptr_clist->head_ = NULL;
}
```

#### Insert (after head)
```c
void insert(clist_t* ptr_clist, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    
    if (ptr_clist->head_ == NULL) {
        temp->next_ = temp;           // Points to self
        ptr_clist->head_ = temp;
    } else {
        temp->next_ = ptr_clist->head_->next_;
        ptr_clist->head_->next_ = temp;
    }
}
```

#### Display (do-while preferred)
```c
void disp_list(clist_t* ptr_clist) {
    if (ptr_clist->head_ == NULL) {
        printf("List is empty\n");
        return;
    }
    node_t *temp = ptr_clist->head_;
    printf("Circular List: ");
    do {
        printf("%d ", temp->key_);
        temp = temp->next_;
    } while (temp != ptr_clist->head_);
    printf("\n");
}
```

### Josephus Problem
**Problem**: n people in circle, eliminate every k-th person, find survivor.

```c
// josephus.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

int josephus(int n, int k) {
    // Create circular list 1..n
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; ++i) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key_ = i;
        if (!head) {
            head = tail = temp;
        } else {
            tail->next_ = temp;
            tail = temp;
        }
    }
    tail->next_ = head;  // Make circular
    
    node_t *curr = head, *prev = tail;
    while (curr->next_ != curr) {
        // Count k-1 steps
        for (int i = 1; i < k; ++i) {
            prev = curr;
            curr = curr->next_;
        }
        // Eliminate curr
        prev->next_ = curr->next_;
        free(curr);
        curr = prev->next_;
    }
    int survivor = curr->key_;
    free(curr);
    return survivor;
}

int main() {
    printf("Survivor: %d\n", josephus(7, 3));  // Output: 4
    return 0;
}
```

### Circular List Quiz Answers
1. End of traversal: **Check if returned to starting node** (c)
2. `while(temp != NULL)` on circular list: **Infinite loop** (a)
3. Fast/slow pointer on even nodes: **May infinite loop** (c)
4. Single node: `head_ == head_->next_` (c)
5. Delete only node: `head_ becomes NULL` (b)

---