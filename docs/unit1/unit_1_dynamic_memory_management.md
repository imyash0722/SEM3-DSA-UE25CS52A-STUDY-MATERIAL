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