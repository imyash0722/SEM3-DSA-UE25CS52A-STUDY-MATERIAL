# Unit 3: Binary Trees & BST

## 🌲 Binary Trees

### Definition
> A **binary tree** is a tree where each node has **at most 2 children**, distinguished as **left** and **right**.

**Recursive Definition:**
- Empty tree, OR
- Root + left subtree (binary tree) + right subtree (binary tree)

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

### Binary Tree Visualization
```mermaid
graph TD
    A[50] --> B[30]
    A --> C[70]
    B --> D[20]
    B --> E[40]
    C --> F[60]
    C --> G[80]
    D --> H[10]
    D --> I[25]
    E --> J[35]
    E --> K[45]
    F --> L[55]
    F --> M[65]
    G --> N[75]
    G --> O[85]
    
    style A fill:#ffebee,stroke:#c62828,stroke-width:3px
    style B fill:#fff3e0,stroke:#e65100,stroke-width:2px
    style C fill:#fff3e0,stroke:#e65100,stroke-width:2px
```

---

## 🔄 Tree Traversals - The Three Orders

### 1. Inorder (Left → Root → Right)
```c
void inorder(node_t *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
```
**Example:** D B E A C F

### Inorder Traversal Visualization
```mermaid
graph TD
    A[50] --> B[30]
    A --> C[70]
    B --> D[20]
    B --> E[40]
    C --> F[60]
    C --> G[80]
    
    %% Traversal order annotations
    D -.->|1st| Order1[1: 10]
    D -.->|2nd| Order2[2: 20]
    I -.->|3rd| Order3[3: 25]
    B -.->|4th| Order4[4: 30]
    J -.->|5th| Order5[5: 35]
    E -.->|6th| Order6[6: 40]
    K -.->|7th| Order7[7: 45]
    A -.->|8th| Order8[8: 50]
    L -.->|9th| Order9[9: 55]
    F -.->|10th| Order10[10: 60]
    M -.->|11th| Order11[11: 65]
    C -.->|12th| Order12[12: 70]
    N -.->|13th| Order13[13: 75]
    G -.->|14th| Order14[14: 80]
    O -.->|15th| Order15[15: 85]
    
    style A fill:#ffebee,stroke:#c62828,stroke-width:3px
```

### 2. Preorder (Root → Left → Right)
```c
void preorder(node_t *root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
```
**Example:** A B D E C F

### Preorder Traversal Visualization
```mermaid
graph TD
    Root[50] --> L[30]
    Root --> R[70]
    L --> LL[20]
    L --> LR[40]
    R --> RL[60]
    R --> RR[80]
    
    %% Preorder: Root, Left, Right
    Root -.->|1st| O1[1: 50]
    L -.->|2nd| O2[2: 30]
    LL -.->|3rd| O3[3: 20]
    LR -.->|4th| O4[4: 40]
    R -.->|5th| O5[5: 70]
    RL -.->|6th| O6[6: 60]
    RR -.->|7th| O7[7: 80]
    
    style Root fill:#ffebee,stroke:#c62828,stroke-width:3px
```

### 3. Postorder (Left → Right → Root)
```c
void postorder(node_t *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}
```
**Example:** D E B F C A

### When to Use Which?
| Traversal | Use Case |
|-----------|----------|
| **Inorder** | BST gives sorted order |
| **Preorder** | Copy tree, serialize |
| **Postorder** | Delete tree, evaluate expressions |

---

## 🔍 Binary Search Tree (BST)

### BST Property
> For every node: **Left subtree keys < Node key < Right subtree keys**

### BST Property Visualization
```mermaid
graph TD
    A[50] --> B[30]
    A --> C[70]
    B --> D[20]
    B --> E[40]
    C --> F[60]
    C --> G[80]
    
    classDef lessThan fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    classDef greaterThan fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    classDef node fill:#fff3e0,stroke:#e65100,stroke-width:2px
    
    class B,D,E lessThan
    class C,F,G greaterThan
    class A node
    
    Less[All < 50] -.-> B
    Greater[All > 50] -.-> C
```

### Operations - All O(h) where h = height

#### Search
```c
node_t* search(node_t *root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}
```

#### Insert
```c
node_t* insert(node_t *root, int key) {
    if (!root) {
        node_t *n = malloc(sizeof(node_t));
        n->key = key; n->left = n->right = NULL;
        return n;
    }
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}
```

### BST Insert Visualization
```mermaid
graph TD
    A[50] --> B[30]
    A --> C[70]
    B --> D[20]
    B --> E[40]
    C --> F[60]
    C --> G[80]
    
    %% Insert 25
    D -.->|Insert 25| New[25]
    D -.->|Insert 55| New2[55]
    
    style A fill:#fff3e0,stroke:#e65100,stroke-width:2px
    style New fill:#e8f5e9,stroke:#2e7d32,stroke-width:3px,stroke-dasharray: 5 5
    style New2 fill:#e8f5e9,stroke:#2e7d32,stroke-width:3px,stroke-dasharray: 5 5
```

#### Delete (4 Cases)
```c
node_t* delete(node_t *root, int key) {
    if (!root) return NULL;
    
    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {  // Found!
        // Case 1: Leaf
        if (!root->left && !root->right) {
            free(root); return NULL;
        }
        // Case 2: Only right child
        if (!root->left) {
            node_t *t = root->right; free(root); return t;
        }
        // Case 3: Only left child
        if (!root->right) {
            node_t *t = root->left; free(root); return t;
        }
        // Case 4: Two children - use inorder successor
        node_t *succ = root->right;
        while (succ->left) succ = succ->left;
        root->key = succ->key;
        root->right = delete(root->right, succ->key);
    }
    return root;
}
```

**Case 4 Explanation:** Replace with inorder successor (smallest in right subtree), then delete that successor.

### BST Delete Cases Visualization
```mermaid
graph TD
    subgraph Case1[Case 1: Leaf Node]
        C1A[Parent] --> C1B[Leaf to Delete]
        style C1B fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    end
    
    subgraph Case2[Case 2: One Child (Right)]
        C2A[Parent] --> C2B[Node to Delete]
        C2B --> C2C[Child]
        style C2B fill:#ffcdd2,stroke:#c62828,stroke-width:2px
        C2A -.->|Replace| C2C
    end
    
    subgraph Case3[Case 3: One Child (Left)]
        C3A[Parent] --> C3B[Node to Delete]
        C3B --> C3C[Child]
        style C3B fill:#ffcdd2,stroke:#c62828,stroke-width:2px
        C3A -.->|Replace| C3C
    end
    
    subgraph Case4[Case 4: Two Children]
        C4A[Node to Delete] --> C4B[Left Child]
        C4A --> C4C[Right Child]
        C4C --> C4D[Inorder Successor<br/>(Min of Right Subtree)]
        C4A -.->|Replace with| C4D
        C4C -.->|Remove| C4D
        style C4A fill:#ffcdd2,stroke:#c62828,stroke-width:2px
        style C4D fill:#c8e6c9,stroke:#2e7d32,stroke-width:2px
    end
```

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Binary Tree** | Max 2 children per node |
| **Traversals** | In/Pre/Post order - different uses |
| **BST** | Left < Root < Right, O(h) ops |
| **BST Delete** | 4 cases - leaf, one child, two children |

---

*Next: [Array Implementation of BST →](./unit3_03_bst_array_implementation.md)*