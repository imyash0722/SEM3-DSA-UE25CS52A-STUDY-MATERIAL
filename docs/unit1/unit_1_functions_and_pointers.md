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