## 2.3 Queue (Linked List Implementation)


### Queue ADT
- **FIFO** (First In First Out)
- Two ends: **front** (remove), **rear** (insert)

### Interface
```c
void init_queue(queue_t*);
void deinit_queue(queue_t*);
void enque(queue_t*, int key);
int deque(queue_t*);
int is_empty(queue_t*);
int is_full(queue_t*);
```

### Structure (Design 2: front → next → ... → rear)
```c
struct node {
    int key_;
    struct node* next_;
};
typedef struct node node_t;

struct queue {
    node_t* front_;
    node_t* rear_;
};
typedef struct queue queue_t;
```

### Operations

#### Initialize
```c
void init_queue(queue_t *ptr_queue) {
    ptr_queue->front_ = ptr_queue->rear_ = NULL;
}
```

#### Enqueue (add at rear)
```c
void enque(queue_t *ptr_queue, int key) {
    if (!is_full(ptr_queue)) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->key_ = key; temp->next_ = NULL;
        
        if (ptr_queue->rear_ == NULL) {
            // Empty queue - new node is both front and rear
            ptr_queue->front_ = temp;
        } else {
            ptr_queue->rear_->next_ = temp;
        }
        ptr_queue->rear_ = temp;
    }
}
```

#### Dequeue (remove from front)
```c
int deque(queue_t *ptr_queue) {
    if (!is_empty(ptr_queue)) {
        node_t* temp = ptr_queue->front_;
        int key = temp->key_;
        
        ptr_queue->front_ = temp->next_;
        if (ptr_queue->front_ == NULL) {
            // Was only node
            ptr_queue->rear_ = NULL;
        }
        free(temp);
        return key;
    }
    return '\0';
}
```

#### Empty/Full Check
```c
int is_empty(queue_t *ptr_queue) {
    return ptr_queue->front_ == NULL;
}

int is_full(queue_t *ptr_queue) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) return 1;
    free(temp);
    return 0;
}
```

---