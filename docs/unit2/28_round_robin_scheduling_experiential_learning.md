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