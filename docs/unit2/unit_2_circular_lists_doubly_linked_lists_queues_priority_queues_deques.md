# Unit 2: Circular Lists, Doubly Linked Lists, Queues, Priority Queues, Deques

---

## 2.1 Circular Linked List

### Concept
- Last node points back to first node
- No NULL termination - cycle continues
- Head pointer can point to ANY node in the cycle
- Useful for: Round-robin scheduling, music playlists, token passing

### Structure
```c
struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

struct clist {
    node_t *head_;  // Points to any node in cycle
};
typedef struct clist clist_t;
```

### Operations

#### Initialize
```c
void init_list(clist_t* ptr_clist) {
    ptr_clist->head_ = NULL;
}
```

#### Insert (after head)
```c
void insert(clist_t* ptr_clist, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    
    if (ptr_clist->head_ == NULL) {
        temp->next_ = temp;           // Points to self
        ptr_clist->head_ = temp;
    } else {
        temp->next_ = ptr_clist->head_->next_;
        ptr_clist->head_->next_ = temp;
    }
}
```

#### Display (do-while preferred)
```c
void disp_list(clist_t* ptr_clist) {
    if (ptr_clist->head_ == NULL) {
        printf("List is empty\n");
        return;
    }
    node_t *temp = ptr_clist->head_;
    printf("Circular List: ");
    do {
        printf("%d ", temp->key_);
        temp = temp->next_;
    } while (temp != ptr_clist->head_);
    printf("\n");
}
```

### Josephus Problem
**Problem**: n people in circle, eliminate every k-th person, find survivor.

```c
// josephus.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

int josephus(int n, int k) {
    // Create circular list 1..n
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; ++i) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key_ = i;
        if (!head) {
            head = tail = temp;
        } else {
            tail->next_ = temp;
            tail = temp;
        }
    }
    tail->next_ = head;  // Make circular
    
    node_t *curr = head, *prev = tail;
    while (curr->next_ != curr) {
        // Count k-1 steps
        for (int i = 1; i < k; ++i) {
            prev = curr;
            curr = curr->next_;
        }
        // Eliminate curr
        prev->next_ = curr->next_;
        free(curr);
        curr = prev->next_;
    }
    int survivor = curr->key_;
    free(curr);
    return survivor;
}

int main() {
    printf("Survivor: %d\n", josephus(7, 3));  // Output: 4
    return 0;
}
```

### Circular List Quiz Answers
1. End of traversal: **Check if returned to starting node** (c)
2. `while(temp != NULL)` on circular list: **Infinite loop** (a)
3. Fast/slow pointer on even nodes: **May infinite loop** (c)
4. Single node: `head_ == head_->next_` (c)
5. Delete only node: `head_ becomes NULL` (b)

---

## 2.2 Doubly Linked List

### Concept
- Each node has `prev_` and `next_` pointers
- List has `head_` and `tail_` pointers
- Bidirectional traversal
- Easier insertion/deletion (no trailing pointer needed)

### Structure
```c
struct node {
    int key_;
    struct node *prev_;
    struct node *next_;
};
typedef struct node node_t;

struct DLL {
    node_t *head_;
    node_t *tail_;
};
typedef struct DLL dll_t;
```

### Operations

#### Initialize
```c
void init_dll(dll_t *ptr_dll) {
    ptr_dll->head_ = ptr_dll->tail_ = NULL;
}
```

#### Insert (4 cases)
```c
void insert_dll(dll_t *ptr_dll, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    
    if (!ptr_dll->head_) {  // Empty list
        temp->prev_ = temp->next_ = NULL;
        ptr_dll->head_ = ptr_dll->tail_ = temp;
    }
    // Add at beginning
    else if (key < ptr_dll->head_->key_) {
        temp->prev_ = NULL;
        temp->next_ = ptr_dll->head_;
        ptr_dll->head_->prev_ = temp;
        ptr_dll->head_ = temp;
    }
    // Add at end
    else if (key > ptr_dll->tail_->key_) {
        temp->next_ = NULL;
        temp->prev_ = ptr_dll->tail_;
        ptr_dll->tail_->next_ = temp;
        ptr_dll->tail_ = temp;
    }
    // Add in middle
    else {
        node_t *pres = ptr_dll->head_;
        while (pres->key_ < key) pres = pres->next_;
        temp->next_ = pres;
        temp->prev_ = pres->prev_;
        pres->prev_->next_ = temp;
        pres->prev_ = temp;
    }
}
```

#### Delete (4 cases)
```c
void delete_dll(dll_t *ptr_dll, int key) {
    node_t *pres = ptr_dll->head_;
    while (pres && pres->key_ != key) pres = pres->next_;
    if (!pres) return;  // Not found
    
    if (pres == ptr_dll->head_ && pres == ptr_dll->tail_) {
        // Only node
        ptr_dll->head_ = ptr_dll->tail_ = NULL;
    } else if (pres == ptr_dll->head_) {
        // First node
        ptr_dll->head_ = pres->next_;
        ptr_dll->head_->prev_ = NULL;
    } else if (pres == ptr_dll->tail_) {
        // Last node
        ptr_dll->tail_ = pres->prev_;
        ptr_dll->tail_->next_ = NULL;
    } else {
        // Middle node
        pres->prev_->next_ = pres->next_;
        pres->next_->prev_ = pres->prev_;
    }
    free(pres);
}
```

#### Traversal
```c
// Forward
void disp_forward(dll_t *ptr_dll) {
    node_t *temp = ptr_dll->head_;
    while (temp) {
        printf("%d ", temp->key_);
        temp = temp->next_;
    }
    printf("\n");
}

// Backward
void disp_backward(dll_t *ptr_dll) {
    node_t *temp = ptr_dll->tail_;
    while (temp) {
        printf("%d ", temp->key_);
        temp = temp->prev_;
    }
    printf("\n");
}
```

### Singly vs Doubly Linked List Comparison

| Operation | Singly | Doubly |
|-----------|--------|--------|
| Move Forward | 1 step | 1 step |
| Move Backward | n steps | 1 step |
| Insert Before | n steps (find prev) | 1 step |
| Delete Node | n steps (find prev) | 1 step |
| Search | n steps | n steps |
| Memory | 1 pointer/node | 2 pointers/node |

**Trade-off**: Time-Space trade-off - doubly linked uses more space, gains time.

### Applications
1. **Browser History** - back/forward buttons
2. **Music Player** - previous/next track
3. **Undo/Redo** - bidirectional state changes
4. **LRU Cache** - move accessed items to front
5. **Round Robin Scheduling** - circular doubly linked

---

## 2.3 Queue (Linked List Implementation)

### Queue ADT
- **FIFO** (First In First Out)
- Two ends: **front** (remove), **rear** (insert)

### Interface
```c
void init_queue(queue_t*);
void deinit_queue(queue_t*);
void enque(queue_t*, int key);
int deque(queue_t*);
int is_empty(queue_t*);
int is_full(queue_t*);
```

### Structure (Design 2: front → next → ... → rear)
```c
struct node {
    int key_;
    struct node* next_;
};
typedef struct node node_t;

struct queue {
    node_t* front_;
    node_t* rear_;
};
typedef struct queue queue_t;
```

### Operations

#### Initialize
```c
void init_queue(queue_t *ptr_queue) {
    ptr_queue->front_ = ptr_queue->rear_ = NULL;
}
```

#### Enqueue (add at rear)
```c
void enque(queue_t *ptr_queue, int key) {
    if (!is_full(ptr_queue)) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->key_ = key; temp->next_ = NULL;
        
        if (ptr_queue->rear_ == NULL) {
            // Empty queue - new node is both front and rear
            ptr_queue->front_ = temp;
        } else {
            ptr_queue->rear_->next_ = temp;
        }
        ptr_queue->rear_ = temp;
    }
}
```

#### Dequeue (remove from front)
```c
int deque(queue_t *ptr_queue) {
    if (!is_empty(ptr_queue)) {
        node_t* temp = ptr_queue->front_;
        int key = temp->key_;
        
        ptr_queue->front_ = temp->next_;
        if (ptr_queue->front_ == NULL) {
            // Was only node
            ptr_queue->rear_ = NULL;
        }
        free(temp);
        return key;
    }
    return '\0';
}
```

#### Empty/Full Check
```c
int is_empty(queue_t *ptr_queue) {
    return ptr_queue->front_ == NULL;
}

int is_full(queue_t *ptr_queue) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) return 1;
    free(temp);
    return 0;
}
```

---

## 2.4 Queue (Circular Array Implementation)

### Structure
```c
#define MAXSIZE 5

struct queue {
    int key_[MAXSIZE];
    int front_;  // Index of front element
    int rear_;   // Index of rear element
};
typedef struct queue queue_t;
```

### Key Design Decisions
1. **Modulo arithmetic** for circular wrapping: `i = (i + 1) % MAXSIZE`
2. **Waste one slot** to distinguish empty vs full
3. **Initialize**: `front_ = rear_ = 0`

### Operations

#### Enqueue
```c
void enque(queue_t *ptr_queue, int key) {
    int temp = (ptr_queue->rear_ + 1) % MAXSIZE;
    if (temp != ptr_queue->front_) {  // Not full
        ptr_queue->rear_ = temp;
        ptr_queue->key_[temp] = key;
    } else {
        printf("queue full\n");
    }
}
```

#### Dequeue
```c
int deque(queue_t *ptr_queue) {
    if (ptr_queue->front_ != ptr_queue->rear_) {  // Not empty
        ptr_queue->front_ = (ptr_queue->front_ + 1) % MAXSIZE;
        return ptr_queue->key_[ptr_queue->front_];
    }
    printf("queue empty\n");
    return '\0';
}
```

#### Empty/Full (SAME condition!)
```c
int is_empty(queue_t *ptr_queue) {
    return ptr_queue->front_ == ptr_queue->rear_;  // Before dequeue
}

int is_full(queue_t *ptr_queue) {
    return ptr_queue->front_ == ptr_queue->rear_;  // After enqueue increment
}
```

**Why this works:**
- Empty: front == rear BEFORE any operation
- Full: front == rear AFTER incrementing rear in enqueue
- We waste one array slot to make this distinction

---

## 2.5 Priority Queue

### Concept
- Each element has a **priority**
- Dequeue removes **highest priority** element (not FIFO)
- Higher numeric value = higher priority (or vice versa)

### Interface
```c
void init_queue(queue_t*);
void deinit_queue(queue_t*);
void enque(queue_t*, job_t*);   // job_t has job_no_ and priority_
job_t deque(queue_t*);
int is_empty(queue_t*);
int is_full(queue_t*);
```

### Job Structure
```c
struct job {
    int job_no_;
    int priority_;
};
typedef struct job job_t;

void set_job(job_t*, int job_no, int priority);
void disp_job(job_t*);
int get_priority(job_t*);
```

---

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

## 2.7 Deque (Double-Ended Queue)

### Concept
- Add/remove at **BOTH ends**
- Pronounced "deck"
- Can implement Stack and Queue using Deque

### Interface (using Doubly Linked List)
```c
void init(dll_t*);
void deinit(dll_t*);
void add_in_begin(dll_t*, int key);
void add_at_end(dll_t*, int key);
int remove_in_begin(dll_t*);
int remove_at_end(dll_t*);
int is_empty(dll_t*);
int is_full(dll_t*);
```

### Stack using Deque (Composition)
```c
struct stack {
    dll_t list_;  // Embedded deque
};
typedef struct stack stack_t;

void push(stack_t *ptr_stack, int key) {
    add_in_begin(&ptr_stack->list_, key);
}

int pop(stack_t *ptr_stack) {
    return remove_in_begin(&ptr_stack->list_);
}

int is_empty_stack(stack_t *ptr_stack) {
    return is_empty(&ptr_stack->list_);
}
```

### Queue using Deque
```c
void enqueue(queue_t *ptr_queue, int key) {
    add_at_end(&ptr_queue->list_, key);
}

int dequeue(queue_t *ptr_queue) {
    return remove_in_begin(&ptr_queue->list_);
}
```

---

## 2.8 Round Robin Scheduling (Experiential Learning)

### Task 1: Circular Doubly Linked List
```c
// Modify DLL to be circular
void init_cdll(cdll_t *ptr_cdll) {
    ptr_cdll->head_ = NULL;
}

void add_before_current(cdll_t *ptr_cdll, job_t *job) {
    // Insert before current pointer
    // Adjust prev/next for circular links
}

void remove_current(cdll_t *ptr_cdll) {
    // Remove current node
    // Handle single node case
}
```

### Task 2: Job Structure
```c
struct job {
    int job_no_;
    int priority_;
    int time_for_completion_;
    int time_allotted_;
};
typedef struct job job_t;
```

### Task 3: Scheduling Logic
```c
void process_job(cdll_t *ptr_cdll, int time_slice) {
    job_t *curr = get_current_job(ptr_cdll);
    curr->time_allotted_ += time_slice;
    
    if (curr->time_allotted_ >= curr->time_for_completion_) {
        remove_current(ptr_cdll);
    } else {
        move_to_next(ptr_cdll);  // Round robin
    }
}
```

---

## 2.9 Example Programs

### 2.9.1 Circular List Demo
```c
// circular_demo.c
#include <stdio.h>
#include <stdlib.h>

struct node { int key_; struct node *next_; };
typedef struct node node_t;

struct clist { node_t *head_; };
typedef struct clist clist_t;

void insert(clist_t*, int);
void disp(clist_t*);

int main() {
    clist_t l = {NULL};
    insert(&l, 10); insert(&l, 20); insert(&l, 30);
    disp(&l);  // 30 20 10 (inserts after head)
    return 0;
}
```

### 2.9.2 Doubly Linked List Demo
```c
// dll_demo.c
#include <stdio.h>
#include <stdlib.h>

struct node { int key_; struct node *prev_, *next_; };
typedef struct node node_t;

struct dll { node_t *head_, *tail_; };
typedef struct dll dll_t;

void insert(dll_t*, int);
void disp_forward(dll_t*);
void disp_backward(dll_t*);

int main() {
    dll_t l = {NULL, NULL};
    insert(&l, 30); insert(&l, 10); insert(&l, 20);
    disp_forward(&l);   // 10 20 30
    disp_backward(&l);  // 30 20 10
    return 0;
}
```

### 2.9.3 Queue Linked List Demo
```c
// queue_ll_demo.c
#include <stdio.h>
#include <stdlib.h>

struct node { int key_; struct node *next_; };
typedef struct node node_t;

struct queue { node_t *front_, *rear_; };
typedef struct queue queue_t;

void enque(queue_t*, int);
int deque(queue_t*);

int main() {
    queue_t q = {NULL, NULL};
    enque(&q, 10); enque(&q, 20); enque(&q, 30);
    printf("%d ", deque(&q));  // 10
    printf("%d ", deque(&q));  // 20
    enque(&q, 40);
    printf("%d ", deque(&q));  // 30
    printf("%d\n", deque(&q)); // 40
    return 0;
}
```

### 2.9.4 Priority Queue Demo
```c
// pq_demo.c
#include <stdio.h>
#include <stdlib.h>

struct job { int job_no_, priority_; };
typedef struct job job_t;

// Using ordered list implementation
struct node { job_t jobx_; struct node *next_; };
typedef struct node node_t;

struct pqueue { node_t *front_, *rear_; };
typedef struct pqueue pqueue_t;

void enque(pqueue_t*, job_t*);
job_t deque(pqueue_t*);

int main() {
    pqueue_t q = {NULL, NULL};
    job_t j1 = {1, 5}, j2 = {2, 10}, j3 = {3, 3};
    enque(&q, &j1); enque(&q, &j2); enque(&q, &j3);
    
    // Should come out in priority order: 10, 5, 3
    while (!is_empty(&q)) {
        job_t j = deque(&q);
        printf("Job %d (pri %d)\n", j.job_no_, j.priority_);
    }
    return 0;
}
```

### 2.9.5 Circular Array Queue Demo
```c
// queue_carray_demo.c
#include <stdio.h>

#define MAXSIZE 5
struct queue { int key_[MAXSIZE]; int front_, rear_; };
typedef struct queue queue_t;

void enque(queue_t*, int);
int deque(queue_t*);

int main() {
    queue_t q = {0};  // front=rear=0
    enque(&q, 10); enque(&q, 20); enque(&q, 30);
    printf("%d ", deque(&q));  // 10
    enque(&q, 40); enque(&q, 50); enque(&q, 60);  // Full!
    enque(&q, 70);  // "queue full"
    while (!is_empty(&q)) printf("%d ", deque(&q));
    return 0;
}
```