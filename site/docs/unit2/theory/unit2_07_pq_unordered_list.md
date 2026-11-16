# Unit 2: PQ Implementation 1 - Unordered List

## 🎯 Priority Queue: Unordered List Implementation

### Implementation 1: Unordered Linked List

**Enqueue:** O(1) - Add at rear
**Dequeue:** O(n) - Traverse to find max priority

```c
job_t dequeue(pqueue_t *q) {
    // Find max priority node
    node_t *max_prev = NULL, *max_curr = q->front;
    node_t *prev = NULL, *curr = q->front;
    int max_pri = curr->job.priority;
    
    while (curr) {
        if (curr->job.priority > max_pri) {
            max_pri = curr->job.priority;
            max_prev = prev;
            max_curr = curr;
        }
        prev = curr;
        curr = curr->next;
    }
    
    // Remove max_curr
    job_t job = max_curr->job;
    if (max_prev == NULL)  // Was first node
        q->front = max_curr->next;
    else
        max_prev->next = max_curr->next;
    
    free(max_curr);
    return job;
}
```

---

## 📝 Key Takeaways

| Implementation | Enqueue | Dequeue |
|----------------|---------|---------|
| **Unordered List** | O(1) | O(n) |

---

*Next: [PQ Implementation 2: Ordered List →](./unit2_08_pq_ordered_list.md)*