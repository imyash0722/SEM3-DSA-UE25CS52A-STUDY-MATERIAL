## 3.7 AVL Trees


### Problem with BST
- Can become skewed (degenerate to list)
- Search becomes O(n) instead of O(log n)

### AVL Property
**Height-balanced**: For every node, |height(left) - height(right)| ≤ 1

**Balance Factor**: BF = height(left) - height(right)
- BF ∈ {-1, 0, 1} for balanced
- BF = +2 → left-heavy
- BF = -2 → right-heavy

### Rotations (4 Cases)

#### LL (Left-Left) → Right Rotation
```
    X               Y
   / \             / \
  Y   T4    →     Z   X
 / \                 / \
Z  T3               T3 T4
/ \
T1 T2
```

#### RR (Right-Right) → Left Rotation
```
X                     Y
 \                   / \
  Y        →        X   Z
   \               / \ / \
    Z             T1 T2 T3 T4
   / \
  T3 T4
```

#### LR (Left-Right) → Left then Right
```
    X               X               Z
   / \             / \             / \
  Y  T4     →     Z  T4    →      Y   X
 / \             / \             / \ / \
T1  Z           Y  T3           T1 T2 T3 T4
   / \         / \
  T2 T3       T1 T2
```

#### RL (Right-Left) → Right then Left
```
X                   X                   Z
 \                 \                   / \
  Y        →        Z        →        X   Y
 / \                 \               / \ / \
T1  Z                Y              T1 T2 T3 T4
   / \                \
  T2 T3               T3
```

### Memory Rule
- **Same direction** (LL, RR) → **Single rotation**
- **Opposite directions** (LR, RL) → **Double rotation**

### Insertion
```c
node_t* insert_avl(node_t* root, int key, int* taller) {
    if (!root) {
        root = create_node(key);
        *taller = 1;
    } else if (key < root->key_) {
        root->left_ = insert_avl(root->left_, key, taller);
        if (*taller) {
            switch (root->bf_) {
                case -1: root->bf_ = 0; *taller = 0; break;
                case 0: root->bf_ = 1; break;
                case 1: root = rotate_ll_or_lr(root); *taller = 0; break;
            }
        }
    } else {
        root->right_ = insert_avl(root->right_, key, taller);
        if (*taller) {
            switch (root->bf_) {
                case 1: root->bf_ = 0; *taller = 0; break;
                case 0: root->bf_ = -1; break;
                case -1: root = rotate_rr_or_rl(root); *taller = 0; break;
            }
        }
    }
    return root;
}
```

### Properties
- Height = O(log n)
- Insert/Delete/Search = O(log n)
- More rotations than Red-Black trees but simpler

---