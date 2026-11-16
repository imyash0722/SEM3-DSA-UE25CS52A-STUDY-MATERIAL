## 3.3 Array Implementation of Binary Tree


### Method 1: Complete Tree Mapping (No Pointers)
**0-indexed:** left = 2i+1, right = 2i+2, parent = (i-1)/2
**1-indexed:** left = 2i, right = 2i+1, parent = i/2
- Only efficient for **complete** binary trees
- Used for Heaps

### Method 2: Array of Node Structures (With Indices)
```c
#define MAXSIZE 200

struct node {
    int key_;
    int left_;   // Index of left child (-1 = null)
    int right_;  // Index of right child
};
typedef struct node node_t;

struct tree {
    int root_;      // Index of root (-1 = empty)
    int count_;     // Number of nodes
    node_t elem_[MAXSIZE];
};
typedef struct tree tree_t;
```

### Operations

#### Initialize
```c
void init(tree_t *ptr_tree) {
    ptr_tree->root_ = -1;
    ptr_tree->count_ = 0;
}
```

#### Display (Inorder)
```c
void disp_recursive(node_t elem[], int temp) {
    if (temp != -1) {
        disp_recursive(elem, elem[temp].left_);
        printf("%d ", elem[temp].key_);
        disp_recursive(elem, elem[temp].right_);
    }
}

void disp(tree_t *ptr_tree) {
    printf("Tree: ");
    disp_recursive(ptr_tree->elem_, ptr_tree->root_);
    printf("\n");
}
```

#### Insert
```c
int insert_recursive(node_t elem[], int root, int temp) {
    if (root == -1) return temp;
    else if (elem[root].key_ > elem[temp].key_)
        elem[root].left_ = insert_recursive(elem, elem[root].left_, temp);
    else
        elem[root].right_ = insert_recursive(elem, elem[root].right_, temp);
    return root;
}

void insert(tree_t *ptr_tree, int key) {
    if (ptr_tree->count_ == MAXSIZE) { printf("full\n"); exit(1); }
    
    int temp = ptr_tree->count_++;
    ptr_tree->elem_[temp].key_ = key;
    ptr_tree->elem_[temp].left_ = ptr_tree->elem_[temp].right_ = -1;
    
    ptr_tree->root_ = insert_recursive(ptr_tree->elem_, ptr_tree->root_, temp);
}
```

#### Count Nodes/Leaves
```c
int count_nodes_recursive(node_t elem[], int temp) {
    return temp == -1 ? 0 : 
           1 + count_nodes_recursive(elem, elem[temp].left_) 
             + count_nodes_recursive(elem, elem[temp].right_);
}

int count_leaves_recursive(node_t elem[], int temp) {
    if (temp == -1) return 0;
    if (elem[temp].left_ == -1 && elem[temp].right_ == -1) return 1;
    return count_leaves_recursive(elem, elem[temp].left_) 
         + count_leaves_recursive(elem, elem[temp].right_);
}
```

#### Compare Trees
```c
int are_same_recursive(node_t e1[], int r1, node_t e2[], int r2) {
    if (r1 == -1 && r2 == -1) return 1;
    if (r1 == -1 || r2 == -1) return 0;
    return e1[r1].key_ == e2[r2].key_ &&
           are_same_recursive(e1, e1[r1].left_, e2, e2[r2].left_) &&
           are_same_recursive(e1, e1[r1].right_, e2, e2[r2].right_);
}
```

#### Copy Tree (Iterative - simpler with arrays!)
```c
void copy(tree_t* src, tree_t* dst) {
    dst->root_ = src->root_;
    dst->count_ = src->count_;
    for (int i = 0; i < MAXSIZE; ++i)
        dst->elem_[i] = src->elem_[i];
}
```

---