# Unit 1: Detailed Example Programs

## 1.1 Swap Function Examples

### 1.1.1 Pass by Value (Does NOT Work)
```c
// 1_swap.c
#include <stdio.h>

void swap(int x, int y) {
    int temp = x; x = y; y = temp;
}

int main() {
    int a = 10, b = 20;
    swap(a, b);
    printf("a : %d b : %d\n", a, b);  // Output: a : 10 b : 20
    return 0;
}
```

### 1.1.2 Pass by Pointer (WORKS)
```c
// 2_swap.c
#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x; *x = *y; *y = temp;
}

int main() {
    int a = 10, b = 20;
    swap(&a, &b);
    printf("a : %d b : %d\n", a, b);  // Output: a : 20 b : 10
    return 0;
}
```

---

## 1.2 Recursion Examples

### 1.2.1 Count 1s in Binary
```c
// 3_what.c
#include <stdio.h>

int what(int n) {
    if (n == 0) return 0;
    else if (n % 2) return 1 + what(n / 2);
    else return what(n / 2);
}

int main() {
    int n = 25;  // Binary: 11001 (three 1s)
    printf("val : %d\n", what(n));  // Output: 3
    return 0;
}
```

### 1.2.2 Fast Power (Exponentiation by Squaring)
```c
// 4_power.c
#include <stdio.h>

int power(int a, int n) {
    if (n == 0) return 1;
    else if (n % 2) return a * power(a * a, n / 2);
    else return power(a * a, n / 2);
}

int main() {
    printf("%d\n", power(3, 5));  // 3^5 = 243
    printf("%d\n", power(2, 10)); // 2^10 = 1024
    return 0;
}
```

### 1.2.3 GCD with Aliasing Demo
```c
// 5_gcd_aliasing.c
#include <stdio.h>

void what(int *p, int *q) {
    int m = *p, n = *q;
    while (m != n) {
        if (m > n) m -= n;
        else n -= m;
    }
    *p /= m; *q /= n;
}

int main() {
    int a = 25, b = 15;
    what(&a, &b);
    printf("%d %d\n", a, b);  // 5 3
    
    // Aliasing demo
    what(&a, &a);
    printf("%d\n", a);  // 0 (divided twice!)
    return 0;
}
```

---

## 1.3 Palindrome Check with Separate Interface

### 1.3.1 Header File
```c
// palindrome.h
#ifndef PALINDROME_H
#define PALINDROME_H

int is_palindrome(int n);
int rev(int n);

#endif
```

### 1.3.2 Implementation
```c
// palindrome.c
#include "palindrome.h"

int rev(int n) {
    int r = 0;
    while (n) {
        r = r * 10 + n % 10;
        n /= 10;
    }
    return r;
}

int is_palindrome(int n) {
    return n == rev(n);
}
```

### 1.3.3 Client Code
```c
// client.c
#include <stdio.h>
#include "palindrome.h"

int main() {
    int n; scanf("%d", &n);
    if (is_palindrome(n))
        printf("%d is a palindrome\n", n);
    else
        printf("%d is not a palindrome\n", n);
    return 0;
}
```

### 1.3.4 Makefile
```makefile
# mymakefile.mk
client: client.o palindrome.o
    gcc client.o palindrome.o -o client

client.o: client.c palindrome.h
    gcc -c client.c

palindrome.o: palindrome.c palindrome.h
    gcc -c palindrome.c
```

---

## 1.4 Array Examples

### 1.4.1 Basic Array Operations
```c
// array_examples.c
#include <stdio.h>

int main() {
    // Declaration and initialization
    int a[5] = {11, 22, 33, 44, 55};
    int b[] = {10, 20, 30, 40, 50};  // Size = 5
    int c[5] = {11, 22};             // Rest = 0
    
    // Traversal methods
    int n = 5;
    int *p = a;
    
    // Index
    for (int i = 0; i < n; ++i) printf("%d ", a[i]);
    
    // Pointer v1
    for (int i = 0; i < n; ++i) printf("%d ", p[i]);
    
    // Pointer v2
    for (int i = 0; i < n; ++i) printf("%d ", *(p + i));
    
    // Pointer v3
    for (int i = 0; i < n; ++i) printf("%d ", *p++);
    
    return 0;
}
```

### 1.4.2 Array Utility Functions
```c
// array_util.h
#ifndef ARRAY_UTIL_H
#define ARRAY_UTIL_H

void read_array(int x[], int n);
void disp_array(int *x, int n);

#endif
```

```c
// array_util.c
#include <stdio.h>
#include "array_util.h"

void read_array(int x[], int n) {
    for (int i = 0; i < n; ++i)
        scanf("%d", x++);  // or &x[i] or x+i
}

void disp_array(int *x, int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", *x++);
    printf("\n");
}
```

### 1.4.3 2D Array with Variable Dimensions
```c
// matrix_flexible.h
#ifndef MATRIX_FLEXIBLE_H
#define MATRIX_FLEXIBLE_H

void read_matrix(int rowsize, int columnsize, 
                 int x[rowsize][columnsize], int m, int n);
void disp_matrix(int rowsize, int columnsize,
                 int x[rowsize][columnsize], int m, int n);

#endif
```

```c
// matrix_flexible.c
#include <stdio.h>
#include "matrix_flexible.h"

void read_matrix(int rowsize, int columnsize, 
                 int x[rowsize][columnsize], int m, int n) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &x[i][j]);
}

void disp_matrix(int rowsize, int columnsize,
                 int x[rowsize][columnsize], int m, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%5d ", x[i][j]);
        printf("\n");
    }
}
```

---

## 1.5 Structure Examples

### 1.5.1 Basic Structure with Size Demo
```c
// struct_size.c
#include <stdio.h>

struct test1 { char j; int i; };
struct test2 { int i; char j; };

int main() {
    printf("sizeof(test1): %lu\n", sizeof(struct test1));  // 8 (padded)
    printf("sizeof(test2): %lu\n", sizeof(struct test2));  // 8 (padded)
    
    #pragma pack(1)
    struct packed1 { char j; int i; };
    struct packed2 { int i; char j; };
    #pragma pack()
    
    printf("packed1: %lu\n", sizeof(struct packed1));  // 5
    printf("packed2: %lu\n", sizeof(struct packed2));  // 5
    return 0;
}
```

### 1.5.2 Structure Initialization
```c
// struct_init.c
#include <stdio.h>
#include <string.h>

struct student {
    int rnum;
    char name[20];
    int marks;
};

int main() {
    // Uninitialized
    struct student s1;
    
    // Full init
    struct student s2 = {23, "pes", 99};
    
    // Partial init
    struct student s3 = {23, "pes"};  // marks = 0
    
    // Designated init
    struct student s5 = {.name="pes", .marks=45};  // rnum = 0
    
    // Copy
    struct student s6 = s2;  // Memberwise copy
    s6.marks = 100;          // s2.marks unchanged
    
    return 0;
}
```

### 1.5.3 Structure Parameter Passing
```c
// struct_param.c
#include <stdio.h>
#include <string.h>

struct test {
    int i;
    char a[20];
    float j;
};

void f1(struct test t) {      // By value
    strcpy(t.a, "pqrstuv");
}

void f2(struct test *p) {     // By pointer (modify)
    strcpy(p->a, "pqr");
}

void f3(const struct test *p) {  // By const pointer (read-only)
    printf("%s\n", p->a);
}

int main() {
    struct test t1 = {20, "xyz", 78.5f};
    printf("%s ", t1.a);  // xyz
    f1(t1);
    printf("%s ", t1.a);  // xyz (unchanged)
    f2(&t1);
    printf("%s ", t1.a);  // pqr (changed)
    f3(&t1);              // pqr
    return 0;
}
```

### 1.5.4 Structure Return
```c
// struct_return.c
#include <stdio.h>
#include <string.h>

struct test {
    int i;
    char a[20];
    float j;
};

struct test f1(struct test t) {
    strcpy(t.a, "pqrstuv");
    return t;  // Returned via temporary
}

int main() {
    struct test t1 = {20, "xyz", 78.5f};
    printf("%s ", t1.a);  // xyz
    t1 = f1(t1);
    printf("%s\n", t1.a); // pqrstuv
    return 0;
}
```

---

## 1.6 Dynamic Memory Examples

### 1.6.1 Basic malloc/free
```c
// dm_basic.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = (int*)malloc(sizeof(int));
    if (p == NULL) return 1;
    
    *p = 20;
    printf("%d\n", *p);  // 20
    
    free(p);  // p now dangling
    
    // Array on heap
    p = (int*)malloc(sizeof(int) * 4);
    p[0] = 11; p[1] = 22; p[2] = 33; p[3] = 44;
    for (int i = 0; i < 4; ++i) printf("%d ", p[i]);
    free(p);
    return 0;
}
```

### 1.6.2 calloc and realloc
```c
// dm_calloc_realloc.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // calloc - zero initialized
    int *p = (int*)calloc(4, sizeof(int));
    for (int i = 0; i < 4; ++i) printf("%d ", p[i]);  // 0 0 0 0
    
    // realloc - resize
    int *q = (int*)realloc(p, 10 * sizeof(int));
    // q may be different from p
    // Old values preserved, new space uninitialized
    q[4] = 55;
    free(q);
    return 0;
}
```

### 1.6.3 Common Pitfalls
```c
// dm_pitfalls.c
#include <stdio.h>
#include <stdlib.h>

// Aliasing
void demo_aliasing() {
    int *p = malloc(sizeof(int));
    *p = 100;
    int *q = p;
    *q = 110;  // *p also 110
    free(q);
    // p now dangling
}

// Memory leak
void demo_leak() {
    int *p = malloc(sizeof(int));
    *p = 30;
    p = malloc(sizeof(int));  // First block leaked!
    // No way to free first block
}

// Dangling pointer
void demo_dangling() {
    int *p = malloc(sizeof(int));
    *p = 30;
    int *q = p;
    free(q);
    // p and q both dangling
    // printf("%d", *p);  // UNDEFINED BEHAVIOR!
}

// Scope leak
void demo_scope_leak() {
    int *p;
    {
        p = malloc(sizeof(int));
        *p = 30;
        int *q = p;
        free(q);  // OK
    }
    // p is dangling here
    // printf("%d", *p);  // UNDEFINED!
}
```

---

## 1.7 Linked List Complete Implementation

### 1.7.1 Header File
```c
// mylist.h
#ifndef MYLIST_H
#define MYLIST_H

struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

struct mylist {
    node_t *head;
};
typedef struct mylist mylist_t;

void init_list(mylist_t*);
void insert_list(mylist_t*, int key);
void disp_list(mylist_t*);
void free_list(mylist_t*);

#endif
```

### 1.7.2 Implementation
```c
// mylist.c
#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"

void init_list(mylist_t* ptr_list) {
    ptr_list->head = NULL;
}

void insert_list(mylist_t* ptr_list, int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->next_ = NULL;
    
    if (ptr_list->head == NULL) {
        ptr_list->head = temp;
    } else {
        node_t* prev = NULL;
        node_t* pres = ptr_list->head;
        while (pres != NULL && pres->key_ < temp->key_) {
            prev = pres;
            pres = pres->next_;
        }
        if (prev == NULL) {  // Beginning
            temp->next_ = pres;
            ptr_list->head = temp;
        } else {  // Middle or end
            temp->next_ = pres;
            prev->next_ = temp;
        }
    }
}

void disp_(node_t* q) {
    while (q != NULL) {
        printf("%d ", q->key_);
        q = q->next_;
    }
}

void disp_list(mylist_t* ptr_list) {
    disp_(ptr_list->head);
}

void free_list_(node_t* q) {
    node_t* r;
    while (q != NULL) {
        r = q->next_;
        free(q);
        q = r;
    }
}

void free_list(mylist_t* ptr_list) {
    free_list_(ptr_list->head);
}
```

### 1.7.3 Client
```c
// client.c
#include <stdio.h>
#include "mylist.h"

int main() {
    mylist_t l;
    init_list(&l);
    
    int a[] = {20, 10, 50, 30, 40};
    int n = 5;
    for (int i = 0; i < n; ++i)
        insert_list(&l, a[i]);
    
    disp_list(&l);  // Output: 10 20 30 40 50
    free_list(&l);
    return 0;
}
```

### 1.7.4 Makefile
```makefile
# makefile
a.exe: mylist.o client.o
    gcc mylist.o client.o -o a.exe

mylist.o: mylist.c mylist.h
    gcc -Wall -c mylist.c

client.o: client.c mylist.h
    gcc -Wall -c client.c
```

---

## 1.8 List with Header Node

### 1.8.1 Header File
```c
// mylist_header.h
#ifndef MYLIST_H
#define MYLIST_H

struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;

struct mylist {
    node_t *head_;
};
typedef struct mylist mylist_t;

void init_list(mylist_t*);
void insert_list(mylist_t*, int key);
void disp_list(mylist_t*);
void free_list(mylist_t*);

#endif
```

### 1.8.2 Implementation (Simplified Insert!)
```c
// mylist_header.c
#include <stdio.h>
#include <stdlib.h>
#include "mylist_header.h"

void init_list(mylist_t* ptr_list) {
    ptr_list->head_ = (node_t*)malloc(sizeof(node_t));
    ptr_list->head_->next_ = NULL;  // Header node, key_ unused
}

void insert_list(mylist_t* ptr_list, int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->next_ = NULL;
    
    // ALWAYS start from header - no empty list check needed!
    node_t* prev = ptr_list->head_;
    node_t* pres = ptr_list->head_->next_;
    
    while (pres != NULL && pres->key_ < temp->key_) {
        prev = pres;
        pres = pres->next_;
    }
    
    // SAME code for middle AND end!
    temp->next_ = pres;
    prev->next_ = temp;
}

void disp_list(mylist_t* ptr_list) {
    node_t* q = ptr_list->head_->next_;  // Skip header
    while (q != NULL) {
        printf("%d ", q->key_);
        q = q->next_;
    }
    printf("\n");
}

void free_list(mylist_t* ptr_list) {
    node_t* q = ptr_list->head_->next_;
    while (q != NULL) {
        node_t* r = q->next_;
        free(q);
        q = r;
    }
    free(ptr_list->head_);  // Free header too
    ptr_list->head_ = NULL;
}
```

---

## 1.9 Stack Implementation

### 1.9.1 Array Stack
```c
// stack_array.h
#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#define MAXSIZE 5

struct stack {
    char key_[MAXSIZE];
    int top_;  // Index of top element (-1 = empty)
};
typedef struct stack stack_t;

void init_stack(stack_t*);
void deinit_stack(stack_t*);
void push(stack_t*, char);
char pop(stack_t*);
int is_empty(stack_t*);
int is_full(stack_t*);

#endif
```

```c
// stack_array.c
#include <stdio.h>
#include "stack_array.h"

void init_stack(stack_t *ptr_stack) {
    ptr_stack->top_ = -1;
}

void deinit_stack(stack_t *ptr_stack) {
    ptr_stack->top_ = -1;
}

void push(stack_t *ptr_stack, char ch) {
    if (!is_full(ptr_stack)) {
        ptr_stack->key_[++ptr_stack->top_] = ch;
    } else {
        printf("stack full\n");
    }
}

char pop(stack_t *ptr_stack) {
    if (!is_empty(ptr_stack)) {
        return ptr_stack->key_[ptr_stack->top_--];
    }
    printf("stack empty\n");
    return '\0';
}

int is_empty(stack_t *ptr_stack) {
    return ptr_stack->top_ == -1;
}

int is_full(stack_t *ptr_stack) {
    return ptr_stack->top_ == MAXSIZE - 1;
}
```

### 1.9.2 Linked List Stack
```c
// stack_list.h
#ifndef STACK_LIST_H
#define STACK_LIST_H

struct node {
    char key_;
    struct node* next_;
};
typedef struct node node_t;

struct stack {
    node_t* top_;
};
typedef struct stack stack_t;

void init_stack(stack_t*);
void deinit_stack(stack_t*);
void push(stack_t*, char);
char pop(stack_t*);
int is_empty(stack_t*);
int is_full(stack_t*);

#endif
```

```c
// stack_list.c
#include <stdio.h>
#include <stdlib.h>
#include "stack_list.h"

void init_stack(stack_t *ptr_stack) {
    ptr_stack->top_ = NULL;
}

void deinit_stack(stack_t *ptr_stack) {
    while (!is_empty(ptr_stack)) pop(ptr_stack);
}

void push(stack_t *ptr_stack, char ch) {
    if (!is_full(ptr_stack)) {
        node_t* temp = (node_t*)malloc(sizeof(node_t));
        temp->key_ = ch;
        temp->next_ = ptr_stack->top_;
        ptr_stack->top_ = temp;
    }
}

char pop(stack_t *ptr_stack) {
    if (!is_empty(ptr_stack)) {
        char ch = ptr_stack->top_->key_;
        node_t* temp = ptr_stack->top_;
        ptr_stack->top_ = ptr_stack->top_->next_;
        free(temp);
        return ch;
    }
    return '\0';
}

int is_empty(stack_t *ptr_stack) {
    return ptr_stack->top_ == NULL;
}

int is_full(stack_t *ptr_stack) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) return 1;
    free(temp);
    return 0;
}
```

### 1.9.3 Client (Works with BOTH implementations!)
```c
// stack_client.c
#include <stdio.h>
#include "stack.h"  // Can be stack_array.h or stack_list.h

int main() {
    stack_t mystack;
    init_stack(&mystack);
    
    char str[100];
    scanf("%s", str);
    
    // Push all chars
    for (int i = 0; str[i]; ++i)
        push(&mystack, str[i]);
    
    // Pop and display (reverses string)
    while (!is_empty(&mystack))
        printf("%c", pop(&mystack));
    printf("\n");
    
    deinit_stack(&mystack);
    return 0;
}
```

---

## 1.10 Stack Applications

### 1.10.1 Well-Formed Parentheses
```c
// paren_check.c
#include <stdio.h>
#include "stack.h"

int main() {
    stack_t mystack;
    init_stack(&mystack);
    
    char str[100];
    scanf("%s", str);
    
    int is_valid = 1;
    for (char *s = str; is_valid && *s; ++s) {
        if (*s == '(') push(&mystack, 'x');
        else if (*s == ')') {
            if (!is_empty(&mystack)) pop(&mystack);
            else is_valid = 0;
        }
    }
    
    if (is_valid && is_empty(&mystack))
        printf("Well formed\n");
    else
        printf("Not well formed\n");
    
    return 0;
}
```

### 1.10.2 Well-Formed Brackets (Multiple Types)
```c
// bracket_check.c
#include <stdio.h>
#include "stack.h"

int main() {
    stack_t mystack;
    init_stack(&mystack);
    
    char str[100];
    scanf("%s", str);
    
    int is_valid = 1;
    for (char *s = str; is_valid && *s; ++s) {
        if (*s == '(') push(&mystack, ')');
        else if (*s == '[') push(&mystack, ']');
        else if (*s == '{') push(&mystack, '}');
        else if (*s == ')' || *s == ']' || *s == '}') {
            if (!is_empty(&mystack)) {
                if (*s != pop(&mystack)) is_valid = 0;
            } else is_valid = 0;
        }
    }
    
    if (is_valid && is_empty(&mystack))
        printf("Well formed\n");
    else
        printf("Not well formed\n");
    
    return 0;
}
```

### 1.10.3 Postfix Evaluation
```c
// postfix_eval.c
#include <stdio.h>
#include <ctype.h>
#include "stack_int.h"  // Stack of int

int main() {
    stack_t mystack;
    init_stack(&mystack);
    
    char str[100];
    gets(str);
    
    int val = 0, is_num = 0;
    for (char *s = str; *s; ++s) {
        if (isdigit(*s)) {
            val = val * 10 + *s - '0';
            is_num = 1;
        } else if (*s == ' ' && is_num) {
            push(&mystack, val);
            val = 0; is_num = 0;
        } else if (*s == '+' || *s == '-' || *s == '*' || *s == '/') {
            int v1 = pop(&mystack);
            int v2 = pop(&mystack);
            switch(*s) {
                case '+': push(&mystack, v2 + v1); break;
                case '-': push(&mystack, v2 - v1); break;
                case '*': push(&mystack, v2 * v1); break;
                case '/': push(&mystack, v2 / v1); break;
            }
        }
    }
    printf("Result: %d\n", pop(&mystack));
    return 0;
}
```

### 1.10.4 Infix to Postfix
```c
// infix_to_postfix.c
#include <stdio.h>
#include "stack.h"

int prec_in_str(char ch) {
    if (ch == '(') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

int prec_in_stack(char ch) {
    if (ch == '(') return 0;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

int main() {
    stack_t mystack;
    init_stack(&mystack);
    
    char in[100], post[200];
    char *s = in, *p = post;
    gets(in);
    
    char ch, ch1;
    while ((ch = *s++) != '\0') {
        if (ch == ')') {
            while ((ch1 = pop(&mystack)) != '(') {
                *p++ = ' '; *p++ = ch1;
            }
        } else if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (is_empty(&mystack)) push(&mystack, ch);
            else {
                while (!is_empty(&mystack) &&
                       prec_in_str(ch) < prec_in_stack(peek(&mystack))) {
                    *p++ = ' '; *p++ = pop(&mystack);
                }
                push(&mystack, ch);
            }
        } else {
            *p++ = ch;  // Operand
        }
    }
    while (!is_empty(&mystack)) {
        *p++ = ' '; *p++ = pop(&mystack);
    }
    *p = '\0';
    
    printf("infix: %s\n", in);
    printf("postfix: %s\n", post);
    return 0;
}
```

---

## 1.11 Polynomial ADT (Experiential Learning)

### 1.11.1 Term Structure
```c
// term.h
typedef struct {
    int coeff_;
    int exp_;
} term_t;

void set_term(term_t*, int coeff, int exp);
void disp_term(term_t*);
int compare_term(term_t*, term_t*);  // By exponent
```

### 1.11.2 Polynomial Operations
```c
// polynomial.c
// Task 1: Create polynomial (ordered list of terms by decreasing exponent)
// Task 2: Evaluate polynomial at x
// Task 3: Copy polynomial
// Task 4: Differentiate polynomial

// Evaluation: sum(coeff * x^exp)
// Differentiation: coeff * exp * x^(exp-1)
```

---

## 1.12 Skiplist Structure (Conceptual)

```c
// skiplist_node.h
struct skiplist_node {
    int key_;
    struct skiplist_node **forward_;  // Array of forward pointers
    int level_;                       // Number of levels for this node
};
```

---

## 1.13 Multilist - Sparse Matrix

```c
// sparse_matrix.h
struct matrix_node {
    int row_, col_, value_;
    struct matrix_node *right_;  // Next in row
    struct matrix_node *down_;   // Next in column
};
```