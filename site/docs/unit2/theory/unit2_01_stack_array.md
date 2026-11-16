# Unit 2: Stack - Array Implementation

## 📚 Stack - Array-Based Implementation

### What is a Stack?

> **Stack** is a linear data structure that follows **LIFO (Last In First Out)** principle.
> - Insertion: **Push** (at top)
> - Deletion: **Pop** (from top)
> - View top: **Peek/Top**

### Real-World Analogy
- Stack of plates in a cafeteria
- Stack of books on a desk
- Browser back button (history stack)
- Function call stack (recursion)

### Stack ADT Interface
```c
void init_stack(stack_t *s);      // Initialize empty stack
void deinit_stack(stack_t *s);    // Clean up
void push(stack_t *s, int val);   // Insert at top
int pop(stack_t *s);              // Remove from top
int peek(stack_t *s);             // View top without removing
int is_empty(stack_t *s);         // Check if empty
int is_full(stack_t *s);          // Check if full (bounded)
```

---

## 🔧 Stack Implementation 1: Array-Based

### Structure
```c
#define MAXSIZE 5

struct stack {
    int data[MAXSIZE];
    int top;        // Index of top element (-1 = empty)
};
typedef struct stack stack_t;
```

### Operations

#### Initialize
```c
void init_stack(stack_t *s) {
    s->top = -1;  // -1 means empty
}
```

#### Push
```c
void push(stack_t *s, int val) {
    if (is_full(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = val;  // Increment first, then store
}
```

#### Pop
```c
int pop(stack_t *s) {
    if (is_empty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];  // Return value, then decrement
}
```

#### Peek
```c
int peek(stack_t *s) {
    if (is_empty(s)) return -1;
    return s->data[s->top];
}
```

#### Empty/Full Check
```c
int is_empty(stack_t *s) { return s->top == -1; }
int is_full(stack_t *s) { return s->top == MAXSIZE - 1; }
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Stack** | LIFO, Push/Pop at top |
| **Array Stack** | Fixed size, O(1) operations |
| **top = -1** | Empty indicator |
| **top = MAXSIZE-1** | Full indicator |
| **++top** | Pre-increment for push |
| **top--** | Post-decrement for pop |

---

## 🧪 Self-Test Questions

1. Why do we use `++s->top` (pre-increment) in push?
2. What happens if we pop from an empty stack?
3. What is the time complexity of push/pop in array stack?
4. Why do we waste one slot in some implementations?

---

*Next: [Stack - Linked List Implementation →](./unit2_02_stack_linked_list.md)*