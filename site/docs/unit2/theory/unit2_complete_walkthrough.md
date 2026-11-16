# Unit 2: Stacks, Queues, Priority Queues & Advanced Lists

## 📚 Unit Overview

**Topics Covered:**
1. Stack (Array & Linked List Implementation)
2. Stack Applications (Recursion, Expression Evaluation, Infix→Postfix, Parentheses Matching)
3. Queue (Linked List & Circular Array Implementation)
4. Circular Queue
5. Priority Queue (5 Implementations)
6. Deque (Double-Ended Queue)
7. Josephus Problem (Circular List Application)
8. Round Robin Scheduling (Experiential Learning)

---

## 📚 Stack - Complete Walkthrough

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

## 🔗 Stack Implementation 2: Linked List-Based

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

## 🎯 Stack Applications - Deep Dive

### Application 1: Parentheses Matching

**Problem:** Check if parentheses in expression are balanced.

**Algorithm:**
```
For each character in string:
    If '(', '[', '{' → push to stack
    If ')', ']', '}' → 
        If stack empty → NOT balanced
        Pop and check if matching pair
After loop: if stack empty → balanced, else NOT balanced
```

**Matching Pairs:**
- `(` matches `)`
- `[` matches `]`
- `{` matches `}`

```c
int is_balanced(char *expr) {
    stack_t s; init_stack(&s);
    
    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{')
            push(&s, ch);
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (is_empty(&s)) return 0;
            char top = pop(&s);
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{'))
                return 0;
        }
    }
    return is_empty(&s);
}
```

**Example Traces:**
```
Input: "({[]})"     → BALANCED
Stack: ( → { → [ → pop[ matches ] → pop{ matches } → pop( matches ) → empty ✓

Input: "({[)]}"     → NOT BALANCED
Stack: ( → { → [ → pop[ but got ) → MISMATCH ✗
```

---

### Application 2: Infix to Postfix Conversion

**Definitions:**
- **Infix:** Operator between operands (A + B)
- **Postfix:** Operator after operands (A B +)
- **Prefix:** Operator before operands (+ A B)

**Why Postfix?** No parentheses needed, easy to evaluate with stack!

**Precedence Table:**
| Operator | Precedence |
|----------|------------|
| `^`      | 3 (highest)|
| `* / %`  | 2          |
| `+ -`    | 1          |

**Algorithm (Shunting Yard):**
```
For each token in infix:
    If operand → output
    If '(' → push to stack
    If ')' → pop and output until '('
    If operator:
        While stack not empty AND 
              precedence(top) >= precedence(current) AND top != '(':
            pop and output
        push current operator
After loop: pop remaining operators to output
```

```c
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infix_to_postfix(char *infix, char *postfix) {
    stack_t s; init_stack(&s);
    int j = 0;
    
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        
        if (isalnum(ch)) {
            postfix[j++] = ch;  // Operand goes to output
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!is_empty(&s) && peek(&s) != '(')
                postfix[j++] = pop(&s);
            pop(&s);  // Remove '('
        } else {  // Operator
            while (!is_empty(&s) && precedence(peek(&s)) >= precedence(ch))
                postfix[j++] = pop(&s);
            push(&s, ch);
        }
    }
    while (!is_empty(&s)) postfix[j++] = pop(&s);
    postfix[j] = '\0';
}
```

**Trace Example:**
```
Infix:  A + B * C
Step 1: A          → output: A
Step 2: +          → push +
Step 3: B          → output: AB
Step 4: *          → push * (higher precedence than +)
Step 5: C          → output: ABC
End:   pop * → output: ABC*  pop + → output: ABC*+

Postfix: ABC*+
```

---

### Application 3: Postfix Expression Evaluation

**Algorithm:**
```
For each token in postfix:
    If operand → push to stack
    If operator:
        pop operand2 (right)
        pop operand1 (left)
        result = operand1 operator operand2
        push result
Final result = pop stack
```

```c
int evaluate_postfix(char *postfix) {
    stack_t s; init_stack(&s);
    
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            push(&s, ch - '0');  // Convert char to int
        } else {
            int b = pop(&s);  // Right operand
            int a = pop(&s);  // Left operand
            int result;
            switch(ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}
```

**Trace Example:**
```
Postfix:  3 4 + 5 *
Step 1: 3 → push 3      Stack: [3]
Step 2: 4 → push 4      Stack: [3, 4]
Step 3: + → pop 4, pop 3 → 3+4=7 → push 7   Stack: [7]
Step 4: 5 → push 5      Stack: [7, 5]
Step 5: * → pop 5, pop 7 → 7*5=35 → push 35  Stack: [35]
Result: 35
```

---

## 📋 Queue - Complete Walkthrough

### What is a Queue?

> **Queue** is a linear data structure following **FIFO (First In First Out)**.
> - Insert at **rear** (enqueue)
> - Remove from **front** (dequeue)

### Real-World Examples
- Printer queue
- CPU process scheduling
- Ticket counter line
- Breadth-First Search (BFS)

---

## 🔗 Queue Implementation 1: Linked List

### Structure
```c
struct node {
    int data;
    struct node *next;
};
typedef struct node node_t;

struct queue {
    node_t *front;  // First element
    node_t *rear;   // Last element
};
typedef struct queue queue_t;
```

### Operations

#### Enqueue (Insert at Rear)
```c
void enqueue(queue_t *q, int val) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->data = val;
    temp->next = NULL;
    
    if (q->rear == NULL) {
        // Empty queue - new node is both front and rear
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}
```

#### Dequeue (Remove from Front)
```c
int dequeue(queue_t *q) {
    if (q->front == NULL) return -1;  // Empty
    
    node_t *temp = q->front;
    int val = temp->data;
    
    q->front = temp->next;
    if (q->front == NULL)  // Was last element
        q->rear = NULL;
    
    free(temp);
    return val;
}
```

---

## 🔄 Circular Array Queue

### Why Circular Array?
- Array is fixed size
- Simple indices: front=0, rear=0 initially
- Use modulo arithmetic to wrap around
- **Waste ONE slot** to distinguish full vs empty

### Structure
```c
#define MAXSIZE 5

struct queue {
    int data[MAXSIZE];
    int front;  // Index of front element
    int rear;   // Index of rear element
};
typedef struct queue queue_t;
```

### Key Concept: Modulo Arithmetic
```
Index = (Index + 1) % MAXSIZE
```

**Visual:**
```
Array size 5: [ ][ ][ ][ ][ ]
                ↑
              front=rear=0 (empty)

Enqueue 10:  rear = (0+1)%5 = 1, data[1]=10
    [ ][10][ ][ ][ ]
           ↑   ↑
          f=0  r=1

Enqueue 20:  rear = (1+1)%5 = 2, data[2]=20
    [ ][10][20][ ][ ]
           ↑     ↑
          f=0   r=2

... continue until r=4
    [50][10][20][30][40]
     ↑            ↑
    f=0          r=4

Enqueue 50: rear = (4+1)%5 = 0
    rear == front? → FULL! (wasted one slot)
```

### Operations

```c
void init_queue(queue_t *q) {
    q->front = q->rear = 0;
}

int is_empty(queue_t *q) {
    return q->front == q->rear;
}

int is_full(queue_t *q) {
    return (q->rear + 1) % MAXSIZE == q->front;
}

void enqueue(queue_t *q, int val) {
    if (is_full(q)) { printf("Queue full\n"); return; }
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = val;
}

int dequeue(queue_t *q) {
    if (is_empty(q)) return -1;
    q->front = (q->front + 1) % MAXSIZE;
    return q->data[q->front];
}
```

---

## 🎯 Priority Queue - Complete Walkthrough

### What is a Priority Queue?

> **Priority Queue** is a queue where each element has a **priority**.
> - Dequeue removes **highest priority** element (not FIFO)
> - Higher numeric value = higher priority (typically)

### Real-World Examples
- Hospital ER: Critical patients first
- CPU scheduling: Real-time processes first
- Network packets: QoS priority
- Dijkstra's algorithm

### Priority Queue ADT
```c
struct job {
    int job_no;
    int priority;
};
typedef struct job job_t;

void init_pq(pqueue_t *q);
void enqueue(pqueue_t *q, job_t *job);
job_t dequeue(pqueue_t *q);  // Returns highest priority job
```

---

## 🎯 Priority Queue: 5 Implementations Compared

| Implementation | Enqueue | Dequeue | Space |
|----------------|---------|---------|-------|
| **Unordered List** | O(1) - add at rear | O(n) - search max | O(n) |
| **Ordered List** | O(n) - find position | O(1) - remove front | O(n) |
| **Unordered Array** | O(1) - add at end | O(n) - search + shift | O(n) |
| **Ordered Array** | O(n) - find + shift | O(1) - remove end | O(n) |
| **Heap (Tree)** | O(log n) | O(log n) | O(n) |

---

### Implementation 1: Unordered Linked List

**Enqueue:** O(1) - Add at rear
**Dequeue:** O(n) - Traverse to find max priority

```c
job_t dequeue(pqueue_t *q) {
    // Find max priority node
    node_t *max_prev = NULL, *max_curr = q->front;
    node_t *prev = NULL, *curr = q->front;
    int max_pri = curr->job.priority;
    
    while (curr) {
        if (curr->job.priority > max_pri) {
            max_pri = curr->job.priority;
            max_prev = prev;
            max_curr = curr;
        }
        prev = curr;
        curr = curr->next;
    }
    
    // Remove max_curr
    job_t job = max_curr->job;
    if (max_prev == NULL)  // Was first node
        q->front = max_curr->next;
    else
        max_prev->next = max_curr->next;
    
    free(max_curr);
    return job;
}
```

---

### Implementation 2: Ordered Linked List

**Enqueue:** O(n) - Find correct position by priority
**Dequeue:** O(1) - Remove from front

```c
void enqueue(pqueue_t *q, job_t *job) {
    node_t *temp = create_node(job);
    
    // Insert in descending priority order
    if (!q->front || q->front->job.priority <= job->priority) {
        // Insert at front
        temp->next = q->front;
        q->front = temp;
        if (!q->rear) q->rear = temp;
    } else {
        // Find position
        node_t *curr = q->front;
        while (curr->next && curr->next->job.priority > job->priority)
            curr = curr->next;
        temp->next = curr->next;
        curr->next = temp;
        if (!temp->next) q->rear = temp;
    }
}

job_t dequeue(pqueue_t *q) {
    job_t job = q->front->job;
    node_t *temp = q->front;
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return job;
}
```

---

### Implementation 3: Unordered Array

```c
#define MAXSIZE 100

struct pqueue {
    job_t jobs[MAXSIZE];
    int count;
};

void enqueue(pqueue_t *q, job_t *job) {
    if (q->count < MAXSIZE)
        q->jobs[q->count++] = *job;
}

job_t dequeue(pqueue_t *q) {
    int max_idx = 0;
    for (int i = 1; i < q->count; i++)
        if (q->jobs[i].priority > q->jobs[max_idx].priority)
            max_idx = i;
    
    job_t job = q->jobs[max_idx];
    // Shift left
    for (int i = max_idx; i < q->count - 1; i++)
        q->jobs[i] = q->jobs[i + 1];
    q->count--;
    return job;
}
```

---

### Implementation 4: Ordered Array

```c
void enqueue(pqueue_t *q, job_t *job) {
    int i = q->count - 1;
    while (i >= 0 && q->jobs[i].priority >= job->priority) {
        q->jobs[i + 1] = q->jobs[i];
        i--;
    }
    q->jobs[i + 1] = *job;
    q->count++;
}

job_t dequeue(pqueue_t *q) {
    return q->jobs[--q->count];  // Last element = highest priority
}
```

---

## 🔀 Deque (Double-Ended Queue)

### What is a Deque?
- Insert/Delete at **BOTH** ends
- Can implement both Stack and Queue!

### Operations
```c
void add_front(deque_t *d, int val);
void add_rear(deque_t *d, int val);
int remove_front(deque_t *d);
int remove_rear(deque_t *d);
```

### Stack using Deque
```c
void push(stack_t *s, int val) { add_front(&s->deque, val); }
int pop(stack_t *s) { return remove_front(&s->deque); }
```

### Queue using Deque
```c
void enqueue(queue_t *q, int val) { add_rear(&q->deque, val); }
int dequeue(queue_t *q) { return remove_front(&q->deque); }
```

---

## 🎯 Anchor Programs for Unit 2

### Program 1: Stack Applications Demo
```c
// stack_apps_demo.c - All Stack Applications
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100

typedef struct {
    int data[MAXSIZE];
    int top;
} Stack;

void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
int isFull(Stack *s) { return s->top == MAXSIZE - 1; }

void push(Stack *s, int val) {
    if (isFull(s)) return;
    s->data[++s->top] = val;
}

int pop(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->data[s->top--];
}

int peek(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->data[s->top];
}

// 1. Parentheses Matching
int isBalanced(char *expr) {
    Stack s; init(&s);
    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') push(&s, ch);
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (isEmpty(&s)) return 0;
            char top = pop(&s);
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{')) return 0;
        }
    }
    return isEmpty(&s);
}

// 2. Infix to Postfix
int prec(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack s; init(&s);
    int j = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        if (isalnum(ch)) postfix[j++] = ch;
        else if (ch == '(') push(&s, ch);
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(')
                postfix[j++] = pop(&s);
            pop(&s);  // Remove '('
        } else {
            while (!isEmpty(&s) && prec(peek(&s)) >= prec(ch))
                postfix[j++] = pop(&s);
            push(&s, ch);
        }
    }
    while (!isEmpty(&s)) postfix[j++] = pop(&s);
    postfix[j] = '\0';
}

// 3. Postfix Evaluation
int evalPostfix(char *postfix) {
    Stack s; init(&s);
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) push(&s, ch - '0');
        else {
            int b = pop(&s);
            int a = pop(&s);
            switch(ch) {
                case '+': push(&s, a + b); break;
                case '-': push(&s, a - b); break;
                case '*': push(&s, a * b); break;
                case '/': push(&s, a / b); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    printf("=== Stack Applications Demo ===\n\n");
    
    // 1. Parentheses
    char *expr1 = "({[]})";
    char *expr2 = "({[)]}";
    printf("1. Parentheses Matching:\n");
    printf("  %s → %s\n", expr1, isBalanced(expr1) ? "BALANCED" : "NOT BALANCED");
    printf("  %s → %s\n", expr2, isBalanced(expr2) ? "BALANCED" : "NOT BALANCED");
    
    // 2. Infix to Postfix
    char infix[] = "A+B*C";
    char postfix[100];
    infixToPostfix(infix, postfix);
    printf("\n2. Infix to Postfix:\n");
    printf("  Infix: %s\n", infix);
    printf("  Postfix: %s\n", postfix);
    
    // 3. Postfix Evaluation
    char *post = "34+5*";
    int result = evalPostfix(post);
    printf("\n3. Postfix Evaluation:\n");
    printf("  Postfix: %s\n", post);
    printf("  Result: %d\n", result);
    
    return 0;
}
```

### Program 2: Queue Implementations
```c
// queue_demo.c - All Queue Implementations
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5

// ===== 1. Linked List Queue =====
typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *front, *rear;
} LLQueue;

void ll_init(LLQueue *q) { q->front = q->rear = NULL; }

void ll_enqueue(LLQueue *q, int val) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = val; temp->next = NULL;
    if (!q->rear) q->front = q->rear = temp;
    else { q->rear->next = temp; q->rear = temp; }
}

int ll_dequeue(LLQueue *q) {
    if (!q->front) return -1;
    Node *temp = q->front;
    int val = temp->data;
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return val;
}

// ===== 2. Circular Array Queue =====
typedef struct {
    int data[MAXSIZE];
    int front, rear;
} CAQueue;

void ca_init(CAQueue *q) { q->front = q->rear = 0; }
int ca_empty(CAQueue *q) { return q->front == q->rear; }
int ca_full(CAQueue *q) { return (q->rear + 1) % MAXSIZE == q->front; }

void ca_enqueue(CAQueue *q, int val) {
    if (ca_full(q)) { printf("Full\n"); return; }
    q->rear = (q->rear + 1) % MAXSIZE;
    q->data[q->rear] = val;
}

int ca_dequeue(CAQueue *q) {
    if (ca_empty(q)) return -1;
    q->front = (q->front + 1) % MAXSIZE;
    return q->data[q->front];
}

int main() {
    printf("=== Queue Implementations Demo ===\n\n");
    
    // Linked List Queue
    printf("1. Linked List Queue:\n");
    LLQueue llq; ll_init(&llq);
    ll_enqueue(&llq, 10); ll_enqueue(&llq, 20); ll_enqueue(&llq, 30);
    printf("Dequeue: %d\n", ll_dequeue(&llq));  // 10
    ll_enqueue(&llq, 40);
    while (!ca_empty((CAQueue*)&llq))  // Hack: reuse empty check
        printf("Dequeue: %d\n", ll_dequeue(&llq));
    
    // Circular Array Queue
    printf("\n2. Circular Array Queue (size 5):\n");
    CAQueue caq; ca_init(&caq);
    for (int i = 1; i <= 4; i++) ca_enqueue(&caq, i*10);
    printf("Enqueued 10,20,30,40\n");
    ca_enqueue(&caq, 50);  // Fills last slot
    ca_enqueue(&caq, 60);  // Should say "Full"
    printf("Dequeue all: ");
    while (!ca_empty(&caq))
        printf("%d ", ca_dequeue(&caq));
    printf("\n");
    
    return 0;
}
```

### Program 3: Priority Queue Comparison
```c
// pq_comparison.c - Priority Queue All 4 Implementations
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct { int job_no, priority; } Job;

typedef struct node { Job job; struct node *next; } Node;
typedef struct { Node *front, *rear; } PQList;

// Helper
Node* create_node(Job j) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->job = j; n->next = NULL;
    return n;
}

// ===== 1. Unordered List =====
void ulist_init(PQList *q) { q->front = q->rear = NULL; }

void ulist_enqueue(PQList *q, Job j) {
    Node *n = create_node(j);
    if (!q->rear) q->front = q->rear = n;
    else { q->rear->next = n; q->rear = n; }
}

Job ulist_dequeue(PQList *q) {
    Node *max_p = NULL, *max_c = q->front, *p = NULL, *c = q->front;
    int max_pri = c->job.priority;
    while (c) {
        if (c->job.priority > max_pri) {
            max_pri = c->job.priority; max_p = p; max_c = c;
        }
        p = c; c = c->next;
    }
    Job job = max_c->job;
    if (!max_p) q->front = max_c->next;
    else max_p->next = max_c->next;
    if (!max_c->next) q->rear = max_p;
    free(max_c);
    return job;
}

// ===== 2. Ordered List =====
void olist_enqueue(PQList *q, Job j) {
    Node *n = create_node(j);
    if (!q->front || q->front->job.priority <= j.priority) {
        n->next = q->front; q->front = n;
        if (!q->rear) q->rear = n;
    } else {
        Node *c = q->front;
        while (c->next && c->next->job.priority > j.priority) c = c->next;
        n->next = c->next; c->next = n;
        if (!n->next) q->rear = n;
    }
}

Job olist_dequeue(PQList *q) {
    Job j = q->front->job;
    Node *t = q->front;
    q->front = t->next;
    if (!q->front) q->rear = NULL;
    free(t);
    return j;
}

// ===== 3. Unordered Array =====
typedef struct { Job jobs[MAXSIZE]; int n; } PQArray;

void uarr_init(PQArray *q) { q->n = 0; }
void uarr_enqueue(PQArray *q, Job j) {
    if (q->n < MAXSIZE) q->jobs[q->n++] = j;
}

Job uarr_dequeue(PQArray *q) {
    int max_i = 0;
    for (int i = 1; i < q->n; i++)
        if (q->jobs[i].priority > q->jobs[max_i].priority) max_i = i;
    Job j = q->jobs[max_i];
    for (int i = max_i; i < q->n - 1; i++) q->jobs[i] = q->jobs[i+1];
    q->n--;
    return j;
}

// ===== 4. Ordered Array =====
void oarr_enqueue(PQArray *q, Job j) {
    int i = q->n - 1;
    while (i >= 0 && q->jobs[i].priority >= j.priority) {
        q->jobs[i+1] = q->jobs[i];
        i--;
    }
    q->jobs[i+1] = j; q->n++;
}

Job oarr_dequeue(PQArray *q) {
    return q->jobs[--q->n];
}

// Test
void test_pq(char *name, void (*enq)(void*,Job), Job (*deq)(void*), void *q) {
    Job jobs[] = {{1,10}, {2,30}, {3,20}, {4,5}, {5,25}};
    for (int i = 0; i < 5; i++) enq(q, jobs[i]);
    printf("%s: ", name);
    while (1) {
        Job j = deq(q);
        if (j.job_no == 0 && j.priority == 0) break;  // Empty check needed
        printf("J%d(p%d) ", j.job_no, j.priority);
    }
    printf("\n");
}

int main() {
    printf("=== Priority Queue Comparison ===\n\n");
    
    // Note: Each implementation needs separate test due to different structures
    // This is a simplified demo
    
    // Unordered List
    PQList ulist; ulist_init(&ulist);
    Job jobs[] = {{1,10}, {2,30}, {3,20}, {4,5}, {5,25}};
    for (int i = 0; i < 5; i++) ulist_enqueue(&ulist, jobs[i]);
    printf("Unordered List (Dequeue order): ");
    for (int i = 0; i < 5; i++) {
        Job j = ulist_dequeue(&ulist);
        printf("J%d(p%d) ", j.job_no, j.priority);
    }
    printf("\n");
    
    // Ordered List
    PQList olist; ulist_init(&olist);  // Reuse init
    for (int i = 0; i < 5; i++) olist_enqueue(&olist, jobs[i]);
    printf("Ordered List (Dequeue order):  ");
    for (int i = 0; i < 5; i++) {
        Job j = olist_dequeue(&olist);
        printf("J%d(p%d) ", j.job_no, j.priority);
    }
    printf("\n");
    
    // Unordered Array
    PQArray uarr; uarr_init(&uarr);
    for (int i = 0; i < 5; i++) uarr_enqueue(&uarr, jobs[i]);
    printf("Unordered Array (Dequeue):       ");
    for (int i = 0; i < 5; i++) {
        Job j = uarr_dequeue(&uarr);
        printf("J%d(p%d) ", j.job_no, j.priority);
    }
    printf("\n");
    
    // Ordered Array
    PQArray oarr; uarr_init(&oarr);
    for (int i = 0; i < 5; i++) oarr_enqueue(&oarr, jobs[i]);
    printf("Ordered Array (Dequeue):         ");
    for (int i = 0; i < 5; i++) {
        Job j = oarr_dequeue(&oarr);
        printf("J%d(p%d) ", j.job_no, j.priority);
    }
    printf("\n");
    
    return 0;
}
```

---

## 📝 Key Takeaways for Unit 2

| Concept | Key Insight |
|---------|-------------|
| **Stack** | LIFO, Push/Pop at top |
| **Stack Apps** | Parentheses, Infix→Postfix, Postfix Eval, Recursion |
| **Queue** | FIFO, Enqueue at rear, Dequeue at front |
| **Circular Queue** | Modulo arithmetic, waste 1 slot |
| **Priority Queue** | Dequeue by priority, not arrival |
| **PQ Implementations** | Trade-off: Enqueue vs Dequeue speed |
| **Deque** | Both ends, generalizes Stack/Queue |

---

## 📚 Reference Materials

- **Notes:** Unit 2 Combined Notes (96 pages)
- **Slides:** Unit 2 Combined Slides (169 pages)
- **Assignments:** Weeks 4, 5, 6
- **MCQ Bank:** 16 pages

---

*Next: Unit 3 - Trees, BST, Heaps, AVL, Splay, Graphs*