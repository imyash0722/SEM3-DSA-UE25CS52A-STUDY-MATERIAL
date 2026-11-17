# Unit 3: Splay Trees

## 🎯 Splay Trees (Self-Adjusting)

### Concept
- No balance factors stored (memory efficient!)
- **Splay**: Move accessed node to root via rotations
- **Amortized** O(log n) for sequence of operations

### Splaying Cases
1. **Zig**: Node is child of root → single rotation
2. **Zig-Zig**: Node & parent same side → two same-direction rotations
3. **Zig-Zag**: Node & parent opposite sides → two opposite rotations

### Zig Case (Node is child of root)
```mermaid
graph TD
    subgraph Before[Before: Zig]
        P[Parent/Root] --> X[Node]
    end
    
    ArrowZig -.->|Rotate| AfterZig
    
    subgraph After[After: Node at Root]
        X2[X: Root] --> P2[Parent]
    end
    
    Before -.->|Single Rotation| After
    
    style X fill:#ffebee,stroke:#c62828,stroke-width:2px
    style X2 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### Zig-Zig Case (Node & parent same side - both left)
```mermaid
graph TD
    subgraph ZigZigBefore[Before: Zig-Zig]
        G[Grandparent] --> P[Parent]
        P --> X[Node]
    end
    
    ZigZigStep1 -.->|1st Rotation: Grandparent| ZigZigMid
    
    subgraph ZigZigMid[After 1st Rotation]
        P2[Parent] --> X2[Node]
        P2 --> G2[Grandparent]
    end
    
    ZigZigStep2 -.->|2nd Rotation: Parent| ZigZigAfter
    
    subgraph ZigZigAfter[After: Node at Root]
        X3[X: Root] --> P3[Parent]
        P3 --> G3[Grandparent]
    end
    
    ZigZigBefore -.->|Step 1| ZigZigMid -.->|Step 2| ZigZigAfter
    
    style X fill:#ffebee,stroke:#c62828,stroke-width:2px
    style X3 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### Zig-Zag Case (Node & parent opposite sides)
```mermaid
graph TD
    subgraph ZigZagBefore[Before: Zig-Zag]
        G[Grandparent] --> P[Parent]
        P --> X[Node]
    end
    
    ZigZagStep1 -.->|1st Rotation: Parent| ZigZagMid
    
    subgraph ZigZagMid[After 1st Rotation]
        G2[Grandparent] --> X2[Node]
        X2 --> P2[Parent]
    end
    
    ZigZagStep2 -.->|2nd Rotation: Grandparent| ZigZagAfter
    
    subgraph ZigZagAfter[After: Node at Root]
        X3[X: Root] --> G3[Grandparent]
        G3 --> P3[Parent]
    end
    
    ZigZagBefore -.->|Step 1| ZigZagMid -.->|Step 2| ZigZagAfter
    
    style X fill:#ffebee,stroke:#c62828,stroke-width:2px
    style X3 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### Splaying Decision Flowchart
```mermaid
flowchart TD
    Start([Access Node]) --> AtRoot{Node is Root?}
    AtRoot -- Yes --> Done[Done]
    AtRoot -- No --> ParentOfRoot{Parent is Root?}
    ParentOfRoot -- Yes --> Zig[Zig: Single Rotation]
    ParentOfRoot -- No --> CheckSides{Same Side?}
    CheckSides -- Yes --> ZigZig[Zig-Zig: Two Same Rotations]
    CheckSides -- No --> ZigZag[Zig-Zag: Two Opposite Rotations]
    
    Zig --> Done2[Done]
    ZigZig --> Done2
    ZigZag --> Done2
    Done2 --> Done
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Done fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### Applications
- Caches (recently accessed → root)
- Memory allocators
- Network routers (frequent IPs)

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Splay** | Self-adjusting, amortized O(log n) |
| **No BF** | No balance factors stored |
| **Splaying** | Move accessed to root |

---

*Next: [Graphs →](./unit3_09_graphs.md)*