# Unit 3: Trees, Heaps, AVL Trees, Splay Trees, Graphs

---

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

## 3.4 Expression Trees

### Postfix to Expression Tree

**Algorithm:**
1. Scan postfix left to right
2. **Operand**: Create node, push to stack
3. **Operator**: Pop 2 nodes, create operator node with them as children, push result

```
Postfix: 3 4 + 5 *
Stack evolution:
  push 3     → [3]
  push 4     → [3, 4]
  +          → pop 4,3; create (+, 3, 4); push → [(+)]
  push 5     → [(+), 5]
  *          → pop 5, (+); create (*, (+), 5); push → [(*)]
Result: * root with left=+ and right=5
```

### Structure
```c
struct node {
    char ch_;           // Operand (digit) or operator
    struct node *left_, *right_;
};
typedef struct node node_t;

struct stack {
    node_t* key_[MAXSIZE];
    int top_;
};
typedef struct stack stack_t;
```

### Stack Operations
```c
node_t* create_node(char ch) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->ch_ = ch; temp->left_ = temp->right_ = NULL;
    return temp;
}

void push_operand(stack_t* s, char ch) {
    if (!is_full(s)) s->key_[++s->top_] = create_node(ch);
}

void push_operator(stack_t* s, char ch) {
    if (!is_full(s)) {
        node_t* temp = create_node(ch);
        temp->right_ = pop(s);   // First popped = right operand
        temp->left_ = pop(s);    // Second popped = left operand
        s->key_[++s->top_] = temp;
    }
}
```

### Evaluation (Recursive)
```c
int eval_recursive(node_t* root) {
    if (!root->left_ && !root->right_)  // Leaf = operand
        return root->ch_ - '0';
    
    int left = eval_recursive(root->left_);
    int right = eval_recursive(root->right_);
    
    switch (root->ch_) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}

int eval(stack_t* s) {
    return eval_recursive(pop(s));  // Final tree on stack
}
```

---

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

## 3.6 Heaps

### Definition
**Max-Heap** (Min-Heap similar):
1. **Complete Binary Tree** - all levels full except last (left-filled)
2. **Parental Dominance** - parent ≥ children (recursively)

### Array Representation (1-indexed)
```
Left(i) = 2i, Right(i) = 2i+1, Parent(i) = i/2
```
- No pointers needed!
- No wasted space (complete tree)
- Easy traversal

### Structure
```c
#define MAXSIZE 100

struct heap {
    int key_[MAXSIZE];
    int n_;  // Number of elements
};
typedef struct heap heap_t;
```

### Operations

#### Heapify (Fix subtree at pos)
```c
void heapify(int a[], int n, int pos) {
    int i = pos, j = 2*i;
    int val = a[i];
    int is_heap = 0;
    
    while (j <= n && !is_heap) {
        if (j+1 <= n && a[j+1] > a[j]) ++j;  // Larger child
        if (a[j] > val) {
            a[i] = a[j];   // Move child up
            i = j; j = 2*i;  // Move down
        } else is_heap = 1;
    }
    a[i] = val;
}
```

#### Build Heap (O(n))
```c
void build_heap(heap_t* h, int a[], int n) {
    h->n_ = n;
    for (int i = 1; i <= n; ++i) h->key_[i] = a[i];
    for (int i = n/2; i >= 1; --i)  // Start from last internal node
        heapify(h->key_, h->n_, i);
}
```

#### Insert (O(log n))
```c
void insert(heap_t* h, int key) {
    int pos = ++h->n_;
    h->key_[pos] = key;
    
    // Bubble up
    while (pos > 1 && h->key_[pos] > h->key_[pos/2]) {
        swap(&h->key_[pos], &h->key_[pos/2]);
        pos = pos/2;
    }
}
```

#### Delete Max (O(log n))
```c
int delete_max(heap_t* h) {
    int res = h->key_[1];
    h->key_[1] = h->key_[h->n_];  // Move last to root
    --h->n_;
    heapify(h->key_, h->n_, 1);   // Fix from root
    return res;
}
```

### Heap Applications

#### Priority Queue with Heap
```c
struct queue { heap_t q_; };
typedef struct queue queue_t;

void enqueue(queue_t* q, int key) { insert(&q->q_, key); }
int dequeue(queue_t* q) { return delete_max(&q->q_); }
```

**Operations**: O(log n) for both insert and delete

#### Heapsort
```c
void heapsort(int a[], int n) {
    heap_t h; build_heap(&h, a, n);
    for (int i = n; i >= 1; --i)
        a[i] = delete_max(&h);  // Extract max to end
}
```
- Time: O(n log n)
- Space: O(1) extra
- **Not cache-friendly** - not used in standard libraries

---

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

## 3.9 Graphs

### Definition
**G = (V, E)**
- V: Set of vertices (nodes)
- E: Set of edges (connections)

### Terminology
- **Adjacent**: Connected by edge
- **Incident**: Edge touches vertex
- **Degree**: Edges incident (undirected)
- **In-degree/Out-degree**: Directed edges in/out
- **Path**: Sequence of vertices
- **Cycle**: Path returning to start
- **Connected**: Path between every pair
- **Weighted**: Edges have values (cost, distance, time)

### Special Graphs
- **Eulerian**: Traverse each edge exactly once, return to start
  - Condition: All vertices have even degree
- **Hamiltonian**: Visit each vertex exactly once, return to start
  - No simple condition (NP-complete)

### Representations

#### Adjacency Matrix
```c
// V × V matrix
int adj[MAXV][MAXV];
adj[u][v] = 1;  // Edge exists
adj[u][v] = w;  // Weight (weighted)
// Space: O(V²)
// Edge check: O(1)
```

#### Adjacency List
```c
struct node {
    int vertex_;
    int weight_;     // For weighted graphs
    struct node* next_;
};
typedef struct node node_t;

node_t* adj[MAXV];  // Array of linked lists
// Space: O(V + E)
// Traverse neighbors: O(degree)
```

### Example Graph
```
V = {A, B, C, D, E, F, G, H}
E = {AB, AC, BC, BD, CE, DE, DF, FG, EG, GH, FH}

Adjacency List:
A → B, C
B → A, C, D
C → A, B, E
D → B, E, F
E → C, D, G
F → D, G, H
G → E, F, H
H → F, G

Degree: deg(A)=2, deg(B)=3, deg(H)=2
Σdeg(v) = 2|E| = 22
```

### Graph Algorithms (Overview)

#### BFS (Breadth-First Search) - Uses Queue
```c
void bfs(int start) {
    queue_t q; init_queue(&q);
    int visited[MAXV] = {0};
    enque(&q, start); visited[start] = 1;
    
    while (!is_empty(&q)) {
        int u = deque(&q);
        for (node_t* p = adj[u]; p; p = p->next_)
            if (!visited[p->vertex_]) {
                visited[p->vertex_] = 1;
                enque(&q, p->vertex_);
            }
    }
}
```

#### DFS (Depth-First Search) - Uses Stack
```c
void dfs(int start) {
    stack_t s; init_stack(&s);
    int visited[MAXV] = {0};
    push(&s, start); visited[start] = 1;
    
    while (!is_empty(&s)) {
        int u = pop(&s);
        for (node_t* p = adj[u]; p; p = p->next_)
            if (!visited[p->vertex_]) {
                visited[p->vertex_] = 1;
                push(&s, p->vertex_);
            }
    }
}
```

#### Dijkstra's Shortest Path - Uses Priority Queue (Min-Heap)
```c
void dijkstra(int src) {
    int dist[MAXV]; for (i) dist[i] = INF;
    dist[src] = 0;
    
    pqueue_t pq; init_pqueue(&pq);
    enqueue(&pq, src, 0);  // (vertex, distance)
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);  // Extract min distance
        for (node_t* p = adj[u]; p; p = p->next_) {
            int v = p->vertex_;
            int w = p->weight_;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                enqueue(&pq, v, dist[v]);  // Decrease key
            }
        }
    }
}
```

#### Prim's MST - Uses Priority Queue
```c
void prim(int start) {
    int key[MAXV]; for (i) key[i] = INF;
    int parent[MAXV]; for (i) parent[i] = -1;
    key[start] = 0;
    
    pqueue_t pq; init_pqueue(&pq);
    for (i) enqueue(&pq, i, key[i]);
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);
        for (node_t* p = adj[u]; p; p = p->next_) {
            int v = p->vertex_;
            int w = p->weight_;
            if (in_queue(v) && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                decrease_key(&pq, v, w);
            }
        }
    }
}
```

### Applications
1. **Road Networks** - vertices = cities, edges = roads (weights = distance/time)
2. **Social Networks** - vertices = people, edges = friendships
3. **Computer Networks** - vertices = routers, edges = links
4. **Course Prerequisites** - directed edges = must take before
5. **Web Pages** - vertices = pages, directed edges = hyperlinks
6. **Project Scheduling** - vertices = tasks, edges = dependencies
7. **Software Dependencies** - vertices = modules, edges = imports