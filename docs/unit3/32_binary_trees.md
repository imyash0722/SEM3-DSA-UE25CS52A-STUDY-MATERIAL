## 3.2 Binary Trees


### Definition
- Each node has **at most 2 children**
- Children distinguished as **left** and **right**
- Recursive: Empty tree OR root + left subtree + right subtree

### Structure
```c
struct node {
    int key_;
    struct node *left_;
    struct node *right_;
};
typedef struct node node_t;

struct tree {
    node_t *root_;
};
typedef struct tree tree_t;
```

### Traversals

#### Inorder (Left, Root, Right)
```c
void inorder(node_t *temp) {
    if (temp) {
        inorder(temp->left_);
        printf("%d ", temp->key_);
        inorder(temp->right_);
    }
}
// Example: D B E A C F
```

#### Preorder (Root, Left, Right)
```c
void preorder(node_t *temp) {
    if (temp) {
        printf("%d ", temp->key_);
        preorder(temp->left_);
        preorder(temp->right_);
    }
}
// Example: A B D E C F
```

#### Postorder (Left, Right, Root)
```c
void postorder(node_t *temp) {
    if (temp) {
        postorder(temp->left_);
        postorder(temp->right_);
        printf("%d ", temp->key_);
    }
}
// Example: D E B F C A
```

### Binary Search Tree (BST)
- Keys ordered: left < root < right
- Search/Insert/Delete: O(h) where h = height
- **Worst case**: Skewed tree, h = n → O(n)

### BST Operations (Recursive on Nodes)

#### Insert
```c
node_t* insert_recursive(node_t* root, node_t* temp) {
    if (root == NULL) return temp;
    else if (root->key_ > temp->key_)
        root->left_ = insert_recursive(root->left_, temp);
    else
        root->right_ = insert_recursive(root->right_, temp);
    return root;
}

void insert(tree_t *ptr_tree, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->left_ = temp->right_ = NULL;
    ptr_tree->root_ = insert_recursive(ptr_tree->root_, temp);
}
```

#### Search
```c
node_t* search_recursive(node_t* root, int key) {
    if (!root) return NULL;
    if (key == root->key_) return root;
    else if (key < root->key_) return search_recursive(root->left_, key);
    else return search_recursive(root->right_, key);
}
```

#### Delete (4 Cases)
```c
node_t* delete_key_recursive(node_t* root, int key) {
    if (!root) return NULL;
    
    if (key < root->key_)
        root->left_ = delete_key_recursive(root->left_, key);
    else if (key > root->key_)
        root->right_ = delete_key_recursive(root->right_, key);
    else {  // Found - handle 4 cases
        // Case 1: Leaf node
        if (!root->left_ && !root->right_) {
            free(root); return NULL;
        }
        // Case 2: Only right child
        else if (!root->left_) {
            node_t* temp = root->right_;
            free(root); return temp;
        }
        // Case 3: Only left child
        else if (!root->right_) {
            node_t* temp = root->left_;
            free(root); return temp;
        }
        // Case 4: Two children - use inorder successor
        else {
            node_t* succ = root->right_;
            while (succ->left_) succ = succ->left_;
            root->key_ = succ->key_;
            root->right_ = delete_key_recursive(root->right_, succ->key_);
        }
    }
    return root;
}
```

#### Utility Functions
```c
// Count nodes
int count_nodes(node_t* root) {
    return root ? 1 + count_nodes(root->left_) + count_nodes(root->right_) : 0;
}

// Count leaves
int count_leaves(node_t* root) {
    if (!root) return 0;
    if (!root->left_ && !root->right_) return 1;
    return count_leaves(root->left_) + count_leaves(root->right_);
}

// Compare trees
int are_same(node_t* r1, node_t* r2) {
    if (!r1 && !r2) return 1;
    if (!r1 || !r2) return 0;
    return r1->key_ == r2->key_ &&
           are_same(r1->left_, r2->left_) &&
           are_same(r1->right_, r2->right_);
}

// Copy tree
node_t* copy_recursive(node_t* src) {
    if (!src) return NULL;
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = src->key_;
    temp->left_ = copy_recursive(src->left_);
    temp->right_ = copy_recursive(src->right_);
    return temp;
}
```

### Tree Reconstruction
**Inorder + Postorder uniquely define a tree**
- Last in postorder = root
- Find root in inorder → left/right split
- Recurse on subtrees

---