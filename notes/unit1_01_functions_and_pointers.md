# Unit 1: Functions and Pointers

## Function Basics

A function associates a sequence of values (arguments) with a result value. In C, parameter passing is **by value** - copies of arguments are passed to parameters.

### Parameter Passing by Value

```c
// Does NOT swap - copies are swapped
void swap(int x, int y) {
    int temp = x; x = y; y = temp;
}

// DOES swap - pointers passed
void swap(int *x, int *y) {
    int temp = *x; *x = *y; *y = temp;
}
```

**Key concept**: To change a caller's variable, the callee must receive a pointer to that variable.

### Recursion

A function calling itself directly or indirectly is recursive. Requires:
- **Base case** (escape hatch) - simple case that stops recursion
- **Recursive step** - expresses solution in terms of smaller problem

```c
// Count 1s in binary representation
int what(int n) {
    if (n == 0) return 0;
    else if (n % 2) return 1 + what(n / 2);
    else return what(n / 2);
}
```

```c
// Power function: a^n
int what(int a, int n) {
    if (n == 0) return 1;
    else if (n % 2) return a * what(a * a, n / 2);
    else return what(a * a, n / 2);
}
```

### Pointer Concepts

**Aliasing**: Two pointers pointing to the same location
```c
int a = 25, b = 15;
what(&a, &b); // a=5, b=3
what(&a, &a); // Aliasing! a becomes 0 (divided twice)
```

**Dangling Pointer**: Pointer to memory that no longer exists
```c
int* two() {
    int x = 111;
    return &x; // DANGER: x destroyed on return
}
```

**Garbage / Memory Leak**: Allocated memory with no pointer to it
```c
p = malloc(sizeof(int));
p = malloc(sizeof(int)); // First allocation becomes garbage
```

## Function Declaration vs Definition

```c
// Declaration (interface) - in header file
int f2(int x, int y);

// Definition (implementation) - in source file
int f2(int x, int y) {
    return x + y;
}
```

**Interface** (declaration) is sacred - cannot change without affecting clients.
**Implementation** (definition) can change freely.

## Makefiles

```makefile
a.out : 6_client.o 6_server.o
    gcc 6_client.o 6_server.o

6_client.o : 6_client.c 6_server.h
    gcc -c 6_client.c

6_server.o : 6_server.c 6_server.h
    gcc -c 6_server.c
```

Run with: `make -f mymakefile.mk`

---

# Unit 1: Arrays

## Array Characteristics

- Homogeneous elements (same type)
- Fixed size at creation (compile-time constant or C99 VLA)
- Zero-based indexing
- **Random access** - O(1) access time regardless of position
- At runtime, array **degenerates to pointer** - size not stored
- No bounds checking - "programmer gets what he deserves"
- Not assignment compatible

## Declaration and Initialization

```c
int a[5] = {11, 22, 33, 44, 55};
int a[] = {10, 20, 30, 40, 50};    // Size inferred
int b[5];                          // Uninitialized (garbage)
int c[5] = {11, 22};               // Rest zero-initialized
```

## Array Traversal Methods

```c
int a[] = {10, 20, 30, 40, 50}; int n = 5;

// a) Indexing
for (int i = 0; i < n; ++i) printf("%d ", a[i]);

// b) Pointer v1: p[i]
int *p = a;
for (int i = 0; i < n; ++i) printf("%d ", p[i]);

// c) Pointer v2: *(p + i)
for (int i = 0; i < n; ++i) printf("%d ", *(p + i));

// d) Pointer v3: *p++
for (int i = 0; i < n; ++i) printf("%d ", *p++);

// e) CANNOT do: *a++ (array is constant pointer)
```

## Passing Arrays to Functions

```c
// Parameter is ALWAYS a pointer, never an array
void read_array(int x[], int n);    // int x[] == int *x
void disp_array(int *x, int n);

void read_array(int x[], int n) {
    for (int i = 0; i < n; ++i)
        scanf("%d", x++);  // or &x[i] or x+i
}

void disp_array(int *x, int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", *x++);
}
```

Three ways to pass array info:
1. Array + size
2. Begin pointer + end pointer
3. Sentinel value (e.g., '\0' for strings)

## Multidimensional Arrays

```c
int a[5][4];  // 5 rows, 4 columns - row-major order
```

**Address calculation** (row-major):
```
Address(A[i][j]) = Base + (i * num_columns + j) * sizeof(element)
```

Example: `int a[2][3] = {{66,90,86},{23,44,11}}`, base=2000, int=4 bytes
```
a[1][2] = 2000 + ((1*3)+2)*4 = 2020
```

### Passing 2D Arrays

```c
// Column size REQUIRED
void foo(int x[][4]);
void foo(int (*x)[4]);
void foo(int x[5][4]);  // First dimension ignored

// WRONG:
void foo(int x[][]);
void foo(int x[5][]);
```

### Flexible 2D Arrays (C99 VLA)

```c
void read_matrix(int rowsize, int columnsize, 
                 int x[rowsize][columnsize], int m, int n);
```

---

# Unit 1: Structures

## Structure Basics

```c
struct student {
    int rnum;
    char name[20];
    int marks;
};

struct student s1;
strcpy(s1.name, "abc");
s1.marks = 78;
s1.rnum = 56;
```

**Pointer to structure:**
```c
struct student *p = &s1;
(*p).marks    // or
p->marks      // preferred
```

## Structure Characteristics

- Heterogeneous components
- Named components (vs. computed indices in arrays)
- Fixed offsets at compile time
- Random access
- Size ≥ sum of member sizes (due to padding/alignment)
- **Does NOT degenerate to pointer** (unlike arrays)
- **Assignment compatible** - memberwise copy

## Structure Padding and Alignment

```c
struct test1 {
    char j;  // 1 byte
    int i;   // 4 bytes
};
// Size could be 5 (packed) or 8 (aligned)
// Alignment: int typically word-aligned for faster access

#pragma pack(1)  // Force byte alignment (non-portable)
```

## Initialization

```c
struct student s1;                    // Uninitialized
struct student s2 = {23, "pes", 99};  // Full init (order matters)
struct student s3 = {23, "pes"};      // Partial init (rest = 0)
struct student s5 = {.name="pes", .marks=45};  // Designated init
```

## Copying and Comparison

```c
struct test1 t1 = {23, 'w'};
struct test1 t2 = t1;  // Memberwise copy - separate memory

// No direct comparison operator
if (t1.i == t2.i && t1.ch == t2.ch)  // Manual field comparison
```

**Pointer fields in structures** create aliasing issues:
```c
struct What { int *p; int a; };
what_t x, y;
x.p = malloc(sizeof(int));
y = x;  // Aliasing! Both point to same memory
free(y.p);  // x.p now dangling
```

## Parameter Passing

```c
// Pass by value - copy made, changes don't affect original
void f1(struct test t) { strcpy(t.a, "pqrstuv"); }

// Pass by pointer - can modify original
void f2(struct test *p) { strcpy(p->a, "pqr"); }

// Pass by const pointer - read-only access
void f3(const struct test *p) { printf("%s\n", p->a); }
```

**Best practice**: Always pass structures by pointer (const if read-only).

## Returning Structures

```c
struct test f1(struct test t) {
    strcpy(t.a, "pqrstuv");
    return t;  // Returns copy via temporary
}
```

**DANGER**: Never return pointer to local variable (dangling pointer).

## Typedef

```c
typedef struct student student_t;  // Creates type name
student_t s1;  // Cleaner than 'struct student s1'
```

---

# Unit 1: Dynamic Memory Management

## Memory Model

- **Stack**: Automatic variables (created/destroyed with block)
- **Heap**: Dynamic memory (programmer-controlled)

## Core Functions

```c
#include <stdlib.h>

void* malloc(size_t size);      // Allocate, uninitialized
void* calloc(size_t n, size_t); // Allocate + zero-initialize
void* realloc(void* ptr, size_t); // Resize allocation
void free(void* ptr);           // Deallocate
```

## malloc Example

```c
int *p = (int*)malloc(sizeof(int));
if (p == NULL) { /* handle failure */ }
*p = 20;
free(p);  // p still holds old value (dangling), but memory freed
```

## Array on Heap

```c
int *p = (int*)malloc(sizeof(int) * 4);
p[0] = 11; *(p + 1) = 22;
free(p);  // Frees entire block
```

## Bookkeeping

`malloc` stores allocation size in hidden bookkeeping area. `free` uses this to know how much to deallocate.

**Critical rules:**
- Only `free` pointers returned by `malloc`
- Never `free(p + 1)` - no bookkeeping there
- Double-free = undefined behavior
- `free(NULL)` is safe (no-op)

## Common Issues

### Aliasing
```c
int *p = malloc(sizeof(int));
int *q = p;
free(q);  // OK - same pointer value
// p now dangling
```

### Memory Leak (Garbage in C)
```c
p = malloc(sizeof(int));
*p = 30;
p = malloc(sizeof(int));  // First block lost = garbage = memory leak
```

### Dangling Pointer
```c
p = malloc(sizeof(int));
int *q = p;
free(q);
// p and q now dangling - point to freed memory
printf("%d", *p);  // Undefined behavior!
```

### Dangling from Scope
```c
void foo() {
    int *p = malloc(sizeof(int));
    *p = 10;
}  // p dies, heap memory leaked
```

## calloc and realloc

```c
// calloc: allocate + zero-init
int *p = (int*)calloc(4, sizeof(int));  // 4 ints, all 0

// realloc: resize (may move memory)
int *q = (int*)realloc(p, 10000);
// q may != p; old values copied; new space uninitialized
// On shrink: excess values lost
```

## Structure Allocation

```c
struct What { int *p; int a; };
what_t x;
x.a = 100;
x.p = (int*)malloc(sizeof(int));
*(x.p) = 10000;

what_t y = x;  // Aliasing on pointer field!

// Case 1: y.p = x.p, free(y.p) → x.p dangling
// Case 2: y.p = malloc(...) after copy → breaks aliasing, safe
// Case 3: x.p = malloc(...) after copy → breaks aliasing, safe
// Case 4: x.p = NULL after malloc → memory leak!
```

---

# Unit 1: Abstract Data Types (ADT)

## Type Concept

A **type** defines:
- Legal values
- Operations on those values
- **NOT** how operations are implemented

```c
// int is a type - we know +, -, *, / work, but not HOW
// Car is a type - start(), stop(), accelerate(), brake()
```

## Abstract Data Type

**ADT** = Interface (what) + Implementation (how)
- Interface is **sacred** (cannot change)
- Implementation can change freely
- **Inversion of dependency**: Both client and implementer depend on interface

```c
// List ADT Interface
void create(list_t*);
void destroy(list_t*);
void insert(list_t*, int key);
void delete(list_t*, int key);
// ...

// Implementations:
// 1. Linked list
// 2. Array
```

## Data Structure

A data structure is an ADT with:
- Components arranged in specific way
- Efficient operations (time/space constrained)
- Multiple implementations possible for same interface

**Example**: Stack of tumblers
- Stacked vertically: space-efficient, single access
- Side by side: space-costly, parallel access
- Neither is "wrong" - depends on requirements

---

# Unit 1: Lists and Linked Lists

## List ADT

- Zero or more components
- Each has ordinal position
- **Sequential access** (no random/direct access)
- Insert/delete at known position: few operations

**Interface:**
```c
void init(list_t*);
void destroy(list_t*);
void insert(list_t*, int key);
void delete(list_t*, int key);
void traverse(list_t*);
```

## Linked List Implementation

### Self-Referential Structure

```c
struct node {
    int key_;
    struct node *next_;
};
typedef struct node node_t;
```

### Building a List

```c
node_t *p = (node_t*)malloc(sizeof(node_t));
p->key_ = 20;
p->next_ = (node_t*)malloc(sizeof(node_t));
p->next_->key_ = 40;
p->next_->next_ = (node_t*)malloc(sizeof(node_t));
p->next_->next_->key_ = 60;
p->next_->next_->next_ = NULL;
```

### Traversal (THE key statement)

```c
void disp(node_t* q) {
    while (q != NULL) {
        printf("%d ", q->key_);
        q = q->next_;  // Most important statement in data structures!
    }
}
```

### Freeing List

```c
void freelist(node_t* q) {
    node_t* r;
    while (q != NULL) {
        r = q->next_;  // Save next BEFORE freeing
        free(q);
        q = r;
    }
}
```

---

# Unit 1: Ordered Lists

## Insertion Cases

Four boundary conditions:
1. **Empty list**
2. **Insert at beginning**
3. **Insert in middle**
4. **Insert at end**

```c
void insert_list(mylist_t* ptr_list, int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->next_ = NULL;
    
    if (ptr_list->head == NULL) {  // Empty
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
        } else {  // Middle or end (same code!)
            temp->next_ = pres;
            prev->next_ = temp;
        }
    }
}
```

---

# Unit 1: List with Header Node

## Concept

Add a **dummy header node** at start:
- Empty list has header node (next = NULL)
- Eliminates special cases for empty list and insert at beginning
- Insertion code becomes simpler

```c
void init_list(mylist_t* ptr_list) {
    ptr_list->head_ = (node_t*)malloc(sizeof(node_t));
    ptr_list->head_->next_ = NULL;
}

void insert_list(mylist_t* ptr_list, int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->next_ = NULL;
    
    // Traverse from header
    node_t* prev = ptr_list->head_;
    node_t* pres = ptr_list->head_->next_;
    
    while (pres != NULL && pres->key_ < temp->key_) {
        prev = pres;
        pres = pres->next_;
    }
    
    // Same code for middle AND end!
    temp->next_ = pres;
    prev->next_ = temp;
}
```

---

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

# Unit 1: Stack Applications

## 1. Well-Formed Parentheses

```c
// Single type: ()
stack_t mystack; init_stack(&mystack);
while ((ch = *s++) != '\0') {
    if (ch == '(') push(&mystack, 'x');
    else if (ch == ')') {
        if (!is_empty(&mystack)) pop(&mystack);
        else is_valid = 0;
    }
}
if (is_valid && is_empty(&mystack))  // Well-formed
```

## 2. Well-Formed Brackets: (), [], {}

```c
// Push MATCHING closing bracket
if (ch == '(') push(&mystack, ')');
else if (ch == '[') push(&mystack, ']');
else if (ch == '{') push(&mystack, '}');
else if (ch == ')' || ch == ']' || ch == '}') {
    if (!is_empty(&mystack)) {
        if (ch != pop(&mystack)) is_valid = 0;
    } else is_valid = 0;
}
```

## 3. Postfix Expression Evaluation

```
Infix:    3 + 4        →  Postfix: 3 4 +
Infix:    5 * 6 + 7    →  Postfix: 5 6 * 7 +
Infix:    (3 + 4) * 5  →  Postfix: 3 4 + 5 *
```

**Algorithm:**
```c
// Stack of operands (int)
while ((ch = *s++) != '\0') {
    if (isdigit(ch)) {
        val = val * 10 + ch - '0';
        is_num = 1;
    } else if (ch == ' ' && is_num) {
        push(&mystack, val); val = 0; is_num = 0;
    } else if (is_operator(ch)) {
        val1 = pop(&mystack);  // Second operand
        val2 = pop(&mystack);  // First operand
        switch(ch) {
            case '+': push(&mystack, val2 + val1); break;
            case '-': push(&mystack, val2 - val1); break;
            case '*': push(&mystack, val2 * val1); break;
            case '/': push(&mystack, val2 / val1); break;
        }
    }
}
result = pop(&mystack);
```

## 4. Infix to Postfix Conversion

**Algorithm uses stack of operators:**
```
Input:  5 * 6 + 7 * 8
Output: 5 6 * 7 8 * +
```

```c
while ((ch = *s++) != '\0') {
    if (ch == ')') {
        while ((ch1 = pop(&mystack)) != '(') output ch1;
    }
    else if (is_operator(ch) || ch == '(') {
        if (is_empty(&mystack)) push(&mystack, ch);
        else {
            while (!is_empty(&mystack) && 
                   prec_in_str(ch) < prec_in_stack(peek(&mystack))) {
                output pop(&mystack);
            }
            push(&mystack, ch);
        }
    }
    else output operand ch;
}
while (!is_empty(&mystack)) output pop(&mystack);
```

**Precedence rules:**
- In string: `(` has highest, in stack: `(` has lowest
- Left-associative: pop when precedence equal
- Right-associative: push when precedence equal

---

# Unit 1: Skiplist and Multilist

## Skiplist

**Problem**: Searching in sorted linked list is O(n)

**Solution**: Multiple levels with "express lanes"

```
Level 2:  10 ──────────→ 40 ──────────→ 70 ─────→ 100
           ↓              ↓              ↓
Level 1:  10 ──→ 20 ──→ 40 ──→ 50 ──→ 70 ──→ 100
           ↓       ↓       ↓       ↓       ↓
Level 0:  10 → 20 → 30 → 40 → 50 → 60 → 70 → 80 → 90 → 100
```

**Search for 90:**
1. Level 2: 10 → 40 → 70 → (100 > 90, drop down)
2. Level 1: 70 → 100 (drop down)
3. Level 0: 70 → 80 → 90 (found!)

**Properties:**
- Bottom level = all elements
- Each higher level ≈ half nodes of level below
- Search/insert/delete: O(log n) expected
- Used in: Redis, LevelDB, concurrent data structures

## Multilist

**Concept**: One node participates in multiple lists

**Sparse Matrix Example:**
```
Row lists: Each row has list of non-zero elements
Col lists: Each column has list of non-zero elements
One physical node → appears in both row and column list
```

**Student-Course Example:**
- Student node → list of courses
- Course node → list of students
- Single enrollment node → in both lists

**Benefits:**
- Avoids duplicate data
- Single update point
- Multiple access paths

**Costs:**
- Complex pointer management
- Complex insertion/deletion