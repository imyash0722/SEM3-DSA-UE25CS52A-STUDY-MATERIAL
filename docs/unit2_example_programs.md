# Unit 2: Detailed Example Programs

## 2.1 Circular Linked List

### 2.1.1 Basic Circular List
```c
// circular_basic.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

struct clist {
    node_t *head_;
};
typedef struct clist clist_t;

void init_clist(clist_t *ptr_clist) {
    ptr_clist->head_ = NULL;
}

void insert_clist(clist_t *ptr_clist, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    
    if (ptr_clist->head_ == NULL) {
        temp->next_ = temp;  // Point to self
        ptr_clist->head_ = temp;
    } else {
        temp->next_ = ptr_clist->head_->next_;
        ptr_clist->head_->next_ = temp;
    }
}

void disp_clist(clist_t *ptr_clist) {
    if (!ptr_clist->head_) {
        printf("Empty\n"); return;
    }
    node_t *temp = ptr_clist->head_;
    printf("Circular: ");
    do {
        printf("%d ", temp->key_);
        temp = temp->next_;
    } while (temp != ptr_clist->head_);
    printf("\n");
}

int main() {
    clist_t l; init_clist(&l);
    insert_clist(&l, 10); insert_clist(&l, 20); insert_clist(&l, 30);
    disp_clist(&l);  // 30 20 10 (each insert after head)
    return 0;
}
```

### 2.1.2 Josephus Problem
```c
// josephus.c
#include <stdio.h>
#include <stdlib.h>

struct node { int key_; struct node *next_; };
typedef struct node node_t;

int josephus(int n, int k) {
    // Create circular list 1..n
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; ++i) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key_ = i;
        if (!head) head = tail = temp;
        else { tail->next_ = temp; tail = temp; }
    }
    tail->next_ = head;  // Make circular
    
    node_t *curr = head, *prev = tail;
    while (curr->next_ != curr) {
        // Count k-1 steps
        for (int i = 1; i < k; ++i) {
            prev = curr;
            curr = curr->next_;
        }
        // Eliminate
        prev->next_ = curr->next_;
        free(curr);
        curr = prev->next_;
    }
    int survivor = curr->key_;
    free(curr);
    return survivor;
}

int main() {
    printf("n=7, k=3: Survivor = %d\n", josephus(7, 3));  // 4
    printf("n=5, k=2: Survivor = %d\n", josephus(5, 2));  // 3
    return 0;
}
```

---

## 2.2 Doubly Linked List

### 2.2.1 Complete Implementation
```c
// dll_complete.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_;
    struct node *prev_, *next_;
};
typedef struct node node_t;

struct dll {
    node_t *head_, *tail_;
};
typedef struct dll dll_t;

void init_dll(dll_t *ptr_dll) {
    ptr_dll->head_ = ptr_dll->tail_ = NULL;
}

void insert_dll(dll_t *ptr_dll, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    
    if (!ptr_dll->head_) {  // Empty
        temp->prev_ = temp->next_ = NULL;
        ptr_dll->head_ = ptr_dll->tail_ = temp;
    }
    else if (key <= ptr_dll->head_->key_) {  // At front
        temp->prev_ = NULL;
        temp->next_ = ptr_dll->head_;
        ptr_dll->head_->prev_ = temp;
        ptr_dll->head_ = temp;
    }
    else if (key >= ptr_dll->tail_->key_) {  // At end
        temp->next_ = NULL;
        temp->prev_ = ptr_dll->tail_;
        ptr_dll->tail_->next_ = temp;
        ptr_dll->tail_ = temp;
    }
    else {  // In middle
        node_t *pres = ptr_dll->head_;
        while (pres->key_ < key) pres = pres->next_;
        temp->next_ = pres;
        temp->prev_ = pres->prev_;
        pres->prev_->next_ = temp;
        pres->prev_ = temp;
    }
}

void delete_dll(dll_t *ptr_dll, int key) {
    node_t *pres = ptr_dll->head_;
    while (pres && pres->key_ != key) pres = pres->next_;
    if (!pres) return;
    
    if (pres == ptr_dll->head_ && pres == ptr_dll->tail_) {
        ptr_dll->head_ = ptr_dll->tail_ = NULL;
    } else if (pres == ptr_dll->head_) {
        ptr_dll->head_ = pres->next_;
        ptr_dll->head_->prev_ = NULL;
    } else if (pres == ptr_dll->tail_) {
        ptr_dll->tail_ = pres->prev_;
        ptr_dll->tail_->next_ = NULL;
    } else {
        pres->prev_->next_ = pres->next_;
        pres->next_->prev_ = pres->prev_;
    }
    free(pres);
}

void disp_forward(dll_t *ptr_dll) {
    printf("Forward: ");
    for (node_t *t = ptr_dll->head_; t; t = t->next_) printf("%d ", t->key_);
    printf("\n");
}

void disp_backward(dll_t *ptr_dll) {
    printf("Backward: ");
    for (node_t *t = ptr_dll->tail_; t; t = t->prev_) printf("%d ", t->key_);
    printf("\n");
}

int main() {
    dll_t l; init_dll(&l);
    insert_dll(&l, 30); insert_dll(&l, 10); insert_dll(&l, 20);
    insert_dll(&l, 40); insert_dll(&l, 5);
    disp_forward(&l);   // 5 10 20 30 40
    disp_backward(&l);  // 40 30 20 10 5
    
    delete_dll(&l, 20);
    disp_forward(&l);   // 5 10 30 40
    return 0;
}
```

### 2.2.2 Browser History Simulation
```c
// browser_history.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct page {
    char url[100];
    struct page *prev_, *next_;
};
typedef struct page page_t;

struct history {
    page_t *current_;
};
typedef struct history history_t;

void visit(history_t *h, const char *url) {
    page_t *p = (page_t*)malloc(sizeof(page_t));
    strcpy(p->url, url);
    p->prev_ = h->current_;
    p->next_ = NULL;
    if (h->current_) h->current_->next_ = p;
    h->current_ = p;
}

void back(history_t *h) {
    if (h->current_ && h->current_->prev_) h->current_ = h->current_->prev_;
}

void forward(history_t *h) {
    if (h->current_ && h->current_->next_) h->current_ = h->current_->next_;
}

int main() {
    history_t h = {NULL};
    visit(&h, "google.com");
    visit(&h, "github.com");
    visit(&h, "stackoverflow.com");
    printf("Current: %s\n", h.current_->url);  // stackoverflow.com
    back(&h);
    printf("Back: %s\n", h.current_->url);    // github.com
    back(&h);
    printf("Back: %s\n", h.current_->url);    // google.com
    forward(&h);
    printf("Forward: %s\n", h.current_->url); // github.com
    return 0;
}
```

---

## 2.3 Queue Implementations

### 2.3.1 Linked List Queue
```c
// queue_ll.c
#include <stdio.h>
#include <stdlib.h>

struct node { int key_; struct node *next_; };
typedef struct node node_t;

struct queue { node_t *front_, *rear_; };
typedef struct queue queue_t;

void init_queue(queue_t *q) { q->front_ = q->rear_ = NULL; }

int is_empty(queue_t *q) { return q->front_ == NULL; }

int is_full(queue_t *q) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    if (!t) return 1; free(t); return 0;
}

void enque(queue_t *q, int key) {
    if (!is_full(q)) {
        node_t *t = (node_t*)malloc(sizeof(node_t));
        t->key_ = key; t->next_ = NULL;
        if (!q->rear_) q->front_ = t;
        else q->rear_->next_ = t;
        q->rear_ = t;
    }
}

int deque(queue_t *q) {
    if (!is_empty(q)) {
        node_t *t = q->front_;
        int k = t->key_;
        q->front_ = t->next_;
        if (!q->front_) q->rear_ = NULL;
        free(t); return k;
    }
    return -1;
}

int main() {
    queue_t q; init_queue(&q);
    enque(&q, 10); enque(&q, 20); enque(&q, 30);
    printf("%d ", deque(&q));  // 10
    enque(&q, 40);
    while (!is_empty(&q)) printf("%d ", deque(&q));  // 20 30 40
    return 0;
}
```

### 2.3.2 Circular Array Queue
```c
// queue_carray.c
#include <stdio.h>
#define MAXSIZE 5

struct queue {
    int key_[MAXSIZE];
    int front_, rear_;  // Both start at 0
};
typedef struct queue queue_t;

void init_queue(queue_t *q) { q->front_ = q->rear_ = 0; }

int is_empty(queue_t *q) { return q->front_ == q->rear_; }

int is_full(queue_t *q) { return (q->rear_ + 1) % MAXSIZE == q->front_; }

void enque(queue_t *q, int key) {
    if (!is_full(q)) {
        q->rear_ = (q->rear_ + 1) % MAXSIZE;
        q->key_[q->rear_] = key;
    } else printf("Full\n");
}

int deque(queue_t *q) {
    if (!is_empty(q)) {
        q->front_ = (q->front_ + 1) % MAXSIZE;
        return q->key_[q->front_];
    }
    return -1;
}

int main() {
    queue_t q; init_queue(&q);
    enque(&q, 10); enque(&q, 20); enque(&q, 30);
    printf("%d ", deque(&q));  // 10
    enque(&q, 40); enque(&q, 50);  // Full now (wasted 1 slot)
    enque(&q, 60);  // "Full"
    while (!is_empty(&q)) printf("%d ", deque(&q));  // 20 30 40 50
    return 0;
}
```

---

## 2.4 Priority Queue Implementations

### 2.4.1 Unordered List (Enqueue O(1), Dequeue O(n))
```c
// pq_unordered_list.c
#include <stdio.h>
#include <stdlib.h>

struct job { int job_no_, priority_; };
typedef struct job job_t;

struct node { job_t jobx_; struct node *next_; };
typedef struct node node_t;

struct pqueue { node_t *front_, *rear_; };
typedef struct pqueue pqueue_t;

void init_pq(pqueue_t *q) { q->front_ = q->rear_ = NULL; }

int is_empty(pqueue_t *q) { return q->front_ == NULL; }

int is_full(pqueue_t *q) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    if (!t) return 1; free(t); return 0;
}

void enque(pqueue_t *q, job_t *j) {
    if (!is_full(q)) {
        node_t *t = (node_t*)malloc(sizeof(node_t));
        t->jobx_ = *j; t->next_ = NULL;
        if (!q->rear_) q->front_ = t;
        else q->rear_->next_ = t;
        q->rear_ = t;
    }
}

job_t deque(pqueue_t *q) {
    if (is_empty(q)) exit(1);
    node_t *prev = NULL, *pres = q->front_;
    int max_pri = pres->jobx_.priority_;
    node_t *max_prev = NULL, *max_pres = pres;
    
    while (pres) {
        if (pres->jobx_.priority_ > max_pri) {
            max_pri = pres->jobx_.priority_;
            max_prev = prev; max_pres = pres;
        }
        prev = pres; pres = pres->next_;
    }
    
    job_t j = max_pres->jobx_;
    if (!max_prev) {
        q->front_ = max_pres->next_;
        if (!q->front_) q->rear_ = NULL;
    } else {
        max_prev->next_ = max_pres->next_;
        if (!max_pres->next_) q->rear_ = max_prev;
    }
    free(max_pres); return j;
}

int main() {
    pqueue_t q; init_pq(&q);
    job_t j1 = {1, 5}, j2 = {2, 10}, j3 = {3, 3}, j4 = {4, 10};
    enque(&q, &j1); enque(&q, &j2); enque(&q, &j3); enque(&q, &j4);
    
    // Should output in priority order (FIFO for same priority)
    while (!is_empty(&q)) {
        job_t j = deque(&q);
        printf("Job %d (pri %d)\n", j.job_no_, j.priority_);
    }
    return 0;
}
```

### 2.4.2 Ordered Array (Enqueue O(n), Dequeue O(1))
```c
// pq_ordered_array.c
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

struct job { int job_no_, priority_; };
typedef struct job job_t;

struct pqueue { job_t key_[MAXSIZE]; int n_; };
typedef struct pqueue pqueue_t;

void init_pq(pqueue_t *q) { q->n_ = 0; }

int is_empty(pqueue_t *q) { return q->n_ == 0; }
int is_full(pqueue_t *q) { return q->n_ == MAXSIZE; }

void enque(pqueue_t *q, job_t *j) {
    if (!is_full(q)) {
        int i = q->n_ - 1;
        int pri = j->priority_;
        while (i >= 0 && q->key_[i].priority_ >= pri) {
            q->key_[i+1] = q->key_[i];
            --i;
        }
        q->key_[i+1] = *j;
        q->n_++;
    }
}

job_t deque(pqueue_t *q) {
    if (!is_empty(q)) return q->key_[--q->n_];
    exit(1);
}

int main() {
    pqueue_t q; init_pq(&q);
    job_t j1 = {1, 5}, j2 = {2, 10}, j3 = {3, 3};
    enque(&q, &j1); enque(&q, &j2); enque(&q, &j3);
    while (!is_empty(&q)) {
        job_t j = deque(&q);
        printf("Job %d (pri %d)\n", j.job_no_, j.priority_);
    }
    return 0;
}
```

---

## 2.5 Deque (Double-Ended Queue)

### 2.5.1 Deque with Doubly Linked List
```c
// deque_dll.c
#include <stdio.h>
#include <stdlib.h>

struct node { int key_; struct node *prev_, *next_; };
typedef struct node node_t;

struct deque { node_t *head_, *tail_; };
typedef struct deque deque_t;

void init_deque(deque_t *d) { d->head_ = d->tail_ = NULL; }
int is_empty(deque_t *d) { return d->head_ == NULL; }

void add_front(deque_t *d, int key) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    t->key_ = key; t->prev_ = NULL; t->next_ = d->head_;
    if (!d->head_) d->tail_ = t;
    else d->head_->prev_ = t;
    d->head_ = t;
}

void add_rear(deque_t *d, int key) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    t->key_ = key; t->next_ = NULL; t->prev_ = d->tail_;
    if (!d->tail_) d->head_ = t;
    else d->tail_->next_ = t;
    d->tail_ = t;
}

int remove_front(deque_t *d) {
    if (is_empty(d)) return -1;
    node_t *t = d->head_; int k = t->key_;
    d->head_ = t->next_;
    if (d->head_) d->head_->prev_ = NULL;
    else d->tail_ = NULL;
    free(t); return k;
}

int remove_rear(deque_t *d) {
    if (is_empty(d)) return -1;
    node_t *t = d->tail_; int k = t->key_;
    d->tail_ = t->prev_;
    if (d->tail_) d->tail_->next_ = NULL;
    else d->head_ = NULL;
    free(t); return k;
}

int main() {
    deque_t d; init_deque(&d);
    add_front(&d, 10); add_rear(&d, 20); add_front(&d, 5);
    printf("%d ", remove_front(&d));  // 5
    printf("%d ", remove_rear(&d));   // 20
    printf("%d\n", remove_front(&d)); // 10
    return 0;
}
```

### 2.5.2 Stack and Queue using Deque
```c
// stack_queue_from_deque.c
#include <stdio.h>
#include "deque_dll.c"  // Include deque implementation

// Stack using Deque
struct stack { deque_t d_; };
typedef struct stack stack_t;

void push(stack_t *s, int key) { add_front(&s->d_, key); }
int pop(stack_t *s) { return remove_front(&s->d_); }
int is_empty_stack(stack_t *s) { return is_empty(&s->d_); }

// Queue using Deque
struct queue { deque_t d_; };
typedef struct queue queue_t;

void enqueue(queue_t *q, int key) { add_rear(&q->d_, key); }
int dequeue(queue_t *q) { return remove_front(&q->d_); }
int is_empty_queue(queue_t *q) { return is_empty(&q->d_); }

int main() {
    // Stack test
    stack_t s = {{0}};
    push(&s, 1); push(&s, 2); push(&s, 3);
    while (!is_empty_stack(&s)) printf("%d ", pop(&s));  // 3 2 1
    
    // Queue test
    queue_t q = {{0}};
    enqueue(&q, 1); enqueue(&q, 2); enqueue(&q, 3);
    while (!is_empty_queue(&q)) printf("%d ", dequeue(&q));  // 1 2 3
    return 0;
}
```

---

## 2.6 Round Robin Scheduling

### 2.6.1 Circular Doubly Linked List with Jobs
```c
// round_robin.c
#include <stdio.h>
#include <stdlib.h>

struct job {
    int job_no_;
    int time_needed_;
    int time_got_;
};
typedef struct job job_t;

struct node {
    job_t job_;
    struct node *prev_, *next_;
};
typedef struct node node_t;

struct scheduler {
    node_t *current_;
    int time_slice_;
};
typedef struct scheduler scheduler_t;

void add_job(scheduler_t *s, job_t j) {
    node_t *t = (node_t*)malloc(sizeof(node_t));
    t->job_ = j;
    if (!s->current_) {
        t->prev_ = t->next_ = t;
        s->current_ = t;
    } else {
        t->next_ = s->current_;
        t->prev_ = s->current_->prev_;
        s->current_->prev_->next_ = t;
        s->current_->prev_ = t;
    }
}

void run_scheduler(scheduler_t *s) {
    while (s->current_) {
        node_t *curr = s->current_;
        printf("Running Job %d (need %d, got %d)\n", 
               curr->job_.job_no_, curr->job_.time_needed_, curr->job_.time_got_);
        
        curr->job_.time_got_ += s->time_slice_;
        
        if (curr->job_.time_got_ >= curr->job_.time_needed_) {
            printf("  Job %d COMPLETE\n", curr->job_.job_no_);
            if (curr->next_ == curr) {  // Only job
                free(curr); s->current_ = NULL;
            } else {
                curr->prev_->next_ = curr->next_;
                curr->next_->prev_ = curr->prev_;
                s->current_ = curr->next_;
                free(curr);
            }
        } else {
            s->current_ = curr->next_;  // Next job
        }
    }
}

int main() {
    scheduler_t s = {NULL, 3};
    add_job(&s, (job_t){1, 10, 0});
    add_job(&s, (job_t){2, 5, 0});
    add_job(&s, (job_t){3, 8, 0});
    run_scheduler(&s);
    return 0;
}
```