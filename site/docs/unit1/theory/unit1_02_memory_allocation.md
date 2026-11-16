# Unit 1: Memory Allocation in C

## 💾 Memory Allocation in C

### Static Memory Allocation
- **Allocated by compiler** at compile time
- Exact size and type must be known at compile time
- Memory allocated in **stack area**
- Examples: `int b; int c[10];`

**Disadvantages:**
- Size cannot be altered at runtime
- May lead to under/over utilization of memory
- Memory cannot be deleted explicitly
- Only useful when data size is fixed and known beforehand

### Dynamic Memory Allocation
- Memory allocated and released **during program execution**
- Operates at low level
- Functions defined in `<stdlib.h>`

| Function | Purpose |
|----------|---------|
| `malloc(size)` | Allocate memory (uninitialized) |
| `calloc(n, size)` | Allocate memory (zero-initialized) |
| `realloc(ptr, new_size)` | Resize allocated memory |
| `free(ptr)` | Release allocated memory |

---

## 🔧 Dynamic Memory Functions - Deep Dive

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

**Critical Concepts:**
- **Dangling Pointer**: Pointer to memory that has been freed
- **Memory Leak**: Allocated memory with no pointer to it (cannot be freed)

```c
// DANGEROUS - Dangling pointer
int *p = malloc(sizeof(int));
free(p);
// p now dangles - points to freed memory!
// *p = 10; // UNDEFINED BEHAVIOR!

// DANGEROUS - Memory leak
int *p = malloc(sizeof(int));
*p = 30;
p = malloc(sizeof(int)); // First block lost forever!
```

---

## ⚠️ Common Pitfalls & Best Practices

### Dangling Pointer Prevention
```c
int *p = malloc(sizeof(int));
*p = 100;
free(p);
p = NULL;  // ALWAYS set to NULL after free!
```

### Memory Leak Prevention
```c
// BAD - Memory leak
int *leak = malloc(sizeof(int));
leak = malloc(sizeof(int));  // First block lost!

// GOOD - Free before reassign
int *good = malloc(sizeof(int));
*good = 42;
free(good);  // Free first!
good = malloc(sizeof(int));
*good = 84;
free(good);
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Static Allocation** | Compile-time, stack, fixed size |
| **Dynamic Allocation** | Runtime, heap, flexible size |
| **malloc** | Uninitialized memory |
| **calloc** | Zero-initialized memory |
| **realloc** | Resize existing allocation |
| **free** | Release memory |
| **Dangling Pointer** | Pointer to freed memory - SET TO NULL! |
| **Memory Leak** | Lost allocated memory - ALWAYS FREE! |

---

## 🧪 Self-Test Questions

1. What is the difference between malloc and calloc?
2. What happens if you free a pointer twice?
3. Why should you set a pointer to NULL after free()?
4. What is a memory leak and how to prevent it?
5. When would you use realloc()?

---

*Next: [Dynamic Memory Functions Deep Dive →](./unit1_03_dynamic_memory_functions.md)*