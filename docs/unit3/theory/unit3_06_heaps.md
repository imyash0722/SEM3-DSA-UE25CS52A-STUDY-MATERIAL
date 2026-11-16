# Unit 3: Heaps

## 📦 Heaps

### Definition (Max-Heap)
> **Heap** = Complete Binary Tree + Parental Dominance
> 1. **Complete**: All levels full except last (left-filled)
> 2. **Parental Dominance**: Parent ≥ Children (recursively)

### Array Representation (1-indexed)
```
Left(i) = 2*i, Right(i) = 2*i+1, Parent(i) = i/2
```

### Structure
```c
#define MAXSIZE 100
struct heap {
    int key[MAXSIZE];
    int n;  // Number of elements
};
typedef struct heap heap_t;
```

### Core Operations

#### Heapify (Fix subtree at position i)
```c
void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2*i, right = 2*i + 1;
    
    if (left <= n && a[left] > a[largest]) largest = left;
    if (right <= n && a[right] > a[largest]) largest = right;
    
    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}
```

#### Build Heap (O(n))
```c
void build_heap(heap_t *h, int a[], int n) {
    h->n = n;
    for (int i = 1; i <= n; i++) h->key[i] = a[i];
    for (int i = n/2; i >= 1; i--)  // Start from last internal node
        heapify(h->key, h->n, i);
}
```

#### Insert (O(log n))
```c
void insert(heap_t *h, int key) {
    int i = ++h->n;
    h->key[i] = key;
    // Bubble up
    while (i > 1 && h->key[i] > h->key[i/2]) {
        swap(&h->key[i], &h->key[i/2]);
        i = i/2;
    }
}
```

#### Delete Max (O(log n))
```c
int delete_max(heap_t *h) {
    int max = h->key[1];
    h->key[1] = h->key[h->n--];  // Move last to root
    heapify(h->key, h->n, 1);    // Fix from root
    return max;
}
```

### Heapsort (O(n log n))
```c
void heapsort(int a[], int n) {
    heap_t h; build_heap(&h, a, n);
    for (int i = n; i >= 1; i--)
        a[i] = delete_max(&h);  // Extract max to end
}
```

### Priority Queue using Heap
```c
struct pqueue { heap_t h; };
void pq_enqueue(pqueue_t *q, int key) { insert(&q->h, key); }
int pq_dequeue(pqueue_t *q) { return delete_max(&q->h); }
// Both O(log n)!
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Heap** | Complete tree + parental dominance |
| **Array (1-indexed)** | Left=2i, Right=2i+1, Parent=i/2 |
| **Build Heap** | O(n) |
| **Insert/Delete** | O(log n) |
| **Heapsort** | O(n log n), in-place |
| **PQ with Heap** | Both O(log n) |

---

*Next: [AVL Trees →](./unit3_07_avl_trees.md)*