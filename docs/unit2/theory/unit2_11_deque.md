# Unit 2: Deque (Double-Ended Queue)

## 🔀 Deque (Double-Ended Queue)

### What is a Deque?
- Insert/Delete at **BOTH** ends
- Can implement both Stack and Queue!

### Operations
```c
void add_front(deque_t *d, int val);
void add_rear(deque_t *d, int val);
int remove_front(deque_t *d);
int remove_rear(deque_t *d);
```

### Stack using Deque
```c
void push(stack_t *s, int val) { add_front(&s->deque, val); }
int pop(stack_t *s) { return remove_front(&s->deque); }
```

### Queue using Deque
```c
void enqueue(queue_t *q, int val) { add_rear(&q->deque, val); }
int dequeue(queue_t *q) { return remove_front(&q->deque); }
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Deque** | Both ends, generalizes Stack/Queue |
| **Stack from Deque** | add_front/remove_front |
| **Queue from Deque** | add_rear/remove_front |

---

*Next: [Unit 2 Anchor Programs →](./unit2_11_anchor_programs.md)*