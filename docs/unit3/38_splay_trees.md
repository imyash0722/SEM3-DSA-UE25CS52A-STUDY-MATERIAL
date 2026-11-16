## 3.8 Splay Trees


### Concept
- **Self-adjusting** BST
- **No balance factor stored** (memory efficient)
- **Splay**: Move accessed node to root via rotations
- Amortized O(log n) for sequence of operations

### Splaying Cases

#### Zig (Node is child of root)
```
  P           X
 /     →       \
X               P
```

#### Zig-Zig (Node and parent same side)
```
    G           X
   /           / \
  P     →     G   P
 /           /   /
X           Y   Z
```
→ Two rotations in same direction

#### Zig-Zag (Node and parent opposite sides)
```
    G           X
   /             \
  P       →       G
   \             /
    X           P
   / \         / \
  Y   Z       Y   Z
```
→ Two rotations in opposite directions

### Operations
```c
void splay(node_t* x) {
    while (x->parent_) {
        node_t* p = x->parent_;
        node_t* g = p->parent_;
        
        if (!g) {  // Zig
            if (p->left_ == x) rotate_right(p);
            else rotate_left(p);
        } else if ((g->left_ == p) == (p->left_ == x)) {  // Zig-Zig
            if (g->left_ == p) {
                rotate_right(g); rotate_right(p);
            } else {
                rotate_left(g); rotate_left(p);
            }
        } else {  // Zig-Zag
            if (p->left_ == x) {
                rotate_right(p); rotate_left(g);
            } else {
                rotate_left(p); rotate_right(g);
            }
        }
    }
}
```

### Applications
- Caches (recently accessed → root)
- Memory allocators
- Network routers (frequent IPs)
- Data compression

---