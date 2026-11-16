# Unit 2: PQ Implementation 3 - Unordered Array

## 🎯 Priority Queue: Unordered Array Implementation

### Implementation 3: Unordered Array

```c
#define MAXSIZE 100

struct pqueue {
    job_t jobs[MAXSIZE];
    int count;
};

void enqueue(pqueue_t *q, job_t *job) {
    if (q->count < MAXSIZE)
        q->jobs[q->count++] = *job;
}

job_t dequeue(pqueue_t *q) {
    int max_idx = 0;
    for (int i = 1; i < q->count; i++)
        if (q->jobs[i].priority > q->jobs[max_idx].priority)
            max_idx = i;
    
    job_t job = q->jobs[max_idx];
    // Shift left
    for (int i = max_idx; i < q->count - 1; i++)
        q->jobs[i] = q->jobs[i + 1];
    q->count--;
    return job;
}
```

---

## 📝 Key Takeaways

| Implementation | Enqueue | Dequeue |
|----------------|---------|---------|
| **Unordered Array** | O(1) | O(n) |

---

*Next: [PQ Implementation 4: Ordered Array →](./unit2_10_pq_ordered_array.md)*