## 2.7 Deque (Double-Ended Queue)


### Concept
- Add/remove at **BOTH ends**
- Pronounced "deck"
- Can implement Stack and Queue using Deque

### Interface (using Doubly Linked List)
```c
void init(dll_t*);
void deinit(dll_t*);
void add_in_begin(dll_t*, int key);
void add_at_end(dll_t*, int key);
int remove_in_begin(dll_t*);
int remove_at_end(dll_t*);
int is_empty(dll_t*);
int is_full(dll_t*);
```

### Stack using Deque (Composition)
```c
struct stack {
    dll_t list_;  // Embedded deque
};
typedef struct stack stack_t;

void push(stack_t *ptr_stack, int key) {
    add_in_begin(&ptr_stack->list_, key);
}

int pop(stack_t *ptr_stack) {
    return remove_in_begin(&ptr_stack->list_);
}

int is_empty_stack(stack_t *ptr_stack) {
    return is_empty(&ptr_stack->list_);
}
```

### Queue using Deque
```c
void enqueue(queue_t *ptr_queue, int key) {
    add_at_end(&ptr_queue->list_, key);
}

int dequeue(queue_t *ptr_queue) {
    return remove_in_begin(&ptr_queue->list_);
}
```

---