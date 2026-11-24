# Unit 3: Threaded Binary Trees

## 🧵 Threaded Binary Trees

### Problem
- n nodes → n-1 edges (structural pointers)
- 2n pointer fields → n+1 NULL pointers **wasted!**

### Solution: Threads
- Replace NULL pointers with **threads** to inorder predecessor/successor
- `lthread = 1` → left is thread (not structural)
- `rthread = 1` → right is thread

### Structure
```c
struct node {
    int key;
    struct node *left, *right;
    int lthread, rthread;  // 1 = thread, 0 = structural
};
```

### Threaded Tree Visualization
```mermaid
graph TD
    A[40] --> B[20]
    A --> C[60]
    B --> D[10]
    B --> E[30]
    C --> F[50]
    C --> G[70]
    
    %% Right Threads (Inorder Successors: 10->20, 30->40, 50->60)
    D -.->|Right Thread| B
    E -.->|Right Thread| A
    F -.->|Right Thread| C
    
    %% Left Threads (Inorder Predecessors: 30<-20, 50<-40, 70<-60)
    E -.->|Left Thread| B
    F -.->|Left Thread| A
    G -.->|Left Thread| C
    
    style A fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style B fill:#fff3e0,stroke:#e65100
    style C fill:#fff3e0,stroke:#e65100
```

### Thread Types Visualization
```mermaid
graph LR
    subgraph Structural[Structural Pointers]
        S1[Node] --> S2[Left Child]
        S1 --> S3[Right Child]
        style S1 fill:#e3f2fd,stroke:#1565c0
        style S2 fill:#e3f2fd,stroke:#1565c0
        style S3 fill:#e3f2fd,stroke:#1565c0
    end
    
    subgraph Threads[Thread Pointers]
        T1[Node] -.-> T2[Inorder Predecessor]
        T1 -.-> T3[Inorder Successor]
        style T1 fill:#fff3e0,stroke:#e65100
        style T2 fill:#fff3e0,stroke:#e65100
        style T3 fill:#fff3e0,stroke:#e65100
    end
```

### Inorder Traversal (Iterative - No Recursion!)
```c
node_t* leftmost(node_t *n) {
    if (!n) return NULL;
    while (n->lthread == 0) n = n->left;  // Follow structural
    return n;
}

void inorder(node_t *root) {
    node_t *curr = leftmost(root);
    while (curr) {
        printf("%d ", curr->key);
        if (curr->rthread == 1)
            curr = curr->right;      // Thread to successor
        else
            curr = leftmost(curr->right);  // Structural right
    }
}
```

### Inorder Traversal Flow
```mermaid
flowchart TD
    Start(["Start"]) --> LM["leftmost(root)"]
    LM --> Loop{"Current != NULL?"}
    Loop -- No --> End(["End"])
    Loop -- Yes --> Print["Print curr->key"]
    Print --> Check{"curr->rthread == 1?"}
    Check -- Yes --> Thread["curr = curr->right"]
    Check -- No --> Structural["curr = leftmost(curr->right)"]
    Thread --> Loop
    Structural --> Loop
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style End fill:#ffebee,stroke:#c62828
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Threaded Tree** | Threads replace NULL, O(1) successor |
| **lthread/rthread** | 1 = thread, 0 = structural |
| **Inorder** | Iterative, no recursion needed |

---

*Next: [Heaps →](./unit3_06_heaps.md)*