# Unit 4: Example Programs

## 4.1 Graph Adjacency Matrix

### 4.1.1 Complete Graph Implementation with DFS/BFS

```c
// graph_adj_mat.c
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

struct graph {
    int n_vertices_;
    int n_edges_;
    int adj_mat_[MAXSIZE][MAXSIZE];
};
typedef struct graph graph_t;

void init_graph(graph_t *ptr_graph, int n_vertices, int n_edges) {
    ptr_graph->n_vertices_ = n_vertices;
    ptr_graph->n_edges_ = n_edges;
    for(int i = 0; i < MAXSIZE; ++i)
        for(int j = 0; j < MAXSIZE; ++j)
            ptr_graph->adj_mat_[i][j] = 0;
}

void add_edge(graph_t *ptr_graph, int from, int to) {
    if(from < MAXSIZE && to < MAXSIZE)
        ptr_graph->adj_mat_[from][to] = 1;
}

void dfs_recursive(int n, int a[][MAXSIZE], int visited[], int u) {
    visited[u] = 1;
    printf("visited %c ", u + 'A');
    for(int i = 0; i < n; ++i)
        if(a[u][i] && !visited[i])
            dfs_recursive(n, a, visited, i);
}

void dfs(graph_t *ptr_graph, int u) {
    int visited[MAXSIZE] = {0};
    dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_mat_, visited, u);
    printf("\n");
}

void bfs(graph_t *ptr_graph, int u) {
    int n = ptr_graph->n_vertices_;
    int visited[MAXSIZE] = {0};
    int q[MAXSIZE], front = 0, rear = 0;
    
    visited[u] = 1;
    q[rear++] = u;
    
    while(front != rear) {
        int v = q[front++];
        printf("visiting : %c\n", v + 'A');
        for(int i = 0; i < n; ++i)
            if(ptr_graph->adj_mat_[v][i] && !visited[i]) {
                visited[i] = 1;
                q[rear++] = i;
            }
    }
}

int to_visit(int v[], int n) {
    for(int i = 0; i < n; ++i)
        if(v[i] == 0) return i;
    return -1;
}

int connected_components_dfs(graph_t *ptr_graph) {
    int visited[MAXSIZE] = {0}, count = 0;
    int u = to_visit(visited, ptr_graph->n_vertices_);
    while(u != -1) {
        printf("Component %d: ", ++count);
        dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_mat_, visited, u);
        printf("\n");
        u = to_visit(visited, ptr_graph->n_vertices_);
    }
    return count;
}

int connected_components_bfs(graph_t *ptr_graph) {
    int visited[MAXSIZE] = {0}, count = 0;
    int u = to_visit(visited, ptr_graph->n_vertices_);
    while(u != -1) {
        printf("Component %d: ", ++count);
        bfs(ptr_graph, u);
        printf("\n");
        u = to_visit(visited, ptr_graph->n_vertices_);
    }
    return count;
}

// Path finding using DFS
int find_path_recursive(graph_t *ptr_graph, int path[], int* ptr_len,
                        int from, int to, int visited[]) {
    visited[from] = 1;
    int n = ptr_graph->n_vertices_;
    for(int i = 0; i < n; ++i) {
        if(ptr_graph->adj_mat_[from][i] && !visited[i]) {
            path[(*ptr_len)++] = i;
            if(i == to) return 1;
            return find_path_recursive(ptr_graph, path, ptr_len, i, to, visited);
        }
    }
    --(*ptr_len);  // Backtrack
    return 0;
}

int find_path_dfs(graph_t *ptr_graph, int path[], int* ptr_len, int from, int to) {
    int visited[MAXSIZE] = {0};
    path[(*ptr_len)++] = from;
    return find_path_recursive(ptr_graph, path, ptr_len, from, to, visited);
}

void disp_graph(graph_t *ptr_graph) {
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) {
        printf("%c: ", i + 'A');
        for(int j = 0; j < ptr_graph->n_vertices_; ++j)
            if(ptr_graph->adj_mat_[i][j]) printf("%c ", j + 'A');
        printf("\n");
    }
}

int main() {
    graph_t g;
    init_graph(&g, 8, 11);
    
    // Graph from notes
    add_edge(&g, 0, 1); add_edge(&g, 0, 2);
    add_edge(&g, 1, 2); add_edge(&g, 1, 3);
    add_edge(&g, 2, 4);
    add_edge(&g, 3, 4); add_edge(&g, 3, 5);
    add_edge(&g, 4, 6);
    add_edge(&g, 5, 6); add_edge(&g, 5, 7);
    add_edge(&g, 6, 7);
    
    printf("Graph:\n"); disp_graph(&g);
    
    printf("\nDFS from A: "); dfs(&g, 0);
    printf("\nBFS from A: "); bfs(&g, 0);
    
    printf("\nConnected Components (DFS):\n");
    connected_components_dfs(&g);
    
    int path[MAXSIZE], len = 0;
    printf("\nPath from A to H: ");
    if(find_path_dfs(&g, path, &len, 0, 7)) {
        for(int i = 0; i < len; ++i) printf("%c ", path[i] + 'A');
    } else printf("No path");
    printf("\n");
    
    return 0;
}
```

---

## 4.2 Graph Adjacency List

### 4.2.1 Complete Implementation with DFS/BFS/Path

```c
// graph_adj_list.c
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

struct node {
    int vertex_;
    struct node* next_;
};
typedef struct node node_t;

struct list {
    node_t* head_;
    node_t* tail_;
};
typedef struct list list_t;

struct graph {
    int n_vertices_;
    int n_edges_;
    list_t adj_list_[MAXSIZE];
};
typedef struct graph graph_t;

void init_graph(graph_t *ptr_graph, int n_vertices, int n_edges) {
    ptr_graph->n_vertices_ = n_vertices;
    ptr_graph->n_edges_ = n_edges;
    for(int i = 0; i < MAXSIZE; ++i)
        ptr_graph->adj_list_[i].head_ = ptr_graph->adj_list_[i].tail_ = NULL;
}

void add_edge(graph_t *ptr_graph, int from, int to) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->vertex_ = to; temp->next_ = NULL;
    if(!ptr_graph->adj_list_[from].head_)
        ptr_graph->adj_list_[from].head_ = ptr_graph->adj_list_[from].tail_ = temp;
    else {
        ptr_graph->adj_list_[from].tail_->next_ = temp;
        ptr_graph->adj_list_[from].tail_ = temp;
    }
}

void dfs_recursive(int n, list_t a[MAXSIZE], int visited[], int u) {
    visited[u] = 1;
    printf("visited %c ", u + 'A');
    node_t* temp = a[u].head_;
    while(temp) {
        int v = temp->vertex_;
        if(!visited[v]) dfs_recursive(n, a, visited, v);
        temp = temp->next_;
    }
}

void dfs(graph_t *ptr_graph, int u) {
    int visited[MAXSIZE] = {0};
    dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_list_, visited, u);
    printf("\n");
}

void bfs(graph_t *ptr_graph, int u) {
    int n = ptr_graph->n_vertices_;
    int visited[MAXSIZE] = {0};
    int q[MAXSIZE], front = 0, rear = 0;
    visited[u] = 1; q[rear++] = u;
    while(front != rear) {
        int v = q[front++];
        printf("visiting : %c\n", v + 'A');
        node_t* temp = ptr_graph->adj_list_[v].head_;
        while(temp) {
            int v2 = temp->vertex_;
            if(!visited[v2]) { visited[v2] = 1; q[rear++] = v2; }
            temp = temp->next_;
        }
    }
}

// Connected components
int connected_components_dfs(graph_t *ptr_graph) {
    int visited[MAXSIZE] = {0}, count = 0;
    int u;
    for(u = 0; u < ptr_graph->n_vertices_; ++u) if(!visited[u]) break;
    while(u < ptr_graph->n_vertices_) {
        printf("Component %d: ", ++count);
        dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_list_, visited, u);
        printf("\n");
        for(u = 0; u < ptr_graph->n_vertices_; ++u) if(!visited[u]) break;
    }
    return count;
}

// Path finding using BFS (with parent array)
int find_path_bfs(graph_t *ptr_graph, int parent[], int from, int to) {
    int n = ptr_graph->n_vertices_;
    int visited[MAXSIZE] = {0};
    int q[MAXSIZE], front = 0, rear = 0;
    
    visited[from] = 1; q[rear++] = from;
    
    while(front != rear) {
        int u = q[front++];
        node_t* temp = ptr_graph->adj_list_[u].head_;
        while(temp) {
            int v = temp->vertex_;
            if(!visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                if(v == to) return 1;
                q[rear++] = v;
            }
            temp = temp->next_;
        }
    }
    return 0;
}

void fill_path(int parent[], int path[], int* ptr_len, int to) {
    while(parent[to] != -1) {
        path[(*ptr_len)++] = to;
        to = parent[to];
    }
    path[(*ptr_len)++] = to;
    // Reverse
    for(int i = 0, j = *ptr_len - 1; i < j; ++i, --j) {
        int t = path[i]; path[i] = path[j]; path[j] = t;
    }
}

int find_path_bfs_wrapper(graph_t *ptr_graph, int path[], int* ptr_len, int from, int to) {
    int parent[MAXSIZE];
    for(int i = 0; i < MAXSIZE; ++i) parent[i] = -1;
    int res = find_path_bfs(ptr_graph, parent, from, to);
    if(res) fill_path(parent, path, ptr_len, to);
    return res;
}

void disp_graph(graph_t *ptr_graph) {
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) {
        printf("%c: ", i + 'A');
        node_t* temp = ptr_graph->adj_list_[i].head_;
        while(temp) { printf("%c ", temp->vertex_ + 'A'); temp = temp->next_; }
        printf("\n");
    }
}

int main() {
    graph_t g;
    init_graph(&g, 8, 11);
    
    add_edge(&g, 0, 1); add_edge(&g, 0, 2);
    add_edge(&g, 1, 2); add_edge(&g, 1, 3);
    add_edge(&g, 2, 4);
    add_edge(&g, 3, 4); add_edge(&g, 3, 5);
    add_edge(&g, 4, 6);
    add_edge(&g, 5, 6); add_edge(&g, 5, 7);
    add_edge(&g, 6, 7);
    
    printf("Graph:\n"); disp_graph(&g);
    printf("\nDFS from A: "); dfs(&g, 0);
    printf("\nBFS from A: "); bfs(&g, 0);
    
    printf("\nComponents:\n"); connected_components_dfs(&g);
    
    int path[MAXSIZE], len = 0;
    printf("\nPath A to H: ");
    if(find_path_bfs_wrapper(&g, path, &len, 0, 7)) {
        for(int i = 0; i < len; ++i) printf("%c ", path[i] + 'A');
    } else printf("No path");
    printf("\n");
    return 0;
}
```

---

## 4.3 Hash Tables

### 4.3.1 Separate Chaining

```c
// hash_chaining.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLESIZE 19
#define WORDSIZE 32

struct node {
    int key_;
    char word_[WORDSIZE];
    struct node* next_;
};
typedef struct node node_t;

struct hash_table {
    node_t* head_[TABLESIZE];
};
typedef struct hash_table hash_table_t;

void init_hash(hash_table_t* h) {
    for(int i = 0; i < TABLESIZE; ++i) h->head_[i] = NULL;
}

void deinit_hash(hash_table_t* h) {
    for(int i = 0; i < TABLESIZE; ++i) {
        node_t* curr = h->head_[i];
        while(curr) { node_t* n = curr->next_; free(curr); curr = n; }
        h->head_[i] = NULL;
    }
}

void insert_word(hash_table_t* h, int key, char s[]) {
    int idx = key % TABLESIZE;
    node_t* n = malloc(sizeof(node_t));
    n->key_ = key; strcpy(n->word_, s); n->next_ = h->head_[idx];
    h->head_[idx] = n;
}

void delete_key(hash_table_t* h, int key) {
    int idx = key % TABLESIZE;
    node_t *prev = NULL, *curr = h->head_[idx];
    while(curr && curr->key_ != key) { prev = curr; curr = curr->next_; }
    if(!curr) { printf("Key %d not found\n", key); return; }
    if(!prev) h->head_[idx] = curr->next_;
    else prev->next_ = curr->next_;
    free(curr);
    printf("Deleted key %d\n", key);
}

char* search(hash_table_t* h, int key) {
    int idx = key % TABLESIZE;
    for(node_t* p = h->head_[idx]; p; p = p->next_)
        if(p->key_ == key) return p->word_;
    return "";
}

void disp_hash(hash_table_t* h) {
    for(int i = 0; i < TABLESIZE; ++i) {
        printf("index %d: ", i);
        for(node_t* p = h->head_[i]; p; p = p->next_)
            printf("(%d,%s) ", p->key_, p->word_);
        printf("\n");
    }
}

int main() {
    hash_table_t h; init_hash(&h);
    insert_word(&h, 40, "apple");
    insert_word(&h, 19, "banana");
    insert_word(&h, 58, "cherry");  // Collision with 40 (58%19=1, 40%19=2)
    insert_word(&h, 77, "date");    // 77%19=1
    
    printf("Hash Table:\n"); disp_hash(&h);
    
    printf("Search 40: %s\n", search(&h, 40));
    printf("Search 77: %s\n", search(&h, 77));
    
    delete_key(&h, 19);
    printf("After delete 19:\n"); disp_hash(&h);
    
    deinit_hash(&h);
    return 0;
}
```

---

### 4.3.2 Linear Probing

```c
// hash_linear.c
#include <stdio.h>
#include <string.h>
#define TABLESIZE 19
#define WORDSIZE 32

struct node { int in_use_; int key_; char word_[WORDSIZE]; };
typedef struct node node_t;

struct hash_table { node_t elem_[TABLESIZE]; int count_; };
typedef struct hash_table hash_table_t;

void init_hash(hash_table_t* h) {
    h->count_ = 0;
    for(int i = 0; i < TABLESIZE; ++i) h->elem_[i].in_use_ = 0;
}

void insert_word(hash_table_t* h, int key, char word[]) {
    if(h->count_ == TABLESIZE) { printf("Table full\n"); return; }
    int idx = key % TABLESIZE;
    while(h->elem_[idx].in_use_) idx = (idx + 1) % TABLESIZE;
    h->elem_[idx].key_ = key; strcpy(h->elem_[idx].word_, word);
    h->elem_[idx].in_use_ = 1; ++h->count_;
}

void delete_key(hash_table_t* h, int key) {
    if(h->count_ == 0) { printf("Empty\n"); return; }
    int idx = key % TABLESIZE, checked = 0;
    while(checked < h->count_) {
        if(h->elem_[idx].in_use_) {
            ++checked;
            if(h->elem_[idx].key_ == key) {
                h->elem_[idx].in_use_ = 0; --h->count_;
                printf("Deleted %d\n", key); return;
            }
        }
        idx = (idx + 1) % TABLESIZE;
    }
    printf("Key not found\n");
}

char* search(hash_table_t* h, int key) {
    int idx = key % TABLESIZE, checked = 0;
    while(checked < h->count_) {
        if(h->elem_[idx].in_use_) {
            ++checked;
            if(h->elem_[idx].key_ == key) return h->elem_[idx].word_;
        }
        idx = (idx + 1) % TABLESIZE;
    }
    return "";
}

void disp_hash(hash_table_t* h) {
    for(int i = 0; i < TABLESIZE; ++i)
        if(h->elem_[i].in_use_)
            printf("index %d: key=%d word=%s\n", i, h->elem_[i].key_, h->elem_[i].word_);
}

int main() {
    hash_table_t h; init_hash(&h);
    insert_word(&h, 40, "apple");
    insert_word(&h, 59, "banana");  // 59%19=2 (collision with 40%19=2)
    insert_word(&h, 78, "cherry");  // 78%19=2
    insert_word(&h, 15, "date");
    disp_hash(&h);
    return 0;
}
```

---

### 4.3.3 Quadratic Probing

```c
// hash_quadratic.c
// Only changes from linear probing in insert/delete/search:

void insert_word(hash_table_t* h, int key, char word[]) {
    if(h->count_ == TABLESIZE) return;
    int idx = key % TABLESIZE;
    int init = idx;
    int i = 0;
    while(i < TABLESIZE && h->elem_[idx].in_use_) {
        ++i;
        idx = (init + i*i) % TABLESIZE;
    }
    h->elem_[idx].key_ = key; strcpy(h->elem_[idx].word_, word);
    h->elem_[idx].in_use_ = 1; ++h->count_;
}

void delete_key(hash_table_t* h, int key) {
    if(h->count_ == 0) return;
    int idx = key % TABLESIZE, init = idx, i = 0, checked = 0;
    while(checked < h->count_ && i < TABLESIZE) {
        if(h->elem_[idx].in_use_) {
            ++checked;
            if(h->elem_[idx].key_ == key) { h->elem_[idx].in_use_ = 0; --h->count_; return; }
        }
        ++i; idx = (init + i*i) % TABLESIZE;
    }
}
```

---

### 4.3.4 Double Hashing

```c
// hash_double.c
#include <stdio.h>
#define TABLESIZE 19

struct node { int in_use_; int key_; char word_[32]; };
typedef struct node node_t;

struct hash_table {
    node_t elem_[TABLESIZE];
    int count_;
    int (*hash_fn_)(int);
};
typedef struct hash_table hash_table_t;

int hash2(int key) { return 7 - key % 7; }  // Returns 1..7

void init_hash(hash_table_t* h, int (*fn)(int)) {
    h->count_ = 0; h->hash_fn_ = fn;
    for(int i = 0; i < TABLESIZE; ++i) h->elem_[i].in_use_ = 0;
}

void insert_word(hash_table_t* h, int key, char word[]) {
    if(h->count_ == TABLESIZE) return;
    int idx = key % TABLESIZE;
    int init = idx;
    int i = 0;
    while(i < TABLESIZE && h->elem_[idx].in_use_) {
        ++i;
        idx = (init + i * h->hash_fn_(key)) % TABLESIZE;
    }
    h->elem_[idx].key_ = key; strcpy(h->elem_[idx].word_, word);
    h->elem_[idx].in_use_ = 1; ++h->count_;
}
```

---

## 4.4 Trie (Prefix Tree)

```c
// trie.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 256

struct node { struct node* child[MAXSIZE]; int is_word_end; };
typedef struct node node_t;

struct trie { node_t* root_; };
typedef struct trie trie_t;

void init_trie(trie_t* t) { t->root_ = calloc(1, sizeof(node_t)); }

void insert_word(trie_t* t, char* s) {
    node_t* c = t->root_;
    for(int i = 0; s[i]; ++i) {
        int idx = (unsigned char)s[i];
        if(!c->child[idx]) c->child[idx] = calloc(1, sizeof(node_t));
        c = c->child[idx];
    }
    c->is_word_end = 1;
}

int search(trie_t* t, char* s) {
    node_t* c = t->root_;
    for(int i = 0; s[i]; ++i) {
        int idx = (unsigned char)s[i];
        if(!c->child[idx]) return 0;
        c = c->child[idx];
    }
    return c->is_word_end;
}

int delete_recursive(node_t* c, char* s, int depth) {
    if(!c) return 0;
    if(s[depth] == '\0') {
        if(!c->is_word_end) return 0;
        c->is_word_end = 0;
        for(int i = 0; i < MAXSIZE; ++i) if(c->child[i]) return 0;
        free(c); return 1;
    }
    int idx = (unsigned char)s[depth];
    if(delete_recursive(c->child[idx], s, depth + 1)) {
        free(c->child[idx]); c->child[idx] = NULL;
        if(c->is_word_end) return 0;
        for(int i = 0; i < MAXSIZE; ++i) if(c->child[i]) return 0;
        free(c); return 1;
    }
    return 0;
}

void delete_word(trie_t* t, char* s) { delete_recursive(t->root_, s, 0); }

void display_from_node(node_t* c, char* prefix, int len) {
    if(c->is_word_end) {
        prefix[len] = '\0';
        printf("%s\n", prefix);
    }
    for(int i = 0; i < MAXSIZE; ++i) if(c->child[i]) {
        prefix[len] = (char)i;
        display_from_node(c->child[i], prefix, len + 1);
    }
}

void display(trie_t* t) {
    char prefix[100] = {0};
    display_from_node(t->root_, prefix, 0);
}

void all_prefix(trie_t* t, char* s) {
    node_t* c = t->root_;
    for(int i = 0; s[i]; ++i) {
        int idx = (unsigned char)s[i];
        if(!c->child[idx]) return;
        c = c->child[idx];
    }
    char prefix[100]; strcpy(prefix, s);
    display_from_node(c, prefix, strlen(s));
}

void deinit_recursive(node_t* c) {
    if(!c) return;
    for(int i = 0; i < MAXSIZE; ++i) deinit_recursive(c->child[i]);
    free(c);
}

void deinit_trie(trie_t* t) { deinit_recursive(t->root_); }

int main() {
    trie_t t; init_trie(&t);
    insert_word(&t, "cat");
    insert_word(&t, "bat");
    insert_word(&t, "ball");
    insert_word(&t, "rat");
    insert_word(&t, "cap");
    insert_word(&t, "be");
    
    printf("All words:\n"); display(&t);
    
    printf("\nSearch 'bat': %d\n", search(&t, "bat"));
    printf("Search 'ba': %d\n", search(&t, "ba"));
    
    printf("\nPrefix 'ba':\n"); all_prefix(&t, "ba");
    
    delete_word(&t, "bat");
    printf("\nAfter deleting 'bat':\n"); display(&t);
    
    deinit_trie(&t);
    return 0;
}
```

---

## 4.5 Suffix Tree (Conceptual - Ukkonen's Algorithm O(n))

```c
// Suffix Tree is typically implemented using Ukkonen's algorithm
// O(n) construction, O(n) space
// Key structure: compressed trie of all suffixes of T$

// Node structure for suffix tree
struct suffix_node {
    int start;       // Start index in original string
    int* end;        // Pointer to end index (global for leaves)
    struct suffix_node* children[256];
    struct suffix_node* suffix_link;
    int leaf_index;  // For leaf nodes: starting position of suffix
};
typedef struct suffix_node suffix_node_t;

// Suffix tree built for "banana$"
// Suffixes: banana$, anana$, nana$, ana$, na$, a$, $
// 
// Root
//  ├─ $ (leaf 6)
//  ├─ a (internal)
//  │   ├─ n (internal)
//  │   │   ├─ a$ (leaf 3)
//  │   │   └─ na$ (leaf 1)
//  │   └─ $ (leaf 5)
//  ├─ b (internal)
//  │   └─ anana$ (leaf 0)
//  └─ n (internal)
//      ├─ a (internal)
//      │   ├─ $ (leaf 4)
//      │   └─ na$ (leaf 2)
//      └─ $ (leaf - not applicable)

// Search pattern in O(m) where m = pattern length
// Example: Search "ana"
// Root → 'a' → 'n' → 'a' → found!
// Leaves under this node: positions 1, 3 → substrings at index 1 and 3

// Applications:
// - Full-text search
// - DNA sequence analysis
// - Data compression
// - Plagiarism detection
```