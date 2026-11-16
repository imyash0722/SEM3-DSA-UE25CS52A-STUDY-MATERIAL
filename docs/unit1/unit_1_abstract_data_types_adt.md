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