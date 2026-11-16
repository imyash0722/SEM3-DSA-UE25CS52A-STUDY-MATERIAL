# Unit 1: Stack

## Stack ADT

- **LIFO** (Last In First Out)
- Operations only at **top**
- No traversal concept

**Interface:**
```c
void init(stack_t*);
void deinit(stack_t*);
void push(stack_t*, char ch);
char pop(stack_t*);
char peek(stack_t*);      // View top without removing
int is_empty(stack_t*);
int is_full(stack_t*);
```

## Array Implementation

```c
#define MAXSIZE 5
struct stack {
    char key_[MAXSIZE];
    int top_;  // Index of top element (-1 = empty)
};
typedef struct stack stack_t;

void init_stack(stack_t *ptr_stack) {
    ptr_stack->top_ = -1;
}

void push(stack_t *ptr_stack, char ch) {
    if (!is_full(ptr_stack)) {
        ptr_stack->key_[++ptr_stack->top_] = ch;
    }
}

char pop(stack_t *ptr_stack) {
    if (!is_empty(ptr_stack)) {
        return ptr_stack->key_[ptr_stack->top_--];
    }
}
```

## Linked List Implementation

```c
struct node {
    char key_;
    struct node* next_;
};
typedef struct node node_t;

struct stack {
    node_t* top_;
};
typedef struct stack stack_t;

void init_stack(stack_t *ptr_stack) {
    ptr_stack->top_ = NULL;
}

void push(stack_t *ptr_stack, char ch) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = ch;
    temp->next_ = ptr_stack->top_;
    ptr_stack->top_ = temp;
}

char pop(stack_t *ptr_stack) {
    char ch = ptr_stack->top_->key_;
    node_t* temp = ptr_stack->top_;
    ptr_stack->top_ = ptr_stack->top_->next_;
    free(temp);
    return ch;
}

int is_full(stack_t *ptr_stack) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) return 1;
    free(temp);
    return 0;
}
```

---