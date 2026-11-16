# Unit 2: Anchor Programs

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

---

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

---

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

int main() {
    printf("=== Priority Queue Comparison ===\n\n");
    
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
    PQList olist; ulist_init(&olist);
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

## 📝 Key Programs Summary

| Program | Concepts Covered |
|---------|------------------|
| **Stack Apps** | Parentheses, Infix→Postfix, Postfix Eval |
| **Queue Impls** | LL Queue, Circular Array Queue |
| **PQ Comparison** | All 4 PQ implementations |

---

## 📋 Compilation & Testing

```bash
# Compile all
gcc stack_apps_demo.c -o stack
gcc queue_demo.c -o queue
gcc pq_comparison.c -o pq

# Run
./stack
./queue
./pq
```

---

*End of Unit 2 Anchor Programs*

---

*Next: [Unit 3: Trees, BST, Heaps, AVL, Splay, Graphs →](../unit3/)*