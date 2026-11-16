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