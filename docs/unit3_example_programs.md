# Unit 3: Detailed Example Programs

## 3.1 Binary Search Tree (Dynamic Memory)

```c
// bst_dynamic.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_;
    struct node *left_, *right_;
};
typedef struct node node_t;

struct tree {
    node_t *root_;
};
typedef struct tree tree_t;

void init(tree_t *t) { t->root_ = NULL; }

// Insert
node_t* insert_rec(node_t* root, node_t* temp) {
    if (!root) return temp;
    if (root->key_ > temp->key_)
        root->left_ = insert_rec(root->left_, temp);
    else
        root->right_ = insert_rec(root->right_, temp);
    return root;
}

void insert(tree_t *t, int key) {
    node_t *temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; temp->left_ = temp->right_ = NULL;
    t->root_ = insert_rec(t->root_, temp);
}

// Search
node_t* search_rec(node_t* root, int key) {
    if (!root || root->key_ == key) return root;
    if (key < root->key_) return search_rec(root->left_, key);
    return search_rec(root->right_, key);
}

node_t* search(tree_t *t, int key) {
    return search_rec(t->root_, key);
}

// Delete
node_t* inorder_succ(node_t* root) {
    while (root->left_) root = root->left_;
    return root;
}

node_t* delete_rec(node_t* root, int key) {
    if (!root) return NULL;
    if (key < root->key_) root->left_ = delete_rec(root->left_, key);
    else if (key > root->key_) root->right_ = delete_rec(root->right_, key);
    else {
        if (!root->left_ && !root->right_) { free(root); return NULL; }
        if (!root->left_) { node_t* t = root->right_; free(root); return t; }
        if (!root->right_) { node_t* t = root->left_; free(root); return t; }
        node_t* s = inorder_succ(root->right_);
        root->key_ = s->key_;
        root->right_ = delete_rec(root->right_, s->key_);
    }
    return root;
}

void delete_key(tree_t *t, int key) {
    t->root_ = delete_rec(t->root_, key);
}

// Traversals
void inorder(node_t* r) {
    if (r) { inorder(r->left_); printf("%d ", r->key_); inorder(r->right_); }
}
void preorder(node_t* r) {
    if (r) { printf("%d ", r->key_); preorder(r->left_); preorder(r->right_); }
}
void postorder(node_t* r) {
    if (r) { postorder(r->left_); postorder(r->right_); printf("%d ", r->key_); }
}

void disp(tree_t *t) {
    printf("Inorder: "); inorder(t->root_); printf("\n");
    printf("Preorder: "); preorder(t->root_); printf("\n");
    printf("Postorder: "); postorder(t->root_); printf("\n");
}

// Utilities
int count_nodes(node_t* r) {
    return r ? 1 + count_nodes(r->left_) + count_nodes(r->right_) : 0;
}

int count_leaves(node_t* r) {
    if (!r) return 0;
    if (!r->left_ && !r->right_) return 1;
    return count_leaves(r->left_) + count_leaves(r->right_);
}

node_t* copy_rec(node_t* r) {
    if (!r) return NULL;
    node_t* t = (node_t*)malloc(sizeof(node_t));
    t->key_ = r->key_;
    t->left_ = copy_rec(r->left_);
    t->right_ = copy_rec(r->right_);
    return t;
}

int are_same(node_t* r1, node_t* r2) {
    if (!r1 && !r2) return 1;
    if (!r1 || !r2) return 0;
    return r1->key_ == r2->key_ && are_same(r1->left_, r2->left_) && are_same(r1->right_, r2->right_);
}

int main() {
    tree_t t1, t2; init(&t1); init(&t2);
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i) insert(&t1, keys[i]);
    
    disp(&t1);
    printf("Nodes: %d, Leaves: %d\n", count_nodes(t1.root_), count_leaves(t1.root_));
    
    t2.root_ = copy_rec(t1.root_);
    printf("Trees same: %d\n", are_same(t1.root_, t2.root_));
    
    delete_key(&t1, 30);
    printf("After deleting 30: "); inorder(t1.root_); printf("\n");
    return 0;
}
```

---

## 3.2 Binary Search Tree (Array Implementation)

```c
// bst_array.c
#include <stdio.h>
#define MAXSIZE 200

struct node {
    int key_;
    int left_, right_;
};
typedef struct node node_t;

struct tree {
    int root_;
    int count_;
    node_t elem_[MAXSIZE];
};
typedef struct tree tree_t;

void init(tree_t *t) { t->root_ = -1; t->count_ = 0; }

// Insert
int insert_rec(node_t e[], int root, int temp) {
    if (root == -1) return temp;
    if (e[root].key_ > e[temp].key_)
        e[root].left_ = insert_rec(e, e[root].left_, temp);
    else
        e[root].right_ = insert_rec(e, e[root].right_, temp);
    return root;
}

void insert(tree_t *t, int key) {
    if (t->count_ == MAXSIZE) { printf("Full\n"); return; }
    int temp = t->count_++;
    t->elem_[temp].key_ = key;
    t->elem_[temp].left_ = t->elem_[temp].right_ = -1;
    t->root_ = insert_rec(t->elem_, t->root_, temp);
}

// Display
void disp_rec(node_t e[], int temp) {
    if (temp != -1) {
        disp_rec(e, e[temp].left_);
        printf("%d ", e[temp].key_);
        disp_rec(e, e[temp].right_);
    }
}

void disp(tree_t *t) {
    printf("Inorder: "); disp_rec(t->elem_, t->root_); printf("\n");
}

// Count nodes
int count_rec(node_t e[], int temp) {
    return temp == -1 ? 0 : 
        1 + count_rec(e, e[temp].left_) + count_rec(e, e[temp].right_);
}

// Count leaves
int leaves_rec(node_t e[], int temp) {
    if (temp == -1) return 0;
    if (e[temp].left_ == -1 && e[temp].right_ == -1) return 1;
    return leaves_rec(e, e[temp].left_) + leaves_rec(e, e[temp].right_);
}

// Compare
int same_rec(node_t e1[], int r1, node_t e2[], int r2) {
    if (r1 == -1 && r2 == -1) return 1;
    if (r1 == -1 || r2 == -1) return 0;
    return e1[r1].key_ == e2[r2].key_ &&
        same_rec(e1, e1[r1].left_, e2, e2[r2].left_) &&
        same_rec(e1, e1[r1].right_, e2, e2[r2].right_);
}

// Copy (iterative)
void copy(tree_t* src, tree_t* dst) {
    dst->root_ = src->root_;
    dst->count_ = src->count_;
    for (int i = 0; i < MAXSIZE; ++i) dst->elem_[i] = src->elem_[i];
}

int main() {
    tree_t t1, t2; init(&t1); init(&t2);
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i) insert(&t1, keys[i]);
    
    disp(&t1);
    printf("Nodes: %d, Leaves: %d\n", count_rec(t1.elem_, t1.root_), 
           leaves_rec(t1.elem_, t1.root_));
    
    copy(&t1, &t2);
    printf("Trees same: %d\n", same_rec(t1.elem_, t1.root_, t2.elem_, t2.root_));
    return 0;
}
```

---

## 3.3 Expression Tree

```c
// expression_tree.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 100

struct node {
    char ch_;
    struct node *left_, *right_;
};
typedef struct node node_t;

struct stack {
    node_t* key_[MAXSIZE];
    int top_;
};
typedef struct stack stack_t;

void init_s(stack_t *s) { s->top_ = -1; }
int is_empty_s(stack_t *s) { return s->top_ == -1; }
int is_full_s(stack_t *s) { return s->top_ == MAXSIZE - 1; }

node_t* create_node(char ch) {
    node_t* t = (node_t*)malloc(sizeof(node_t));
    t->ch_ = ch; t->left_ = t->right_ = NULL; return t;
}

void push_operand(stack_t *s, char ch) {
    if (!is_full_s(s)) s->key_[++s->top_] = create_node(ch);
}

void push_operator(stack_t *s, char ch) {
    if (!is_full_s(s)) {
        node_t* t = create_node(ch);
        t->right_ = s->key_[s->top_--];
        t->left_ = s->key_[s->top_--];
        s->key_[++s->top_] = t;
    }
}

node_t* pop_s(stack_t *s) {
    return is_empty_s(s) ? NULL : s->key_[s->top_--];
}

int eval_rec(node_t* r) {
    if (!r->left_ && !r->right_) return r->ch_ - '0';
    int l = eval_rec(r->left_);
    int r_val = eval_rec(r->right_);
    switch (r->ch_) {
        case '+': return l + r_val;
        case '-': return l - r_val;
        case '*': return l * r_val;
        case '/': return l / r_val;
    }
    return 0;
}

int main() {
    stack_t s; init_s(&s);
    char postfix[] = "34+5*";  // (3+4)*5 = 35
    
    for (int i = 0; postfix[i]; ++i) {
        char ch = postfix[i];
        if (isdigit(ch)) push_operand(&s, ch);
        else push_operator(&s, ch);
    }
    
    node_t* tree = pop_s(&s);
    printf("Result: %d\n", eval_rec(tree));  // 35
    return 0;
}
```

---

## 3.4 Threaded Binary Tree

```c
// threaded_bst.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key_;
    struct node *left_, *right_;
    int lthread_, rthread_;  // 1 = thread, 0 = structural
};
typedef struct node node_t;

struct tree {
    node_t *root_;
};
typedef struct tree tree_t;

void init(tree_t *t) { t->root_ = NULL; }

node_t* create_node(int key) {
    node_t* t = (node_t*)malloc(sizeof(node_t));
    t->key_ = key; t->left_ = t->right_ = NULL;
    t->lthread_ = t->rthread_ = 1;  // Initially all threads
    return t;
}

void insert(tree_t *t, int key) {
    node_t* temp = create_node(key);
    node_t *parent = NULL, *curr = t->root_;
    
    while (curr) {
        parent = curr;
        if (key < curr->key_) {
            if (curr->lthread_ == 0) curr = curr->left_;
            else break;
        } else {
            if (curr->rthread_ == 0) curr = curr->right_;
            else break;
        }
    }
    
    if (!parent) { t->root_ = temp; return; }
    
    if (key < parent->key_) {
        temp->left_ = parent->left_;
        temp->right_ = parent;
        parent->left_ = temp;
        parent->lthread_ = 0;
    } else {
        temp->right_ = parent->right_;
        temp->left_ = parent;
        parent->right_ = temp;
        parent->rthread_ = 0;
    }
}

// Leftmost node
node_t* leftmost(node_t* n) {
    if (!n) return NULL;
    while (n->lthread_ == 0) n = n->left_;
    return n;
}

// Iterative inorder (NO RECURSION!)
void inorder(tree_t *t) {
    printf("Inorder: ");
    node_t* curr = leftmost(t->root_);
    while (curr) {
        printf("%d ", curr->key_);
        if (curr->rthread_ == 1) curr = curr->right_;
        else curr = leftmost(curr->right_);
    }
    printf("\n");
}

int main() {
    tree_t t; init(&t);
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; ++i) insert(&t, keys[i]);
    inorder(&t);  // 20 30 40 50 60 70 80
    return 0;
}
```

---

## 3.5 Heap (Max-Heap)

```c
// heap.c
#include <stdio.h>
#define MAXSIZE 100

struct heap {
    int key_[MAXSIZE];
    int n_;
};
typedef struct heap heap_t;

void init(heap_t *h) { h->n_ = 0; }

// Heapify subtree at pos
void heapify(int a[], int n, int pos) {
    int i = pos, j = 2*i;
    int val = a[i];
    int done = 0;
    while (j <= n && !done) {
        if (j+1 <= n && a[j+1] > a[j]) ++j;
        if (a[j] > val) { a[i] = a[j]; i = j; j = 2*i; }
        else done = 1;
    }
    a[i] = val;
}

// Build heap from array
void build_heap(heap_t *h, int a[], int n) {
    h->n_ = n;
    for (int i = 1; i <= n; ++i) h->key_[i] = a[i];
    for (int i = n/2; i >= 1; --i) heapify(h->key_, h->n_, i);
}

// Insert
void insert(heap_t *h, int key) {
    int pos = ++h->n_;
    h->key_[pos] = key;
    while (pos > 1 && h->key_[pos] > h->key_[pos/2]) {
        int t = h->key_[pos]; h->key_[pos] = h->key_[pos/2]; h->key_[pos/2] = t;
        pos = pos/2;
    }
}

// Delete max
int delete_max(heap_t *h) {
    int res = h->key_[1];
    h->key_[1] = h->key_[h->n_--];
    heapify(h->key_, h->n_, 1);
    return res;
}

// Heapsort
void heapsort(int a[], int n) {
    heap_t h; build_heap(&h, a, n);
    for (int i = n; i >= 1; --i) a[i] = delete_max(&h);
}

void disp(heap_t *h) {
    for (int i = 1; i <= h->n_; ++i) printf("%d ", h->key_[i]);
    printf("\n");
}

int main() {
    // Build heap
    heap_t h; int a[] = {0, 10, 20, 30, 5, 15};  // 1-indexed
    build_heap(&h, a, 5);
    printf("Heap: "); disp(&h);
    
    // Insert
    insert(&h, 25);
    printf("After insert 25: "); disp(&h);
    
    // Delete max
    printf("Deleted: %d\n", delete_max(&h));
    printf("After delete: "); disp(&h);
    
    // Heapsort
    int arr[] = {0, 4, 10, 3, 5, 1};
    heapsort(arr, 5);
    printf("Sorted: ");
    for (int i = 1; i <= 5; ++i) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
```

---

## 3.6 Priority Queue with Heap

```c
// pq_heap.c
#include <stdio.h>
#define MAXSIZE 100

struct heap {
    int key_[MAXSIZE];
    int n_;
};
typedef struct heap heap_t;

struct pqueue { heap_t h_; };
typedef struct pqueue pqueue_t;

void init_pq(pqueue_t *q) { q->h_.n_ = 0; }
int is_empty(pqueue_t *q) { return q->h_.n_ == 0; }

void enqueue(pqueue_t *q, int key) {
    int pos = ++q->h_.n_;
    q->h_.key_[pos] = key;
    while (pos > 1 && q->h_.key_[pos] > q->h_.key_[pos/2]) {
        int t = q->h_.key_[pos]; q->h_.key_[pos] = q->h_.key_[pos/2]; q->h_.key_[pos/2] = t;
        pos /= 2;
    }
}

int dequeue(pqueue_t *q) {
    int res = q->h_.key_[1];
    q->h_.key_[1] = q->h_.key_[q->h_.n_--];
    int i = 1, j = 2;
    while (j <= q->h_.n_) {
        if (j+1 <= q->h_.n_ && q->h_.key_[j+1] > q->h_.key_[j]) ++j;
        if (q->h_.key_[j] > q->h_.key_[1]) {
            q->h_.key_[i] = q->h_.key_[j];
            i = j; j = 2*i;
        } else break;
    }
    q->h_.key_[i] = q->h_.key_[1];
    return res;
}

int main() {
    pqueue_t q; init_pq(&q);
    enqueue(&q, 10); enqueue(&q, 30); enqueue(&q, 20); enqueue(&q, 5);
    while (!is_empty(&q)) printf("%d ", dequeue(&q));  // 30 20 10 5
    return 0;
}
```

---

## 3.7 Graph Representations

```c
// graph.c
#include <stdio.h>
#include <stdlib.h>
#define MAXV 100

// Adjacency List
struct node {
    int vertex_;
    int weight_;
    struct node* next_;
};
typedef struct node node_t;

node_t* adj[MAXV];

void add_edge(int u, int v, int w) {
    node_t* t = (node_t*)malloc(sizeof(node_t));
    t->vertex_ = v; t->weight_ = w; t->next_ = adj[u]; adj[u] = t;
}

void print_graph(int V) {
    for (int i = 0; i < V; ++i) {
        printf("%d: ", i);
        for (node_t* p = adj[i]; p; p = p->next_)
            printf("-> %d(w=%d) ", p->vertex_, p->weight_);
        printf("\n");
    }
}

// BFS
int visited[MAXV];
struct queue { int q[MAXV]; int f, r; };
typedef struct queue queue_t;

void bfs(int start) {
    queue_t q = {{0}, 0, 0};
    for (int i = 0; i < MAXV; ++i) visited[i] = 0;
    q.q[q.r++] = start; visited[start] = 1;
    while (q.f != q.r) {
        int u = q.q[q.f++];
        printf("%d ", u);
        for (node_t* p = adj[u]; p; p = p->next_)
            if (!visited[p->vertex_]) {
                visited[p->vertex_] = 1;
                q.q[q.r++] = p->vertex_;
            }
    }
    printf("\n");
}

// DFS
struct stack { int s[MAXV]; int top; };
typedef struct stack stack_t;

void dfs(int start) {
    stack_t s = {{0}, -1};
    for (int i = 0; i < MAXV; ++i) visited[i] = 0;
    s.s[++s.top] = start; visited[start] = 1;
    while (s.top >= 0) {
        int u = s.s[s.top--];
        printf("%d ", u);
        for (node_t* p = adj[u]; p; p = p->next_)
            if (!visited[p->vertex_]) {
                visited[p->vertex_] = 1;
                s.s[++s.top] = p->vertex_;
            }
    }
    printf("\n");
}

int main() {
    // Example graph from notes
    add_edge(0, 1, 1); add_edge(0, 2, 1);  // A-B, A-C
    add_edge(1, 0, 1); add_edge(1, 2, 1); add_edge(1, 3, 1);  // B-A, B-C, B-D
    add_edge(2, 0, 1); add_edge(2, 1, 1); add_edge(2, 4, 1);  // C-A, C-B, C-E
    add_edge(3, 1, 1); add_edge(3, 4, 1); add_edge(3, 5, 1);  // D-B, D-E, D-F
    add_edge(4, 2, 1); add_edge(4, 3, 1); add_edge(4, 6, 1);  // E-C, E-D, E-G
    add_edge(5, 3, 1); add_edge(5, 6, 1); add_edge(5, 7, 1);  // F-D, F-G, F-H
    add_edge(6, 4, 1); add_edge(6, 5, 1); add_edge(6, 7, 1);  // G-E, G-F, G-H
    add_edge(7, 5, 1); add_edge(7, 6, 1);  // H-F, H-G
    
    print_graph(8);
    printf("BFS from 0: "); bfs(0);
    printf("DFS from 0: "); dfs(0);
    return 0;
}
```

---

## 3.8 Dijkstra's Algorithm (Graph + Priority Queue)

```c
// dijkstra.c
#include <stdio.h>
#include <limits.h>
#define MAXV 100
#define INF INT_MAX

struct node {
    int vertex_, weight_, next_;
};
typedef struct node node_t;

node_t adj[MAXV * 10];
int head[MAXV], edge_cnt = 0;

void add_edge(int u, int v, int w) {
    adj[edge_cnt] = (node_t){v, w, head[u]};
    head[u] = edge_cnt++;
}

// Min-heap for Dijkstra
struct heap {
    int v[MAXV], dist[MAXV], pos[MAXV];
    int n;
};
typedef struct heap heap_t;

void swap_h(heap_t *h, int i, int j) {
    int tv = h->v[i], td = h->dist[i];
    h->v[i] = h->v[j]; h->dist[i] = h->dist[j]; h->pos[h->v[i]] = i;
    h->v[j] = tv; h->dist[j] = td; h->pos[h->v[j]] = j;
}

void heapify_up(heap_t *h, int i) {
    while (i > 1 && h->dist[i] < h->dist[i/2]) swap_h(h, i, i/2), i /= 2;
}

void heapify_down(heap_t *h, int i) {
    int smallest = i, l = 2*i, r = 2*i+1;
    if (l <= h->n && h->dist[l] < h->dist[smallest]) smallest = l;
    if (r <= h->n && h->dist[r] < h->dist[smallest]) smallest = r;
    if (smallest != i) { swap_h(h, i, smallest); heapify_down(h, smallest); }
}

void dijkstra(int V, int src) {
    int dist[MAXV];
    for (int i = 0; i < V; ++i) dist[i] = INF;
    dist[src] = 0;
    
    heap_t h = {{0}, {0}, {0}, 0};
    for (int i = 0; i < V; ++i) {
        h.v[++h.n] = i;
        h.dist[h.n] = dist[i];
        h.pos[i] = h.n;
    }
    // Build heap
    for (int i = h.n/2; i >= 1; --i) heapify_down(&h, i);
    
    while (h.n > 0) {
        int u = h.v[1];
        int du = h.dist[1];
        h.v[1] = h.v[h.n];
        h.dist[1] = h.dist[h.n];
        h.pos[h.v[1]] = 1;
        --h.n;
        heapify_down(&h, 1);
        
        if (du == INF) break;
        
        for (int e = head[u]; e != -1; e = adj[e].next_) {
            int v = adj[e].vertex_;
            int w = adj[e].weight_;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                int idx = h.pos[v];
                h.dist[idx] = dist[v];
                heapify_up(&h, idx);
            }
        }
    }
    
    printf("Shortest distances from %d:\n", src);
    for (int i = 0; i < V; ++i)
        printf("  to %d: %d\n", i, dist[i] == INF ? -1 : dist[i]);
}

int main() {
    for (int i = 0; i < MAXV; ++i) head[i] = -1;
    // Same graph as before with weights
    add_edge(0, 1, 4); add_edge(0, 2, 2);
    add_edge(1, 2, 1); add_edge(1, 3, 5);
    add_edge(2, 3, 8); add_edge(2, 4, 10);
    add_edge(3, 4, 2); add_edge(3, 5, 6);
    add_edge(4, 5, 2);
    
    dijkstra(6, 0);
    return 0;
}
```

---

## 3.9 Tree Reconstruction from Traversals

```c
// tree_reconstruct.c
#include <stdio.h>
#include <stdlib.h>

struct node {
    char key_;
    struct node *left_, *right_;
};
typedef struct node node_t;

char inorder_str[] = "DBHEAFCGJI";
char postorder_str[] = "DHEBFIJGCA";
int in_idx = 0, post_idx = 0;

node_t* build_tree(char* in, char* post, int in_start, int in_end, int* post_idx) {
    if (in_start > in_end) return NULL;
    
    node_t* root = (node_t*)malloc(sizeof(node_t));
    root->key_ = post[*post_idx];
    root->left_ = root->right_ = NULL;
    (*post_idx)--;
    
    if (in_start == in_end) return root;
    
    int in_root_idx;
    for (int i = in_start; i <= in_end; ++i)
        if (in[i] == root->key_) { in_root_idx = i; break; }
    
    // Build right first (postorder: left, right, root)
    root->right_ = build_tree(in, post, in_root_idx + 1, in_end, post_idx);
    root->left_ = build_tree(in, post, in_start, in_root_idx - 1, post_idx);
    
    return root;
}

void print_inorder(node_t* r) {
    if (r) { print_inorder(r->left_); printf("%c ", r->key_); print_inorder(r->right_); }
}

int main() {
    int post_idx = 9;  // Last index of postorder
    node_t* root = build_tree(inorder_str, postorder_str, 0, 9, &post_idx);
    printf("Reconstructed inorder: "); print_inorder(root); printf("\n");
    return 0;
}
```