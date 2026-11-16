# Unit 1: Singly Linked List - Node Structure & Creation

## 🔗 Singly Linked List - Complete Walkthrough

### What is a Linked List?

A **linked list** is a linear data structure where:
- Elements (nodes) are NOT stored in contiguous memory
- Each node contains **data** and a **pointer (link)** to the next node
- Head/start pointer points to the first node
- Last node's link contains `NULL`

### Visual Representation
```
head → [10|•] → [20|•] → [30|•] → NULL
        │       │       │
      data    data    data
       10      20      30
```

---

## 📋 Node Structure

```c
struct node {
    int data;
    struct node *link;
};
typedef struct node NODE;
```

### Structure Breakdown:
- `data` - The actual value stored (can be any type)
- `link` - Pointer to the next node (self-referential structure)
- `NODE` - Typedef for cleaner code

---

## 🛠️ Creating a Node

### Step-by-Step:
```c
// 1. Allocate memory dynamically
NODE *temp = (NODE*)malloc(sizeof(NODE));
if (temp == NULL) { 
    printf("Memory full\n"); 
    exit(1); 
}

// 2. Set data part
temp->data = user_value;

// 3. Set link part to NULL (will be updated during insertion)
temp->link = NULL;
```

### Helper Function (Recommended)
```c
NODE *create_node(int data) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));
    if (!temp) { 
        printf("Memory full\n"); 
        exit(1); 
    }
    temp->data = data;
    temp->link = NULL;
    return temp;
}
```

---

## 🧠 Understanding Pointers in Linked Lists

### Single Pointer (Singly Linked List)
```c
struct node {
    int data;
    struct node *next;  // Only forward pointer
};
```

### Double Pointer (For Head Modification)
```c
void insert_front(NODE **head, int value);
// Call as: insert_front(&head, 10);
// **head allows modifying the actual head pointer
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Linked List** | Dynamic size, non-contiguous, pointer-based |
| **Node** | Data + Link to next node |
| **Self-referential** | Structure contains pointer to same type |
| **malloc** | Dynamic allocation for each node |
| **NULL** | End of list marker |

---

## 🧪 Self-Test Questions

1. Why is the link field a pointer to the same structure type?
2. What happens if you forget to set `link = NULL` when creating a node?
3. Why do we use `NODE **head` in insertion functions?
4. What is the difference between `node->data` and `(*node).data`?

---

*Next: [Singly Linked List - Insertion Operations →](./unit1_05_sll_insertion.md)*