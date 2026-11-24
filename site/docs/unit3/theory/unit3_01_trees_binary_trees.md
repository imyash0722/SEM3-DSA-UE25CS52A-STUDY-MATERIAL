# Unit 3: Trees & Binary Trees

## 🌳 Trees - Fundamental Concepts

### What is a Tree?

> **Tree** = Non-linear, hierarchical data structure
> - **Acyclic**: No cycles
> - **Connected**: Path between any two nodes
> - **n nodes = n-1 edges**

### Tree Terminology (Genealogy + Botany)

| Genealogy Terms | Botany Terms | Structural Terms |
|-----------------|--------------|------------------|
| Parent | Root | Path |
| Child | Node | Level (root=0) |
| Sibling | Leaf | Height (max path to leaf) |
| Ancestor | Branch | Depth (path from root) |
| Descendant | Internal node | Degree (#children) |
| Grandparent | External node | |
| Uncle | | |

### Properties
- Adding edge → creates cycle
- Removing edge → disconnects tree
- Exactly one path between any two nodes

### Tree Visualization
```mermaid
graph TD
    A["Root (Level 0)"] --> B["Left Child (Level 1)"]
    A --> C["Right Child (Level 1)"]
    B --> D["Left Grandchild (Level 2)"]
    B --> E["Right Grandchild (Level 2)"]
    C --> F["Left Grandchild (Level 2)"]
    C --> G["Right Grandchild (Level 2)"]
    D --> H["Leaf (Level 3)"]
    D --> I["Leaf (Level 3)"]
    
    style A fill:#e1f5fe,stroke:#01579b,stroke-width:2px
    style B fill:#f3e5f5,stroke:#4a148c,stroke-width:2px
    style C fill:#f3e5f5,stroke:#4a148c,stroke-width:2px
    style H fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style I fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

---

## 🌲 Binary Trees

### Definition
> A **binary tree** is a tree where each node has **at most 2 children**, distinguished as **left** and **right**.

**Recursive Definition:**
- Empty tree, OR
- Root + left subtree (binary tree) + right subtree (binary tree)

### Binary Tree Structure
```mermaid
graph TD
    Root[Root Node] --> Left[Left Subtree]
    Root --> Right[Right Subtree]
    Left --> LL[Left-Left]
    Left --> LR[Left-Right]
    Right --> RL[Right-Left]
    Right --> RR[Right-Right]
    
    style Root fill:#ffebee,stroke:#c62828,stroke-width:3px
    style Left fill:#fff3e0,stroke:#e65100,stroke-width:2px
    style Right fill:#fff3e0,stroke:#e65100,stroke-width:2px
```

### Node Structure
```c
struct node {
    int key;
    struct node *left;
    struct node *right;
};
typedef struct node node_t;

struct tree {
    node_t *root;
};
typedef struct tree tree_t;
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Tree** | Hierarchical, n nodes = n-1 edges |
| **Binary Tree** | Max 2 children per node |
| **Node Structure** | key, left, right pointers |

---

*Next: [Binary Trees & BST →](./unit3_02_binary_trees_bst.md)*