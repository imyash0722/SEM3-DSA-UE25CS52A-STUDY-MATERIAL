## 3.6 Heaps


### Definition
**Max-Heap** (Min-Heap similar):
1. **Complete Binary Tree** - all levels full except last (left-filled)
2. **Parental Dominance** - parent ≥ children (recursively)

### Array Representation (1-indexed)
```
Left(i) = 2i, Right(i) = 2i+1, Parent(i) = i/2
```
- No pointers needed!
- No wasted space (complete tree)
- Easy traversal

### Structure
```c
#define MAXSIZE 100

struct heap {
    int key_[MAXSIZE];
    int n_;  // Number of elements
};
typedef struct heap heap_t;
```

### Operations

#### Heapify (Fix subtree at pos)
```c
void heapify(int a[], int n, int pos) {
    int i = pos, j = 2*i;
    int val = a[i];
    int is_heap = 0;
    
    while (j <= n && !is_heap) {
        if (j+1 <= n && a[j+1] > a[j]) ++j;  // Larger child
        if (a[j] > val) {
            a[i] = a[j];   // Move child up
            i = j; j = 2*i;  // Move down
        } else is_heap = 1;
    }
    a[i] = val;
}
```

#### Build Heap (O(n))
```c
void build_heap(heap_t* h, int a[], int n) {
    h->n_ = n;
    for (int i = 1; i <= n; ++i) h->key_[i] = a[i];
    for (int i = n/2; i >= 1; --i)  // Start from last internal node
        heapify(h->key_, h->n_, i);
}
```

#### Insert (O(log n))
```c
void insert(heap_t* h, int key) {
    int pos = ++h->n_;
    h->key_[pos] = key;
    
    // Bubble up
    while (pos > 1 && h->key_[pos] > h->key_[pos/2]) {
        swap(&h->key_[pos], &h->key_[pos/2]);
        pos = pos/2;
    }
}
```

#### Delete Max (O(log n))
```c
int delete_max(heap_t* h) {
    int res = h->key_[1];
    h->key_[1] = h->key_[h->n_];  // Move last to root
    --h->n_;
    heapify(h->key_, h->n_, 1);   // Fix from root
    return res;
}
```

### Heap Applications

#### Priority Queue with Heap
```c
struct queue { heap_t q_; };
typedef struct queue queue_t;

void enqueue(queue_t* q, int key) { insert(&q->q_, key); }
int dequeue(queue_t* q) { return delete_max(&q->q_); }
```

**Operations**: O(log n) for both insert and delete

#### Heapsort
```c
void heapsort(int a[], int n) {
    heap_t h; build_heap(&h, a, n);
    for (int i = n; i >= 1; --i)
        a[i] = delete_max(&h);  // Extract max to end
}
```
- Time: O(n log n)
- Space: O(1) extra
- **Not cache-friendly** - not used in standard libraries

---