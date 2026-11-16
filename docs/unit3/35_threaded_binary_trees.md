## 3.5 Threaded Binary Trees


### Concept
- n nodes → n-1 structural pointers (edges)
- 2n pointer fields → n+1 NULL pointers wasted
- **Thread**: Replace NULL pointers with predecessor/successor in inorder
- **lthread_ = 1** means left is thread (not structural)
- **rthread_ = 1** means right is thread

### Structure
```c
struct node {
    int key_;
    struct node *left_, *right_;
    int lthread_;  // 1 = thread, 0 = structural
    int rthread_;
};
typedef struct node node_t;

struct tree {
    node_t *root_;
};
typedef struct tree tree_t;
```

### Insert (Adjusting Threads)
```c
node_t* create_node(int key) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key;
    temp->left_ = temp->right_ = NULL;
    temp->lthread_ = temp->rthread_ = 1;  // Initially all threads
    return temp;
}

node_t* insert_key(node_t* root, int key) {
    node_t* temp = create_node(key);
    node_t *parent = NULL, *curr = root;
    
    // Find insertion point
    while (curr) {
        parent = curr;
        if (key < curr->key_) {
            if (curr->lthread_ == 0) curr = curr->left_;
            else break;  // Reached thread
        } else {
            if (curr->rthread_ == 0) curr = curr->right_;
            else break;
        }
    }
    
    if (!parent) return temp;  // First node
    
    if (key < parent->key_) {  // Insert as left child
        temp->left_ = parent->left_;   // Inherit parent's thread
        temp->right_ = parent;         // Successor = parent
        parent->left_ = temp;
        parent->lthread_ = 0;          // Now structural
    } else {  // Insert as right child
        temp->right_ = parent->right_; // Inherit parent's thread
        temp->left_ = parent;          // Predecessor = parent
        parent->right_ = temp;
        parent->rthread_ = 0;          // Now structural
    }
    return root;
}
```

### Inorder Traversal (Iterative - No Recursion!)
```c
// Find leftmost node
node_t* leftmost(node_t* temp) {
    if (!temp) return NULL;
    while (temp->lthread_ == 0)  // While structural left
        temp = temp->left_;
    return temp;
}

// Iterative inorder
void inorder(node_t* root) {
    node_t* temp = leftmost(root);
    while (temp) {
        printf("%d ", temp->key_);
        
        if (temp->rthread_ == 1)   // Thread to successor
            temp = temp->right_;
        else                       // Structural right
            temp = leftmost(temp->right_);
    }
}
```

### Benefits
- O(1) successor/predecessor
- No stack/recursion needed for traversal
- Memory trade-off: 2 extra bits per node

---