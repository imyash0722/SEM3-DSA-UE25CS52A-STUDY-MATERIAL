## 3.1 General Trees and Binary Trees


### Tree Terminology

**From Genealogy:**
- Parent, Child, Siblings
- Ancestor, Descendant
- Grandparent, Grandchild, Uncle

**From Botany:**
- Root, Nodes, Leaves
- Internal nodes, External nodes
- Branch

**Structural:**
- Path: Sequence of nodes connected by edges
- Level: Distance from root (root = level 0)
- Height: Longest path from node to leaf
- Depth: Path length from root to node
- Degree: Number of children

### Tree Properties
- **Acyclic**: No cycles
- **Connected**: Path between any two nodes
- **n nodes = n-1 edges**
- Adding edge creates cycle, removing edge disconnects

### General Tree Definition
```
Tree = Empty
     | Root + list of subtrees (each is a Tree)
```

### General Tree ADT
```c
void create(tree_t*);
void destroy(tree_t*);
int is_empty(tree_t*);
int is_full(tree_t*);
void add_node(tree_t*, ...);
void remove_node(tree_t*, ...);
void traverse(tree_t*);
node_t* root(tree_t*);
node_t* parent(tree_t*, node_t*);
node_t* children(tree_t*, node_t*);
int is_leaf(tree_t*, node_t*);
int height(tree_t*);
```

---