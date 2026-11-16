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

### 4 Rotation Cases

| Case | Pattern | Rotation |
|------|---------|----------|
| **LL** | Left-Left | Single Right |
| **RR** | Right-Right | Single Left |
| **LR** | Left-Right | Left then Right |
| **RL** | Right-Left | Right then Left |

**Memory Trick:** Same direction → Single rotation; Opposite → Double rotation

### Right Rotation (LL Case)
```
    X               Y
   / \             / \
  Y   T4    →     Z   X
 / \                 / \
Z  T3               T3 T4
/ \
T1 T2
```

### Left Rotation (RR Case)
```
X                     Y
 \                   / \
  Y        →        X   Z
   \               / \ / \
    Z             T1 T2 T3 T4
   / \
  T3 T4
```

### Double Rotations
```
LR Case:          RL Case:
    X                 X
   / \                \
  Y  T4    →    Z    T4   →      Z
 / \              / \         / \
T1  Z            Y  T3       X   Y
   / \          / \         / \ / \
  T2 T3        T1 T2       T1 T2 T3 T4
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