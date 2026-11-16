## 2.4 Queue (Circular Array Implementation)


### Structure
```c
#define MAXSIZE 5

struct queue {
    int key_[MAXSIZE];
    int front_;  // Index of front element
    int rear_;   // Index of rear element
};
typedef struct queue queue_t;
```

### Key Design Decisions
1. **Modulo arithmetic** for circular wrapping: `i = (i + 1) % MAXSIZE`
2. **Waste one slot** to distinguish empty vs full
3. **Initialize**: `front_ = rear_ = 0`

### Operations

#### Enqueue
```c
void enque(queue_t *ptr_queue, int key) {
    int temp = (ptr_queue->rear_ + 1) % MAXSIZE;
    if (temp != ptr_queue->front_) {  // Not full
        ptr_queue->rear_ = temp;
        ptr_queue->key_[temp] = key;
    } else {
        printf("queue full\n");
    }
}
```

#### Dequeue
```c
int deque(queue_t *ptr_queue) {
    if (ptr_queue->front_ != ptr_queue->rear_) {  // Not empty
        ptr_queue->front_ = (ptr_queue->front_ + 1) % MAXSIZE;
        return ptr_queue->key_[ptr_queue->front_];
    }
    printf("queue empty\n");
    return '\0';
}
```

#### Empty/Full (SAME condition!)
```c
int is_empty(queue_t *ptr_queue) {
    return ptr_queue->front_ == ptr_queue->rear_;  // Before dequeue
}

int is_full(queue_t *ptr_queue) {
    return ptr_queue->front_ == ptr_queue->rear_;  // After enqueue increment
}
```

**Why this works:**
- Empty: front == rear BEFORE any operation
- Full: front == rear AFTER incrementing rear in enqueue
- We waste one array slot to make this distinction

---