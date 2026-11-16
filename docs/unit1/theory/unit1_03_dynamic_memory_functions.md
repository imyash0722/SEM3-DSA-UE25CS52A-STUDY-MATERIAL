# Unit 1: Dynamic Memory Functions - Deep Dive & Anchor Programs

## 🔧 Dynamic Memory Functions - Complete Reference

### malloc()
```c
void *malloc(size_t size);
```
- Takes number of bytes to allocate
- Use `sizeof` to determine size of a type
- Returns `void*` (can be assigned to any pointer)
- Returns `NULL` if no memory available

**Example: Allocate space for 100 integers**
```c
int *p;
if ((p = (int*)malloc(100 * sizeof(int))) == NULL) {
    printf("out of memory\n");
    exit(1);
}
// Access as p[0], p[1], ..., p[99] or *p, *(p+1), ...
```

### calloc()
```c
void *calloc(size_t nitem, size_t size);
```
- Allocates memory and **initializes to zero**
- Requires two arguments: number of items and size of each item

**Example:**
```c
int *p = (int*)calloc(100, sizeof(int)); // 100 ints, all zeros
```

### realloc()
```c
void *realloc(void *ptr, size_t new_size);
```
- Resizes previously allocated block
- Two arguments: pointer to existing block, new size

**Example:**
```c
int *ip = (int*)malloc(100 * sizeof(int));
// ... later need twice as much ...
ip = (int*)realloc(ip, 200 * sizeof(int));
```

### free()
```c
void free(void *ptr);
```
- Deallocates memory allocated by malloc/calloc/realloc
- Takes a pointer as argument

---

## 🎯 Anchor Programs

### Program 1: Dynamic Memory Demo
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

**Output:**
```
=== Dynamic Memory Demo ===

1. malloc():
Allocated 5 ints: 10 20 30 40 50

2. calloc():
Zero-initialized: 0 0 0 0 0

3. realloc():
Before realloc: 1 2 3
After realloc:  1 2 3 4 5 6

4. Structure allocation:
Student: Alice, Roll: 101, Marks: 95.5

=== Dangling Pointer Demo ===
Before free: *dang = 100

=== Memory Leak Demo ===
No leaks!
```

---

## 🔗 Pointer Arithmetic with Dynamic Memory

```c
int *p = (int*)malloc(5 * sizeof(int));
// p[0] = 10; p[1] = 20; ...
// Equivalent:
*p = 10;           // p[0]
*(p + 1) = 20;     // p[1]
*(p + 2) = 30;     // p[2]
```

---

## 📝 Key Takeaways

| Function | Use Case | Returns |
|----------|----------|---------|
| `malloc` | Uninitialized memory | `void*` or `NULL` |
| `calloc` | Zero-initialized memory | `void*` or `NULL` |
| `realloc` | Resize allocation | `void*` or `NULL` |
| `free` | Release memory | `void` |

### Best Practices:
1. **Always check return value** for NULL
2. **Set pointer to NULL** after free()
3. **Free in reverse order** of allocation
4. **Use sizeof()** for portability
4. **Free before reassigning** pointer

---

## 🧪 Self-Test Questions

1. What is the difference between `malloc(10)` and `calloc(10, sizeof(int))`?
2. If `realloc` fails, what happens to the original memory?
3. Why is `free(NULL)` safe?
4. How do you allocate a 2D array dynamically?

---

*Next: [Singly Linked List - Node Structure & Creation →](./unit1_04_sll_node_structure.md)*