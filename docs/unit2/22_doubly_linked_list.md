## 2.2 Doubly Linked List


### Concept
- Each node has `prev_` and `next_` pointers
- List has `head_` and `tail_` pointers
- Bidirectional traversal
- Easier insertion/deletion (no trailing pointer needed)

### Structure
```c
struct node {
    int key_;
    struct node *prev_;
    struct node *next_;
};
typedef struct node node_t;

struct DLL {
    node_t *head_;
    node_t *tail_;
};
typedef struct DLL dll_t;
```

### Operations

#### Initialize
```c
void init_dll(dll_t *ptr_dll) {
    ptr_dll->head_ = ptr_dll->tail_ = NULL;
}
```

#### Insert (4 cases)
```c
void insert_dll(dll_t *ptr_dll, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    
    if (!ptr_dll->head_) {  // Empty list
        temp->prev_ = temp->next_ = NULL;
        ptr_dll->head_ = ptr_dll->tail_ = temp;
    }
    // Add at beginning
    else if (key < ptr_dll->head_->key_) {
        temp->prev_ = NULL;
        temp->next_ = ptr_dll->head_;
        ptr_dll->head_->prev_ = temp;
        ptr_dll->head_ = temp;
    }
    // Add at end
    else if (key > ptr_dll->tail_->key_) {
        temp->next_ = NULL;
        temp->prev_ = ptr_dll->tail_;
        ptr_dll->tail_->next_ = temp;
        ptr_dll->tail_ = temp;
    }
    // Add in middle
    else {
        node_t *pres = ptr_dll->head_;
        while (pres->key_ < key) pres = pres->next_;
        temp->next_ = pres;
        temp->prev_ = pres->prev_;
        pres->prev_->next_ = temp;
        pres->prev_ = temp;
    }
}
```

#### Delete (4 cases)
```c
void delete_dll(dll_t *ptr_dll, int key) {
    node_t *pres = ptr_dll->head_;
    while (pres && pres->key_ != key) pres = pres->next_;
    if (!pres) return;  // Not found
    
    if (pres == ptr_dll->head_ && pres == ptr_dll->tail_) {
        // Only node
        ptr_dll->head_ = ptr_dll->tail_ = NULL;
    } else if (pres == ptr_dll->head_) {
        // First node
        ptr_dll->head_ = pres->next_;
        ptr_dll->head_->prev_ = NULL;
    } else if (pres == ptr_dll->tail_) {
        // Last node
        ptr_dll->tail_ = pres->prev_;
        ptr_dll->tail_->next_ = NULL;
    } else {
        // Middle node
        pres->prev_->next_ = pres->next_;
        pres->next_->prev_ = pres->prev_;
    }
    free(pres);
}
```

#### Traversal
```c
// Forward
void disp_forward(dll_t *ptr_dll) {
    node_t *temp = ptr_dll->head_;
    while (temp) {
        printf("%d ", temp->key_);
        temp = temp->next_;
    }
    printf("\n");
}

// Backward
void disp_backward(dll_t *ptr_dll) {
    node_t *temp = ptr_dll->tail_;
    while (temp) {
        printf("%d ", temp->key_);
        temp = temp->prev_;
    }
    printf("\n");
}
```

### Singly vs Doubly Linked List Comparison

| Operation | Singly | Doubly |
|-----------|--------|--------|
| Move Forward | 1 step | 1 step |
| Move Backward | n steps | 1 step |
| Insert Before | n steps (find prev) | 1 step |
| Delete Node | n steps (find prev) | 1 step |
| Search | n steps | n steps |
| Memory | 1 pointer/node | 2 pointers/node |

**Trade-off**: Time-Space trade-off - doubly linked uses more space, gains time.

### Applications
1. **Browser History** - back/forward buttons
2. **Music Player** - previous/next track
3. **Undo/Redo** - bidirectional state changes
4. **LRU Cache** - move accessed items to front
5. **Round Robin Scheduling** - circular doubly linked

---