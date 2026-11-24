# Unit 3: BST Array Implementation

## 📊 BST Implementation 2: Array-Based

### Structure
```c
#define MAXSIZE 200

struct node {
    int key;
    int left;   // Index of left child (-1 = null)
    int right;  // Index of right child
};
typedef struct node node_t;

struct tree {
    int root;       // Index of root (-1 = empty)
    int count;      // Number of nodes
    node_t elem[MAXSIZE];
};
typedef struct tree tree_t;
```

### Array vs Pointer Comparison
```mermaid
graph LR
    subgraph Pointer[Pointer-Based BST]
        P1[Node*] --> P2[Node*]
        P1 --> P3[Node*]
        style P1 fill:#e3f2fd,stroke:#1565c0
        style P2 fill:#e3f2fd,stroke:#1565c0
        style P3 fill:#e3f2fd,stroke:#1565c0
    end
    
    subgraph Array[Array-Based BST]
        A1[Index 0] --> A2[Index 1]
        A1 --> A3[Index 3]
        A2 --> A4[Index 2]
        A2 -.->|empty| A5[Index -1]
        style A1 fill:#fff3e0,stroke:#e65100
        style A2 fill:#fff3e0,stroke:#e65100
        style A3 fill:#fff3e0,stroke:#e65100
        style A4 fill:#fff3e0,stroke:#e65100
        style A5 fill:#ffcdd2,stroke:#c62828
    end
```

### Array Representation Example
```mermaid
graph TD
    subgraph Array["elem[] Array"]
        I0["Index 0: key=50, left=1, right=2"]
        I1["Index 1: key=30, left=3, right=4"]
        I2["Index 2: key=70, left=5, right=6"]
        I3["Index 3: key=20, left=-1, right=-1"]
        I4["Index 4: key=40, left=-1, right=-1"]
        I5["Index 5: key=60, left=-1, right=-1"]
        I6["Index 6: key=80, left=-1, right=-1"]
    end
    
    Root["root=0"] --> I0
    I0 --> I1
    I0 --> I2
    I1 --> I3
    I1 --> I4
    I2 --> I5
    I2 --> I6
    
    style Root fill:#ffebee,stroke:#c62828,stroke-width:2px
    style I0 fill:#fff3e0,stroke:#e65100
```

### Key Differences from Dynamic Version
- Uses **indices** instead of pointers
- `left`/`right` store array indices (-1 = null)
- `root` stores index of root node
- Copy tree = memcpy entire array!

### Insert
```c
int insert_rec(node_t e[], int root, int new_idx) {
    if (root == -1) return new_idx;
    if (e[root].key > e[new_idx].key)
        e[root].left = insert_rec(e, e[root].left, new_idx);
    else
        e[root].right = insert_rec(e, e[root].right, new_idx);
    return root;
}

void insert(tree_t *t, int key) {
    int idx = t->count++;
    t->elem[idx].key = key;
    t->elem[idx].left = t->elem[idx].right = -1;
    t->root = insert_rec(t->elem, t->root, idx);
}
```

### Insert Flow Visualization
```mermaid
flowchart TD
    Start(["Start: Insert Key"]) --> CheckEmpty{"Root == -1?"}
    CheckEmpty -- Yes --> SetRoot["Root = new_idx"]
    CheckEmpty -- No --> Compare{"Key > Current?"}
    Compare -- Yes --> GoRight["Go Right: insert_rec(right, new_idx)"]
    Compare -- No --> GoLeft["Go Left: insert_rec(left, new_idx)"]
    GoRight --> Recurse["Recursive Call"]
    GoLeft --> Recurse
    Recurse --> CheckEmpty
    SetRoot --> End(["End"])
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style End fill:#ffebee,stroke:#c62828
    style SetRoot fill:#e3f2fd,stroke:#1565c0
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Array BST** | Uses indices instead of pointers |
| **left/right** | Store array indices (-1 = null) |
| **root** | Stores index of root node |
| **Copy tree** | memcpy entire array! |

---

*Next: [Expression Trees →](./unit3_04_expression_trees.md)*