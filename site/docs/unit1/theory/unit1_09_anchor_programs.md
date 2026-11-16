# Unit 1: Anchor Programs - Complete Reference

## 🎯 Complete Programs from Course Material

---

## Program 1: Complete Singly Linked List

```c
// sll_complete.c - Complete Singly Linked List Implementation
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} NODE;

NODE *create_node(int data) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    if (!temp) { printf("Memory full\n"); exit(1); }
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void insert_front(NODE **head, int data) {
    NODE *temp = create_node(data);
    temp->next = *head;
    *head = temp;
}

void insert_end(NODE **head, int data) {
    NODE *temp = create_node(data);
    if (*head == NULL) { *head = temp; return; }
    NODE *curr = *head;
    while (curr->next) curr = curr->next;
    curr->next = temp;
}

void insert_at_pos(NODE **head, int data, int pos) {
    if (pos <= 1 || *head == NULL) { insert_front(head, data); return; }
    NODE *temp = create_node(data);
    NODE *curr = *head, *prev = NULL;
    int i = 1;
    while (curr && i < pos) { prev = curr; curr = curr->next; i++; }
    if (!curr) { prev->next = temp; }
    else { prev->next = temp; temp->next = curr; }
}

void delete_front(NODE **head) {
    if (!*head) return;
    NODE *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void delete_end(NODE **head) {
    if (!*head) return;
    if (!(*head)->next) { free(*head); *head = NULL; return; }
    NODE *curr = *head, *prev = NULL;
    while (curr->next) { prev = curr; curr = curr->next; }
    prev->next = NULL;
    free(curr);
}

void delete_at_pos(NODE **head, int pos) {
    if (!*head) return;
    if (pos <= 1) { delete_front(head); return; }
    NODE *curr = *head, *prev = NULL;
    int i = 1;
    while (curr && i < pos) { prev = curr; curr = curr->next; i++; }
    if (!curr) { printf("Invalid position\n"); return; }
    prev->next = curr->next;
    free(curr);
}

void display(NODE *head) {
    printf("List: ");
    while (head) { printf("%d → ", head->data); head = head->next; }
    printf("NULL\n");
}

int main() {
    NODE *head = NULL;
    
    printf("=== Singly Linked List Demo ===\n");
    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);
    display(head);  // 10 → 20 → 30
    
    insert_front(&head, 5);
    display(head);  // 5 → 10 → 20 → 30
    
    insert_at_pos(&head, 15, 3);
    display(head);  // 5 → 10 → 15 → 20 → 30
    
    delete_front(&head);
    display(head);  // 10 → 15 → 20 → 30
    
    delete_end(&head);
    display(head);  // 10 → 15 → 20
    
    delete_at_pos(&head, 2);
    display(head);  // 10 → 20
    
    return 0;
}
```

---

## Program 2: Dynamic Memory Demo

```c
// memory_demo.c - Dynamic Memory Allocation Demo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("=== Dynamic Memory Demo ===\n\n");
    
    // 1. malloc
    printf("1. malloc():\n");
    int *p = (int*)malloc(5 * sizeof(int));
    if (!p) { printf("Failed\n"); return 1; }
    for (int i = 0; i < 5; i++) p[i] = (i+1)*10;
    printf("Allocated 5 ints: ");
    for (int i = 0; i < 5; i++) printf("%d ", p[i]);
    printf("\n");
    free(p);
    p = NULL;  // Good practice: set to NULL after free
    
    // 2. calloc (zero-initialized)
    printf("\n2. calloc():\n");
    int *q = (int*)calloc(5, sizeof(int));
    printf("Zero-initialized: ");
    for (int i = 0; i < 5; i++) printf("%d ", q[i]);
    printf("\n");
    free(q);
    
    // 3. realloc
    printf("\n3. realloc():\n");
    int *r = (int*)malloc(3 * sizeof(int));
    r[0] = 1; r[1] = 2; r[2] = 3;
    printf("Before realloc: ");
    for (int i = 0; i < 3; i++) printf("%d ", r[i]);
    r = (int*)realloc(r, 6 * sizeof(int));
    r[3] = 4; r[4] = 5; r[5] = 6;
    printf("\nAfter realloc:  ");
    for (int i = 0; i < 6; i++) printf("%d ", r[i]);
    printf("\n");
    free(r);
    
    // 4. Structure allocation
    printf("\n4. Structure allocation:\n");
    struct student {
        char name[20];
        int roll;
        float marks;
    };
    struct student *s = (struct student*)malloc(sizeof(struct student));
    strcpy(s->name, "Alice");
    s->roll = 101;
    s->marks = 95.5;
    printf("Student: %s, Roll: %d, Marks: %.1f\n", s->name, s->roll, s->marks);
    free(s);
    
    printf("\n=== Dangling Pointer Demo ===\n");
    int *dang = (int*)malloc(sizeof(int));
    *dang = 100;
    printf("Before free: *dang = %d\n", *dang);
    free(dang);
    // dang is now DANGLING - don't use it!
    dang = NULL;  // Always set to NULL after free
    
    printf("\n=== Memory Leak Demo ===\n");
    // BAD: memory leak
    // int *leak = malloc(sizeof(int));
    // leak = malloc(sizeof(int));  // First block lost!
    
    // GOOD: free before reassign
    int *good = malloc(sizeof(int));
    *good = 42;
    free(good);
    good = malloc(sizeof(int));
    *good = 84;
    free(good);
    printf("No leaks!\n");
    
    return 0;
}
```

---

## Program 3: Circular List & Josephus

```c
// circular_josephus.c - Circular List & Josephus Problem
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} node_t;

node_t* create_node(int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key = key;
    temp->next = NULL;
    return temp;
}

void insert_clist(node_t **head, int key) {
    node_t *temp = create_node(key);
    if (*head == NULL) {
        temp->next = temp;
        *head = temp;
    } else {
        temp->next = (*head)->next;
        (*head)->next = temp;
    }
}

void disp_clist(node_t *head) {
    if (!head) { printf("Empty\n"); return; }
    node_t *temp = head;
    printf("Circular: ");
    do {
        printf("%d ", temp->key);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Josephus Problem
int josephus(int n, int k) {
    node_t *head = NULL, *tail = NULL;
    for (int i = 1; i <= n; i++) {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->key = i; temp->next = NULL;
        if (!head) head = tail = (node_t*)malloc(sizeof(node_t));
        else { tail->next = temp; tail = temp; }
    }
    tail->next = head;  // Make circular
    
    node_t *curr = head, *prev = head;
    // Find tail (node before head)
    while (prev->next != head) prev = prev->next;
    
    while (curr->next != curr) {
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
    }
    int survivor = curr->key;
    free(curr);
    return survivor;
}

int main() {
    printf("=== Circular List Demo ===\n");
    node_t *head = NULL;
    for (int i = 1; i <= 5; i++) insert_clist(&head, i*10);
    printf("List: "); disp_clist(head);
    
    printf("\n=== Josephus Problem ===\n");
    printf("n=7, k=3: Survivor = %d\n", josephus(7, 3));  // 4
    printf("n=5, k=2: Survivor = %d\n", josephus(5, 2));  // 3
    printf("n=41, k=3: Survivor = %d\n", josephus(41, 3)); // Historical: 31
    
    return 0;
}
```

---

## Program 4: Doubly Linked List Complete

```c
// dll_complete.c - Doubly Linked List
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} NODE;

typedef struct {
    NODE *head, *tail;
} dll_t;

void init_dll(dll_t *list) { list->head = list->tail = NULL; }

NODE* create_node(int data) {
    NODE *n = malloc(sizeof(NODE));
    n->data = data; n->prev = n->next = NULL;
    return n;
}

void insert_front(dll_t *list, int data) {
    NODE *n = malloc(sizeof(NODE));
    n->data = data; n->prev = NULL; n->next = list->head;
    if (!list->head) list->head = list->tail = n;
    else { list->head->prev = n; list->head = n; }
}

void insert_end(dll_t *list, int data) {
    NODE *n = malloc(sizeof(NODE));
    n->data = data; n->next = NULL; n->prev = list->tail;
    if (!list->tail) list->head = list->tail = n;
    else { list->tail->next = n; list->tail = n; }
}

void delete_node(dll_t *list, NODE *n) {
    if (!n) return;
    if (n == list->head && n == list->tail) list->head = list->tail = NULL;
    else if (n == list->head) { list->head = n->next; list->head->prev = NULL; }
    else if (n == list->tail) { list->tail = n->prev; list->tail->next = NULL; }
    else { n->prev->next = n->next; n->next->prev = n->prev; }
    free(n);
}

void display_forward(dll_t *list) {
    NODE *c = list->head;
    printf("Forward: ");
    while (c) { printf("%d ", c->data); c = c->next; }
    printf("\n");
}

void display_backward(dll_t *list) {
    NODE *c = list->tail;
    printf("Backward: ");
    while (c) { printf("%d ", c->data); c = c->prev; }
    printf("\n");
}

int main() {
    dll_t list; init_dll(&list);
    
    insert_end(&list, 10);
    insert_end(&list, 20);
    insert_end(&list, 30);
    insert_front(&list, 5);
    
    display_forward(&list);   // 5 10 20 30
    display_backward(&list);  // 30 20 10 5
    
    return 0;
}
```

---

## Program 5: Stack Applications

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

## 📝 Key Programs Summary

| Program | Concepts Covered |
|---------|------------------|
| **SLL Complete** | Insert (front/end/pos), Delete (front/end/pos), Display |
| **Memory Demo** | malloc, calloc, realloc, free, dangling, leaks |
| **Circular + Josephus** | Circular list, do-while, Josephus algorithm |
| **DLL Complete** | Insert front/end, Delete with pointer, Forward/Backward |
| **Stack Apps** | Parentheses, Infix→Postfix, Postfix Eval |

---

## 📋 Compilation & Testing

```bash
# Compile all
gcc sll_complete.c -o sll
gcc memory_demo.c -o mem
gcc circular_josephus.c -o circ
gcc dll_complete.c -o dll
gcc stack_apps_demo.c -o stack

# Run
./sll
./mem
./circ
./dll
./stack
```

---

## 📝 Key Takeaways

| Program | Key Learning |
|---------|-------------|
| **SLL** | All insert/delete cases with edge cases |
| **Memory** | malloc/calloc/realloc/free best practices |
| **Josephus** | Circular list + elimination algorithm |
| **DLL** | Bidirectional traversal, O(1) insert/delete |
| **Stack Apps** | Real-world stack applications |

---

*End of Unit 1 Anchor Programs*

---

*Next Unit: [Unit 2: Circular Lists, Doubly Linked Lists, Queues, Priority Queues →](../unit2/)*