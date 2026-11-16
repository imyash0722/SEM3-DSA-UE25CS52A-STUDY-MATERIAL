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