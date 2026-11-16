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