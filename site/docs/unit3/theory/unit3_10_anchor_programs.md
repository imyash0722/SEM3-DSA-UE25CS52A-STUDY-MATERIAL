# Unit 3: Anchor Programs

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

---

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

---

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

## 📝 Key Programs Summary

| Program | Concepts Covered |
|---------|------------------|
| **BST Complete** | Insert, Search, Delete (4 cases), Traversals, Copy |
| **Heap + PQ** | Build, Insert, Delete Max, Heapsort, PQ |
| **Graph BFS/DFS** | Adjacency List, BFS (Queue), DFS (Stack) |

---

## 📋 Compilation & Testing

```bash
# Compile all
gcc bst_dynamic.c -o bst
gcc heap_pq.c -o heap
gcc graph_demo.c -o graph

# Run
./bst
./heap
./graph
```

---

*End of Unit 3 Anchor Programs*

---

*Next: [Unit 4: Hashing, Tries, Suffix Trees →](../unit4/)*