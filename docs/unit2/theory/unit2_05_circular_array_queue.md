# Unit 2: Circular Array Queue

## 🔄 Circular Array Queue

### Why Circular Array?
- Array is fixed size
- Simple indices: front=0, rear=0 initially
- Use modulo arithmetic to wrap around
- **Waste ONE slot** to distinguish full vs empty

### Structure
```c
#define MAXSIZE 5

struct queue {
    int data[MAXSIZE];
    int front;  // Index of front element
    int rear;   // Index of rear element
};
typedef struct queue queue_t;
```

### Key Concept: Modulo Arithmetic
```
Index = (Index + 1) % MAXSIZE
```

**Visual:**
```
Array size 5: [ ][ ][ ][ ][ ]
                ↑
              front=rear=0 (empty)

Enqueue 10:  rear = (0+1)%5 = 1, data[1]=10
    [ ][10][ ][ ][ ]
           ↑   ↑
          f=0  r=1

Enqueue 20:  rear = (1+1)%5 = 2, data[2]=20
    [ ][10][20][ ][ ]
           ↑     ↑
          f=0   r=2

... continue until r=4
    [50][10][20][30][40]
     ↑            ↑
    f=0          r=4

Enqueue 50: rear = (4+1)%5 = 0
    rear == front? → FULL! (wasted one slot)
```

### Operations

```c
void init_queue(queue_t *q) {
    q->front = q->rear = 0;
}

int is_empty(queue_t *q) {
    return q->front == q->rear;
}

int is_full(queue_t *q) {
    return (q->rear + 1) % MAXSIZE == q->front;
}

void enqueue(queue_t *q, int val) {
    if (is_full(q)) { printf("Queue full\n"); return; }
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = val;
}

int dequeue(queue_t *q) {
    if (is_empty(q)) return -1;
    q->front = (q->front + 1) % MAXSIZE;
    return q->data[q->front];
}
```

### Key Concept: Same Condition for Empty/Full
- **Empty:** front == rear (before any operation)
- **Full:** front == rear (after rear increment in enqueue)
- We waste one slot to distinguish them

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Circular Queue** | Modulo arithmetic, wrap around |
| **Waste 1 Slot** | Distinguish full vs empty |
| **front==rear** | Empty before op, Full after rear++ |
| **Modulo** | (index + 1) % MAXSIZE |

---

*Next: [Priority Queue Concepts →](./unit2_06_priority_queue_concepts.md)*