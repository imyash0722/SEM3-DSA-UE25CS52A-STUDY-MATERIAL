# Unit 2: PQ Implementation 2 - Ordered List

## 🎯 Priority Queue: Ordered List Implementation

### Implementation 2: Ordered Linked List

**Enqueue:** O(n) - Find correct position by priority
**Dequeue:** O(1) - Remove from front

```c
void enqueue(pqueue_t *q, job_t *job) {
    node_t *temp = create_node(job);
    
    // Insert in descending priority order
    if (!q->front || q->front->job.priority <= job->priority) {
        // Insert at front
        temp->next = q->front;
        q->front = temp;
        if (!q->rear) q->rear = temp;
    } else {
        // Find position
        node_t *curr = q->front;
        while (curr->next && curr->next->job.priority > job->priority)
            curr = curr->next;
        temp->next = curr->next;
        curr->next = temp;
        if (!temp->next) q->rear = temp;
    }
}

job_t dequeue(pqueue_t *q) {
    job_t job = q->front->job;
    node_t *temp = q->front;
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return job;
}
```

---

## 📝 Key Takeaways

| Implementation | Enqueue | Dequeue |
|----------------|---------|---------|
| **Ordered List** | O(n) | O(1) |

---

*Next: [PQ Implementation 3: Unordered Array →](./unit2_09_pq_unordered_array.md)*