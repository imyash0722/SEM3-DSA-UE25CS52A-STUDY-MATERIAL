## 2.6 Priority Queue Implementations


### Comparison Table

| Implementation | Enqueue | Dequeue |
|----------------|---------|---------|
| **Unordered List** | O(1) - add at rear | O(n) - search max |
| **Ordered List** | O(n) - find position | O(1) - remove front |
| **Unordered Array** | O(1) - add at end | O(n) - search + shift |
| **Ordered Array** | O(n) - find + shift | O(1) - remove end |
| **Heap** | O(log n) | O(log n) |

---

### 2.6.1 Unordered List (Enqueue O(1), Dequeue O(n))

```c
struct node {
    job_t jobx_;
    struct node* next_;
};
typedef struct node node_t;

struct queue {
    node_t* front_;
    node_t* rear_;
};
typedef struct queue queue_t;

void enque(queue_t *ptr_queue, job_t *ptr_job) {
    if (!is_full(ptr_queue)) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->jobx_ = *ptr_job;
        temp->next_ = NULL;
        
        if (ptr_queue->rear_ == NULL)
            ptr_queue->front_ = temp;
        else
            ptr_queue->rear_->next_ = temp;
        ptr_queue->rear_ = temp;
    }
}

job_t deque(queue_t *ptr_queue) {
    if (!is_empty(ptr_queue)) {
        // Find max priority node
        node_t *prev = NULL, *pres = ptr_queue->front_;
        int max_pri = get_priority(&pres->jobx_);
        node_t *max_prev = NULL, *max_pres = pres;
        
        while (pres) {
            int pri = get_priority(&pres->jobx_);
            if (pri > max_pri) {
                max_pri = pri;
                max_prev = prev;
                max_pres = pres;
            }
            prev = pres;
            pres = pres->next_;
        }
        
        job_t jobx = max_pres->jobx_;
        
        if (max_prev == NULL) {
            ptr_queue->front_ = max_pres->next_;
            if (!ptr_queue->front_) ptr_queue->rear_ = NULL;
        } else {
            max_prev->next_ = max_pres->next_;
            if (!max_pres->next_) ptr_queue->rear_ = max_prev;
        }
        free(max_pres);
        return jobx;
    }
    exit(1);
}
```

---

### 2.6.2 Ordered List (Enqueue O(n), Dequeue O(1))

```c
void enque(queue_t *ptr_queue, job_t *ptr_job) {
    if (!is_full(ptr_queue)) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->jobx_ = *ptr_job;
        
        // Insert in descending priority order
        if (!ptr_queue->front_ || 
            get_priority(&ptr_queue->front_->jobx_) <= get_priority(ptr_job)) {
            // Insert at front
            temp->next_ = ptr_queue->front_;
            ptr_queue->front_ = temp;
            if (!ptr_queue->rear_) ptr_queue->rear_ = temp;
        } else {
            node_t *pres = ptr_queue->front_;
            while (pres->next_ && 
                   get_priority(&pres->next_->jobx_) > get_priority(ptr_job))
                pres = pres->next_;
            temp->next_ = pres->next_;
            pres->next_ = temp;
            if (!temp->next_) ptr_queue->rear_ = temp;
        }
    }
}

job_t deque(queue_t *ptr_queue) {
    if (!is_empty(ptr_queue)) {
        job_t jobx = ptr_queue->front_->jobx_;
        node_t *temp = ptr_queue->front_;
        ptr_queue->front_ = temp->next_;
        if (!ptr_queue->front_) ptr_queue->rear_ = NULL;
        free(temp);
        return jobx;
    }
    exit(1);
}
```

---

### 2.6.3 Unordered Array (Enqueue O(1), Dequeue O(n))

```c
#define MAXSIZE 10

struct queue {
    job_t key_[MAXSIZE];
    int n_;  // Count of elements
};
typedef struct queue queue_t;

void enque(queue_t *ptr_queue, job_t *ptr_job) {
    if (ptr_queue->n_ < MAXSIZE) {
        ptr_queue->key_[ptr_queue->n_++] = *ptr_job;  // Add at end
    }
}

job_t deque(queue_t *ptr_queue) {
    if (ptr_queue->n_ > 0) {
        int max_idx = 0;
        for (int i = 1; i < ptr_queue->n_; ++i)
            if (get_priority(&ptr_queue->key_[i]) > 
                get_priority(&ptr_queue->key_[max_idx]))
                max_idx = i;
        
        job_t jobx = ptr_queue->key_[max_idx];
        
        // Shift left to fill gap
        for (int i = max_idx; i < ptr_queue->n_ - 1; ++i)
            ptr_queue->key_[i] = ptr_queue->key_[i + 1];
        ptr_queue->n_--;
        return jobx;
    }
    exit(1);
}
```

---

### 2.6.4 Ordered Array (Enqueue O(n), Dequeue O(1))

```c
void enque(queue_t *ptr_queue, job_t *ptr_job) {
    if (ptr_queue->n_ < MAXSIZE) {
        int i = ptr_queue->n_ - 1;
        int pri = get_priority(ptr_job);
        
        // Shift right to make space (insertion sort style)
        while (i >= 0 && get_priority(&ptr_queue->key_[i]) >= pri) {
            ptr_queue->key_[i + 1] = ptr_queue->key_[i];
            --i;
        }
        ptr_queue->key_[i + 1] = *ptr_job;
        ptr_queue->n_++;
    }
}

job_t deque(queue_t *ptr_queue) {
    if (ptr_queue->n_ > 0) {
        return ptr_queue->key_[--ptr_queue->n_];  // Last = highest priority
    }
    exit(1);
}
```

---