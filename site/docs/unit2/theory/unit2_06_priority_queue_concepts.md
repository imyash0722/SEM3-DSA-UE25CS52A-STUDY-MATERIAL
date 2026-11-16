# Unit 2: Priority Queue Concepts

## 🎯 Priority Queue - Complete Walkthrough

### What is a Priority Queue?

> **Priority Queue** is a queue where each element has a **priority**.
> - Dequeue removes **highest priority** element (not FIFO)
> - Higher numeric value = higher priority (typically)

### Real-World Examples
- Hospital ER: Critical patients first
- CPU scheduling: Real-time processes first
- Network packets: QoS priority
- Dijkstra's algorithm

### Priority Queue ADT
```c
struct job {
    int job_no;
    int priority;
};
typedef struct job job_t;

void init_pq(pqueue_t *q);
void enqueue(pqueue_t *q, job_t *job);
job_t dequeue(pqueue_t *q);  // Returns highest priority job
```

---

## 🎯 Priority Queue: 5 Implementations Compared

| Implementation | Enqueue | Dequeue | Space |
|----------------|---------|---------|-------|
| **Unordered List** | O(1) - add at rear | O(n) - search max | O(n) |
| **Ordered List** | O(n) - find position | O(1) - remove front | O(n) |
| **Unordered Array** | O(1) - add at end | O(n) - search + shift | O(n) |
| **Ordered Array** | O(n) - find + shift | O(1) - remove end | O(n) |
| **Heap (Tree)** | O(log n) | O(log n) | O(n) |

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Priority Queue** | Dequeue by priority, not arrival |
| **PQ ADT** | Same interface, different implementations |
| **Trade-off** | Enqueue vs Dequeue speed |
| **Job Structure** | job_no + priority |

---

*Next: [PQ Implementation 1: Unordered List →](./unit2_07_pq_unordered_list.md)*