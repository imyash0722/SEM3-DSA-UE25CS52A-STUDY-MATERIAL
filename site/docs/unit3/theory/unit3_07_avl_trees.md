# Unit 3: AVL Trees

## ⚖️ AVL Trees (Balanced BST)

### Problem
- BST can become skewed → O(n) search
- Need **height-balanced** tree

### AVL Property
> For every node: |height(left) - height(right)| ≤ 1

**Balance Factor (BF)** = height(left) - height(right)
- BF ∈ {-1, 0, 1} → Balanced
- BF = +2 → Left heavy
- BF = -2 → Right heavy

### AVL Balance Factor Visualization
```mermaid
graph TD
    Balanced[BF = 0<br/>Balanced] --> LeftHeavy[BF = +1<br/>Left Heavy]
    Balanced --> RightHeavy[BF = -1<br/>Right Heavy]
    LeftHeavy --> LeftHeavy2[BF = +2<br/>Unbalanced!]
    RightHeavy --> RightHeavy2[BF = -2<br/>Unbalanced!]
    
    style Balanced fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style LeftHeavy fill:#fff3e0,stroke:#e65100
    style RightHeavy fill:#fff3e0,stroke:#e65100
    style LeftHeavy2 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    style RightHeavy2 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
```

---

## 🔄 4 Rotation Cases

| Case | Pattern | Rotation |
|------|---------|----------|
| **LL** | Left-Left | Single Right |
| **RR** | Right-Right | Single Left |
| **LR** | Left-Right | Left then Right |
| **RL** | Right-Left | Right then Left |

**Memory Trick:** Same direction → Single rotation; Opposite → Double rotation

### LL Case - Single Right Rotation
```mermaid
graph TD
    subgraph Before[Before: LL Case]
        X1[X: BF=+2] --> Y1[Y: BF=+1]
        X1 --> T41[T4]
        Y1 --> Z1[Z: BF=0]
        Y1 --> T31[T3]
        Z1 --> T11[T1]
        Z1 --> T21[T2]
    end
    
    Arrow1 -.->|Right Rotation| Arrow2
    
    subgraph After[After: Balanced]
        Y2[Y: BF=0] --> Z2[Z: BF=0]
        Y2 --> X2[X: BF=0]
        Z2 --> T12[T1]
        Z2 --> T22[T2]
        X2 --> T32[T3]
        X2 --> T42[T4]
    end
    
    Before -.->|Right Rotate| After
    
    style X1 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    style Y2 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### RR Case - Single Left Rotation
```mermaid
graph TD
    subgraph BeforeRR[Before: RR Case]
        X1[X: BF=-2] --> Y1[Y: BF=-1]
        Y1 --> Z1[Z: BF=0]
    end
    
    ArrowRR -.->|Left Rotation| ArrowRR2
    
    subgraph AfterRR[After: Balanced]
        Y2[Y: BF=0] --> X2[X: BF=0]
        Y2 --> Z2[Z: BF=0]
    end
    
    BeforeRR -.->|Left Rotate| AfterRR
    
    style X1 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    style Y2 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### LR Case - Double Rotation (Left then Right)
```mermaid
graph TD
    subgraph LRBefore[Before: LR Case]
        X1[X: BF=+2] --> Y1[Y: BF=-1]
        X1 --> T41[T4]
        Y1 --> T11[T1]
        Y1 --> Z1[Z: BF=0]
        Z1 --> T21[T2]
        Z1 --> T31[T3]
    end
    
    ArrowLR1 -.->|Left Rotate on Y| LRMid
    
    subgraph LRMid[After Left Rotate]
        X2[X: BF=+2] --> Z2[Z: BF=+1]
        X2 --> T42[T4]
        Z2 --> T22[T2]
        Z2 --> T32[T3]
        Z2 --> Y2[Y: BF=0]
        Y2 --> T12[T1]
    end
    
    ArrowLR2 -.->|Right Rotate on X| LRAfter
    
    subgraph LRAfter[After: Balanced]
        Z3[Z: BF=0] --> Y3[Y: BF=0]
        Z3 --> X3[X: BF=0]
        Y3 --> T13[T1]
        Y3 --> T23[T2]
        X3 --> T33[T3]
        X3 --> T43[T4]
    end
    
    LRBefore -.->|Step 1: Left| LRMid -.->|Step 2: Right| LRAfter
    
    style X1 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    style Z3 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### RL Case - Double Rotation (Right then Left)
```mermaid
graph TD
    subgraph RLBefore[Before: RL Case]
        X1[X: BF=-2] --> Y1[Y: BF=+1]
        Y1 --> T11[T1]
        Y1 --> Z1[Z: BF=0]
        Z1 --> T21[T2]
        Z1 --> T31[T3]
        X1 --> T41[T4]
    end
    
    ArrowRL1 -.->|Right Rotate on Y| RLMid
    
    subgraph RLMid[After Right Rotate]
        X2[X: BF=-2] --> Z2[Z: BF=-1]
        X2 --> T42[T4]
        Z2 --> T22[T2]
        Z2 --> T32[T3]
        Z2 --> Y2[Y: BF=0]
        Y2 --> T12[T1]
    end
    
    ArrowRL2 -.->|Left Rotate on X| RLAfter
    
    subgraph RLAfter[After: Balanced]
        Z3[Z: BF=0] --> X3[X: BF=0]
        Z3 --> Y3[Y: BF=0]
        X3 --> T13[T1]
        X3 --> T23[T2]
        Y3 --> T33[T3]
        Y3 --> T43[T4]
    end
    
    RLBefore -.->|Step 1: Right| RLMid -.->|Step 2: Left| RLAfter
    
    style X1 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    style Z3 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### Rotation Decision Flowchart
```mermaid
flowchart TD
    Start([Node Unbalanced]) --> CheckBF{BF of Unbalanced Node}
    CheckBF -- +2 (Left Heavy) --> CheckChild{Child BF}
    CheckBF -- -2 (Right Heavy) --> CheckChild2{Child BF}
    CheckChild -- +1 (Left) --> LL[LL Case: Right Rotate]
    CheckChild -- -1 (Right) --> LR[LR Case: Left then Right]
    CheckChild2 -- -1 (Right) --> RR[RR Case: Left Rotate]
    CheckChild2 -- +1 (Left) --> RL[RL Case: Right then Left]
    
    LL --> Balanced[Balanced]
    LR --> Balanced
    RR --> Balanced
    RL --> Balanced
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Balanced fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **AVL** | Height-balanced, 4 rotation cases |
| **BF** | height(left) - height(right) |
| **Rotations** | Same direction = single, Opposite = double |

---

*Next: [Splay Trees →](./unit3_08_splay_trees.md)*