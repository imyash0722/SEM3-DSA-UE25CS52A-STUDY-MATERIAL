# Unit 1: Lists and Linked Lists

## List ADT

- Zero or more components
- Each has ordinal position
- **Sequential access** (no random/direct access)
- Insert/delete at known position: few operations

**Interface:**
```c
void init(list_t*);
void destroy(list_t*);
void insert(list_t*, int key);
void delete(list_t*, int key);
void traverse(list_t*);
```

## Linked List Implementation

### Self-Referential Structure

```c
struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;
```

### Building a List

```c
node_t *p = (node_t*)malloc(sizeof(node_t));
p->key_ = 20;
p->next_ = (node_t*)malloc(sizeof(node_t));
p->next_->key_ = 40;
p->next_->next_ = (node_t*)malloc(sizeof(node_t));
p->next_->next_->key_ = 60;
p->next_->next_->next_ = NULL;
```

### Traversal (THE key statement)

```c
void disp(node_t* q) {
    while (q != NULL) {
        printf("%d ", q->key_);
        q = q->next_;  // Most important statement in data structures!
    }
}
```

### Freeing List

```c
void freelist(node_t* q) {
    node_t* r;
    while (q != NULL) {
        r = q->next_;  // Save next BEFORE freeing
        free(q);
        q = r;
    }
}
```

---