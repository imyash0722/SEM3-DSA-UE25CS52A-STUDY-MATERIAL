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