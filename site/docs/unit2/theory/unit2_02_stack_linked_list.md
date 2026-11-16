# Unit 2: Stack - Linked List Implementation

## 🔗 Stack - Linked List-Based Implementation

### Structure
```c
struct node {
    int data;
    struct node *next;
};
typedef struct node node_t;

struct stack {
    node_t *top;
};
typedef struct stack stack_t;
```

### Operations
```c
void init_stack(stack_t *s) { s->top = NULL; }

void push(stack_t *s, int val) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->data = val;
    temp->next = s->top;
    s->top = temp;
}

int pop(stack_t *s) {
    if (!s->top) return -1;
    int val = s->top->data;
    node_t *temp = s->top;
    s->top = s->top->next;
    free(temp);
    return val;
}

int is_empty(stack_t *s) { return s->top == NULL; }
int is_full(stack_t *s) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    if (!temp) return 1;
    free(temp);
    return 0;
}
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Linked Stack** | Dynamic size, no fixed limit |
| **Node** | Data + next pointer |
| **Top pointer** | Points to most recent node |
| **malloc** | Every push needs new node |
| **free** | Every pop frees node |

---

*Next: [Stack Applications →](./unit2_03_stack_applications.md)*