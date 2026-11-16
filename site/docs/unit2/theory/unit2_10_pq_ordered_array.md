# Unit 2: PQ Implementation 4 - Ordered Array

## 🎯 Priority Queue: Ordered Array Implementation

### Implementation 4: Ordered Array

```c
void enqueue(pqueue_t *q, job_t *job) {
    int i = q->count - 1;
    while (i >= 0 && q->jobs[i].priority >= job->priority) {
        q->jobs[i + 1] = q->jobs[i];
        i--;
    }
    q->jobs[i + 1] = *job;
    q->count++;
}

job_t dequeue(pqueue_t *q) {
    return q->jobs[--q->count];  // Last element = highest priority
}
```

---

## 📝 Key Takeaways

| Implementation | Enqueue | Dequeue |
|----------------|---------|---------|
| **Ordered Array** | O(n) | O(1) |

---

*Next: [Deque →](./unit2_11_deque.md)*