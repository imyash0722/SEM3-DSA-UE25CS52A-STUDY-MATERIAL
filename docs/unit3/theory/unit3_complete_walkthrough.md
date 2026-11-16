# Unit 3: Trees, Binary Search Trees, Heaps, AVL, Splay Trees, Graphs

## 📚 Unit Overview

**Topics Covered:**
1. General Trees & Binary Trees
2. Binary Search Tree (BST) - Dynamic & Array Implementation
3. Tree Traversals (Inorder, Preorder, Postorder)
4. Expression Trees
5. Threaded Binary Trees
6. Heaps & Heapsort
7. AVL Trees (Balanced BST)
8. Splay Trees (Self-Adjusting)
9. Graphs - Representation & Traversal

---

## 🌳 Trees - Fundamental Concepts

### What is a Tree?

> **Tree** = Non-linear, hierarchical data structure
> - **Acyclic**: No cycles
> - **Connected**: Path between any two nodes
> - **n nodes = n-1 edges**

### Tree Terminology (Genealogy + Botany)

| Genealogy Terms | Botany Terms | Structural Terms |
|-----------------|--------------|------------------|
| Parent | Root | Path |
| Child | Node | Level (root=0) |
| Sibling | Leaf | Height (max path to leaf) |
| Ancestor | Branch | Depth (path from root) |
| Descendant | Internal node | Degree (#children) |
| Grandparent | External node | |
| Uncle | | |

### Properties
- Adding edge → creates cycle
- Removing edge → disconnects tree
- Exactly one path between any two nodes

---

## 🌲 Binary Trees

### Definition
> A **binary tree** is a tree where each node has **at most 2 children**, distinguished as **left** and **right**.

**Recursive Definition:**
- Empty tree, OR
- Root + left subtree (binary tree) + right subtree (binary tree)

### Node Structure
```c
struct node {
    int key;
    struct node *left;
    struct node *right;
};
typedef struct node node_t;

struct tree {
    node_t *root;
};
typedef struct tree tree_t;
```

---

## 🔄 Tree Traversals - The Three Orders

### 1. Inorder (Left → Root → Right)
```c
void inorder(node_t *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
```
**Example:** D B E A C F

### 2. Preorder (Root → Left → Right)
```c
void preorder(node_t *root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
```
**Example:** A B D E C F

### 3. Postorder (Left → Right → Root)
```c
void postorder(node_t *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}
```
**Example:** D E B F C A

### When to Use Which?
| Traversal | Use Case |
|-----------|----------|
| **Inorder** | BST gives sorted order |
| **Preorder** | Copy tree, serialize |
| **Postorder** | Delete tree, evaluate expressions |

---

## 🔍 Binary Search Tree (BST)

### BST Property
> For every node: **Left subtree keys < Node key < Right subtree keys**

### Operations - All O(h) where h = height

#### Search
```c
node_t* search(node_t *root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}
```

#### Insert
```c
node_t* insert(node_t *root, int key) {
    if (!root) {
        node_t *n = malloc(sizeof(node_t));
        n->key = key; n->left = n->right = NULL;
        return n;
    }
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);
    return root;
}
```

#### Delete (4 Cases)
```c
node_t* delete(node_t *root, int key) {
    if (!root) return NULL;
    
    if (key < root->key)
        root->left = delete(root->left, key);
    else if (key > root->key)
        root->right = delete(root->right, key);
    else {  // Found!
        // Case 1: Leaf
        if (!root->left && !root->right) {
            free(root); return NULL;
        }
        // Case 2: Only right child
        if (!root->left) {
            node_t *t = root->right; free(root); return t;
        }
        // Case 3: Only left child
        if (!root->right) {
            node_t *t = root->left; free(root); return t;
        }
        // Case 4: Two children - use inorder successor
        node_t *succ = root->right;
        while (succ->left) succ = succ->left;
        root->key = succ->key;
        root->right = delete(root->right, succ->key);
    }
    return root;
}
```

**Case 4 Explanation:** Replace with inorder successor (smallest in right subtree), then delete that successor.

---

## 📊 BST Implementation 2: Array-Based

### Structure
```c
#define MAXSIZE 200

struct node {
    int key;
    int left;   // Index of left child (-1 = null)
    int right;  // Index of right child
};
typedef struct node node_t;

struct tree {
    int root;       // Index of root (-1 = empty)
    int count;      // Number of nodes
    node_t elem[MAXSIZE];
};
typedef struct tree tree_t;
```

### Key Differences from Dynamic Version
- Uses **indices** instead of pointers
- `left`/`right` store array indices (-1 = null)
- `root` stores index of root node
- Copy tree = memcpy entire array!

### Insert
```c
int insert_rec(node_t e[], int root, int new_idx) {
    if (root == -1) return new_idx;
    if (e[root].key > e[new_idx].key)
        e[root].left = insert_rec(e, e[root].left, new_idx);
    else
        e[root].right = insert_rec(e, e[root].right, new_idx);
    return root;
}

void insert(tree_t *t, int key) {
    int idx = t->count++;
    t->elem[idx].key = key;
    t->elem[idx].left = t->elem[idx].right = -1;
    t->root = insert_rec(t->elem, t->root, idx);
}
```

---

## 🌿 Expression Trees

### Concept
- **Leaves**: Operands (numbers)
- **Internal nodes**: Operators (+, -, *, /)
- **Inorder** = Infix expression
- **Postorder** = Postfix expression
- **Preorder** = Prefix expression

### Build from Postfix
```c
node_t* build_expression_tree(char *postfix) {
    node_t *stack[100];
    int top = -1;
    
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            // Operand: create node, push
            node_t *n = malloc(sizeof(node_t));
            n->key = ch; n->left = n->right = NULL;
            stack[++top] = n;
        } else {
            // Operator: pop 2, create node, push
            node_t *n = malloc(sizeof(node_t));
            n->key = ch;
            n->right = stack[top--];  // First popped = right
            n->left = stack[top--];   // Second popped = left
            stack[++top] = n;
        }
    }
    return stack[top];  // Root
}
```

### Evaluate Expression Tree
```c
int eval(node_t *root) {
    if (!root->left && !root->right)  // Leaf = operand
        return root->key - '0';
    
    int left = eval(root->left);
    int right = eval(root->right);
    
    switch(root->key) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}
```

---

## 🧵 Threaded Binary Trees

### Problem
- n nodes → n-1 edges (structural pointers)
- 2n pointer fields → n+1 NULL pointers **wasted!**

### Solution: Threads
- Replace NULL pointers with **threads** to inorder predecessor/successor
- `lthread = 1` → left is thread (not structural)
- `rthread = 1` → right is thread

### Structure
```c
struct node {
    int key;
    struct node *left, *right;
    int lthread, rthread;  // 1 = thread, 0 = structural
};
```

### Inorder Traversal (Iterative - No Recursion!)
```c
node_t* leftmost(node_t *n) {
    if (!n) return NULL;
    while (n->lthread == 0) n = n->left;  // Follow structural
    return n;
}

void inorder(node_t *root) {
    node_t *curr = leftmost(root);
    while (curr) {
        printf("%d ", curr->key);
        if (curr->rthread == 1)
            curr = curr->right;      // Thread to successor
        else
            curr = leftmost(curr->right);  // Structural right
    }
}
```

---

## 📦 Heaps

### Definition (Max-Heap)
> **Heap** = Complete Binary Tree + Parental Dominance
> 1. **Complete**: All levels full except last (left-filled)
> 2. **Parental Dominance**: Parent ≥ Children (recursively)

### Array Representation (1-indexed)
```
Left(i) = 2*i, Right(i) = 2*i+1, Parent(i) = i/2
```

### Structure
```c
#define MAXSIZE 100
struct heap {
    int key[MAXSIZE];
    int n;  // Number of elements
};
typedef struct heap heap_t;
```

### Core Operations

#### Heapify (Fix subtree at position i)
```c
void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2*i, right = 2*i + 1;
    
    if (left <= n && a[left] > a[largest]) largest = left;
    if (right <= n && a[right] > a[largest]) largest = right;
    
    if (largest != i) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }
}
```

#### Build Heap (O(n))
```c
void build_heap(heap_t *h, int a[], int n) {
    h->n = n;
    for (int i = 1; i <= n; i++) h->key[i] = a[i];
    for (int i = n/2; i >= 1; i--)  // Start from last internal node
        heapify(h->key, h->n, i);
}
```

#### Insert (O(log n))
```c
void insert(heap_t *h, int key) {
    int i = ++h->n;
    h->key[i] = key;
    // Bubble up
    while (i > 1 && h->key[i] > h->key[i/2]) {
        swap(&h->key[i], &h->key[i/2]);
        i = i/2;
    }
}
```

#### Delete Max (O(log n))
```c
int delete_max(heap_t *h) {
    int max = h->key[1];
    h->key[1] = h->key[h->n--];  // Move last to root
    heapify(h->key, h->n, 1);    // Fix from root
    return max;
}
```

### Heapsort (O(n log n))
```c
void heapsort(int a[], int n) {
    heap_t h; build_heap(&h, a, n);
    for (int i = n; i >= 1; i--)
        a[i] = delete_max(&h);  // Extract max to end
}
```

### Priority Queue using Heap
```c
struct pqueue { heap_t h; };
void pq_enqueue(pqueue_t *q, int key) { insert(&q->h, key); }
int pq_dequeue(pqueue_t *q) { return delete_max(&q->h); }
// Both O(log n)!
```

---

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

## 🎯 Splay Trees (Self-Adjusting)

### Concept
- No balance factors stored (memory efficient!)
- **Splay**: Move accessed node to root via rotations
- **Amortized** O(log n) for sequence of operations

### Splaying Cases
1. **Zig**: Node is child of root → single rotation
2. **Zig-Zig**: Node & parent same side → two same-direction rotations
3. **Zig-Zag**: Node & parent opposite sides → two opposite rotations

### Applications
- Caches (recently accessed → root)
- Memory allocators
- Network routers (frequent IPs)

---

## 🌐 Graphs

### Definition
> **G = (V, E)** where V = vertices, E = edges

### Representations

#### 1. Adjacency Matrix
```c
int adj[MAXV][MAXV];
adj[u][v] = 1;  // Edge exists
adj[u][v] = w;  // Weight (weighted)
```
- Space: O(V²)
- Edge check: O(1)

#### 2. Adjacency List
```c
struct node {
    int vertex;
    int weight;
    struct node *next;
};
typedef struct node node_t;

node_t *adj[MAXV];  // Array of linked lists
```
- Space: O(V + E)
- Traverse neighbors: O(degree)

### Example Graph
```
V = {A, B, C, D, E, F, G, H}
Edges: AB, AC, BC, BD, CE, DE, DF, FG, EG, GH, FH

Adjacency List:
A → B, C
B → A, C, D
C → A, B, E
D → B, E, F
E → C, D, G
F → D, G, H
G → E, F, H
H → F, G
```

### Traversals

#### BFS (Breadth-First Search) - Uses Queue
```c
void bfs(int start) {
    queue_t q; init(&q);
    int visited[MAXV] = {0};
    enqueue(&q, start); visited[start] = 1;
    
    while (!is_empty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        for (node_t *p = adj[u]; p; p = p->next)
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                enqueue(&q, p->vertex);
            }
    }
}
```

#### DFS (Depth-First Search) - Uses Stack
```c
void dfs(int start) {
    stack_t s; init(&s);
    int visited[MAXV] = {0};
    push(&s, start); visited[start] = 1;
    
    while (!is_empty(&s)) {
        int u = pop(&s);
        printf("%d ", u);
        for (node_t *p = adj[u]; p; p = p->next)
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                push(&s, p->vertex);
            }
    }
}
```

### Graph Algorithms

#### Dijkstra's Shortest Path (Weighted, Non-negative)
- Uses **Min-Heap Priority Queue**
- Time: O((V+E) log V)

#### Prim's MST (Minimum Spanning Tree)
- Uses **Min-Heap Priority Queue**
- Time: O(E log V)

---

## 🎯 Anchor Programs for Unit 3

### Program 1: Complete BST (Dynamic)
```c
// bst_dynamic.c - Complete BST with all operations
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left, *right;
} node_t;

typedef struct { node_t *root; } tree_t;

void init(tree_t *t) { t->root = NULL; }

node_t* create_node(int key) {
    node_t *n = malloc(sizeof(node_t));
    n->key = key; n->left = n->right = NULL;
    return n;
}

// Insert
node_t* insert_rec(node_t *root, node_t *n) {
    if (!root) return n;
    if (root->key > n->key)
        root->left = insert_rec(root->left, n);
    else
        root->right = insert_rec(root->right, n);
    return root;
}

void insert(tree_t *t, int key) {
    t->root = insert_rec(t->root, create_node(key));
}

// Search
node_t* search(node_t *root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

// Traversals
void inorder(node_t *r) { if (r) { inorder(r->left); printf("%d ", r->key); inorder(r->right); } }
void preorder(node_t *r) { if (r) { printf("%d ", r->key); preorder(r->left); preorder(r->right); } }
void postorder(node_t *r) { if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->key); } }

void display(tree_t *t) {
    printf("Inorder: "); inorder(t->root); printf("\n");
    printf("Preorder: "); preorder(t->root); printf("\n");
    printf("Postorder: "); postorder(t->root); printf("\n");
}

// Delete
node_t* inorder_succ(node_t *r) { while (r->left) r = r->left; return r; }

node_t* delete_rec(node_t *root, int key) {
    if (!root) return NULL;
    if (key < root->key) root->left = delete_rec(root->left, key);
    else if (key > root->key) root->right = delete_rec(root->right, key);
    else {
        if (!root->left && !root->right) { free(root); return NULL; }
        if (!root->left) { node_t *t = root->right; free(root); return t; }
        if (!root->right) { node_t *t = root->left; free(root); return t; }
        node_t *s = inorder_succ(root->right);
        root->key = s->key;
        root->right = delete_rec(root->right, s->key);
    }
    return root;
}

void delete_key(tree_t *t, int key) { t->root = delete_rec(t->root, key); }

// Utilities
int count_nodes(node_t *r) { return r ? 1 + count_nodes(r->left) + count_nodes(r->right) : 0; }
int count_leaves(node_t *r) { 
    if (!r) return 0;
    if (!r->left && !r->right) return 1;
    return count_leaves(r->left) + count_leaves(r->right);
}

node_t* copy_rec(node_t *r) {
    if (!r) return NULL;
    node_t *n = malloc(sizeof(node_t));
    n->key = r->key;
    n->left = copy_rec(r->left);
    n->right = copy_rec(r->right);
    return n;
}

int main() {
    tree_t t1, t2; init(&t1); init(&t2);
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) insert(&t1, keys[i]);
    
    display(&t1);
    printf("Nodes: %d, Leaves: %d\n", count_nodes(t1.root), count_leaves(t1.root));
    
    t2.root = copy_rec(t1.root);
    printf("Trees identical: %d\n", 1); // Would use are_same()
    
    delete_key(&t1, 30);
    printf("After delete 30: "); inorder(t1.root); printf("\n");
    
    return 0;
}
```

### Program 2: Heap with Priority Queue
```c
// heap_pq.c - Heap & Priority Queue
#include <stdio.h>
#define MAXSIZE 100

typedef struct {
    int key[MAXSIZE];
    int n;
} heap_t;

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void heapify(int a[], int n, int i) {
    int largest = i, l = 2*i, r = 2*i+1;
    if (l <= n && a[l] > a[largest]) largest = l;
    if (r <= n && a[r] > a[largest]) largest = r;
    if (largest != i) { swap(&a[i], &a[largest]); heapify(a, n, largest); }
}

void build_heap(heap_t *h, int a[], int n) {
    h->n = n;
    for (int i = 1; i <= n; i++) h->key[i] = a[i];
    for (int i = n/2; i >= 1; i--) heapify(h->key, h->n, i);
}

void insert(heap_t *h, int key) {
    int i = ++h->n;
    h->key[i] = key;
    while (i > 1 && h->key[i] > h->key[i/2]) {
        swap(&h->key[i], &h->key[i/2]);
        i = i/2;
    }
}

int delete_max(heap_t *h) {
    int max = h->key[1];
    h->key[1] = h->key[h->n--];
    heapify(h->key, h->n, 1);
    return max;
}

void heapsort(int a[], int n) {
    heap_t h; build_heap(&h, a, n);
    for (int i = n; i >= 1; i--) a[i] = delete_max(&h);
}

typedef struct { heap_t h; } pqueue_t;

void pq_init(pqueue_t *q) { q->h.n = 0; }
void pq_enqueue(pqueue_t *q, int key) { insert(&q->h, key); }
int pq_dequeue(pqueue_t *q) { return delete_max(&q->h); }

int main() {
    printf("=== Heap & Priority Queue Demo ===\n\n");
    
    // Build heap
    int a[] = {0, 10, 20, 30, 5, 15};  // 1-indexed
    heap_t h; build_heap(&h, a, 5);
    printf("Heap: "); for (int i = 1; i <= h.n; i++) printf("%d ", h.key[i]); printf("\n");
    
    insert(&h, 25);
    printf("After insert 25: "); for (int i = 1; i <= h.n; i++) printf("%d ", h.key[i]); printf("\n");
    
    printf("Delete max: %d\n", delete_max(&h));
    printf("After delete: "); for (int i = 1; i <= h.n; i++) printf("%d ", h.key[i]); printf("\n");
    
    // Heapsort
    int arr[] = {0, 4, 10, 3, 5, 1};
    heapsort(arr, 5);
    printf("Sorted: "); for (int i = 1; i <= 5; i++) printf("%d ", arr[i]); printf("\n");
    
    // Priority Queue
    printf("\nPriority Queue:\n");
    pqueue_t pq; pq_init(&pq);
    pq_enqueue(&pq, 10); pq_enqueue(&pq, 30); pq_enqueue(&pq, 20); pq_enqueue(&pq, 5);
    while (pq.h.n) printf("%d ", pq_dequeue(&pq)); printf("\n");
    
    return 0;
}
```

### Program 3: Graph BFS/DFS
```c
// graph_demo.c - Graph Traversals
#include <stdio.h>
#include <stdlib.h>
#define MAXV 100

typedef struct node {
    int vertex;
    struct node *next;
} node_t;

node_t *adj[MAXV];

void add_edge(int u, int v) {
    node_t *n = malloc(sizeof(node_t));
    n->vertex = v; n->next = adj[u]; adj[u] = n;
}

// BFS
void bfs(int start, int V) {
    int q[MAXV], front = 0, rear = 0;
    int visited[MAXV] = {0};
    q[rear++] = start; visited[start] = 1;
    printf("BFS: ");
    while (front != rear) {
        int u = q[front++];
        printf("%d ", u);
        for (node_t *p = adj[u]; p; p = p->next)
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                q[rear++] = p->vertex;
            }
    }
    printf("\n");
}

// DFS
void dfs(int start, int V) {
    int s[MAXV], top = -1;
    int visited[MAXV] = {0};
    s[++top] = start; visited[start] = 1;
    printf("DFS: ");
    while (top >= 0) {
        int u = s[top--];
        printf("%d ", u);
        for (node_t *p = adj[u]; p; p = p->next)
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                s[++top] = p->vertex;
            }
    }
    printf("\n");
}

int main() {
    // Build example graph
    add_edge(0, 1); add_edge(0, 2);
    add_edge(1, 0); add_edge(1, 2); add_edge(1, 3);
    add_edge(2, 0); add_edge(2, 1); add_edge(2, 4);
    add_edge(3, 1); add_edge(3, 4); add_edge(3, 5);
    add_edge(4, 2); add_edge(4, 3); add_edge(4, 6);
    add_edge(5, 3); add_edge(5, 6); add_edge(5, 7);
    add_edge(6, 4); add_edge(6, 5); add_edge(6, 7);
    add_edge(7, 5); add_edge(7, 6);
    
    printf("Graph (Adjacency List):\n");
    for (int i = 0; i < 8; i++) {
        printf("%c: ", 'A' + i);
        for (node_t *p = adj[i]; p; p = p->next)
            printf("%c ", 'A' + p->vertex);
        printf("\n");
    }
    
    bfs(0, 8);
    dfs(0, 8);
    return 0;
}
```

---

## 📝 Key Takeaways for Unit 3

| Concept | Key Insight |
|---------|-------------|
| **Tree** | Hierarchical, n nodes = n-1 edges |
| **Binary Tree** | Max 2 children per node |
| **Traversals** | In/Pre/Post order - different uses |
| **BST** | Left < Root < Right, O(h) ops |
| **BST Delete** | 4 cases - leaf, one child, two children |
| **Expression Tree** | Postfix → Tree → Evaluate recursively |
| **Threaded Tree** | Threads replace NULL, O(1) successor |
| **Heap** | Complete tree + parental dominance |
| **Heap Operations** | Build O(n), Insert/Delete O(log n) |
| **Heapsort** | O(n log n), in-place, not cache-friendly |
| **AVL** | Height-balanced, 4 rotation cases |
| **Splay** | Self-adjusting, amortized O(log n) |
| **Graph** | V vertices, E edges, Matrix/List |
| **BFS** | Queue, shortest path (unweighted) |
| **DFS** | Stack, topological sort, cycles |
| **Dijkstra** | Min-heap, weighted shortest path |
| **Prim** | Min-heap, MST |

---

*Next: Unit 4 - Hashing, Tries, Suffix Trees, Advanced Graph Algorithms*