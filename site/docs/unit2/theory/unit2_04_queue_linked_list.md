# Unit 2: Queue - Linked List Implementation

## 📋 Queue - Complete Walkthrough

### What is a Queue?

> **Queue** is a linear data structure following **FIFO (First In First Out)**.
> - Insert at **rear** (enqueue)
> - Remove from **front** (dequeue)

### Real-World Examples
- Printer queue
- CPU process scheduling
- Ticket counter line
- Breadth-First Search (BFS)

---

## 🔗 Queue Implementation 1: Linked List

### Structure
```c
struct node {
    int data;
    struct node *next;
};
typedef struct node node_t;

struct queue {
    node_t *front;  // First element
    node_t *rear;   // Last element
};
typedef struct queue queue_t;
```

### Operations

#### Enqueue (Insert at Rear)
```c
void enqueue(queue_t *q, int val) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->data = val;
    temp->next = NULL;
    
    if (q->rear == NULL) {
        // Empty queue - new node is both front and rear
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}
```

#### Dequeue (Remove from Front)
```c
int dequeue(queue_t *q) {
    if (q->front == NULL) return -1;  // Empty
    
    node_t *temp = q->front;
    int val = temp->data;
    
    q->front = temp->next;
    if (q->front == NULL)  // Was last element
        q->rear = NULL;
    
    free(temp);
    return val;
}
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Queue** | FIFO, Enqueue at rear, Dequeue at front |
| **Linked Queue** | Dynamic size, no fixed limit |
| **Front & Rear** | Two pointers for O(1) operations |
| **Empty** | front == NULL |
| **Single Node** | Front and rear point to same node |

---

*Next: [Circular Array Queue →](./unit2_05_circular_array_queue.md)*