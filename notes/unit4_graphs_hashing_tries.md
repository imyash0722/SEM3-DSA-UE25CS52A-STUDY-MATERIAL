# Unit 4: Graphs, Hashing, Tries, Suffix Trees

## 4.1 Graph Representations & Traversals

### 4.1.1 Adjacency Matrix Representation

**Structure:**
```c
#define MAXSIZE 10
struct graph {
    int n_vertices_;  // # of vertices
    int n_edges_;     // # of edges
    int adj_mat_[MAXSIZE][MAXSIZE];
};
typedef struct graph graph_t;
```

**Adjacency Matrix Properties:**
- V × V matrix
- `adj_mat_[i][j] = 1` if edge from vertex i to j (unweighted)
- `adj_mat_[i][j] = weight` if weighted
- For undirected graph: matrix is symmetric
- Space: O(V²)

**Interface:**
```c
void init_graph(graph_t *ptr_graph, int n_vertices, int n_edges);
void add_edge(graph_t *ptr_graph, int from, int to);
void dfs(graph_t *ptr_graph, int u);
void bfs(graph_t *ptr_graph, int u);
void disp(graph_t *ptr_graph);
void deinit_graph(graph_t *ptr_graph);
```

### 4.1.2 Adjacency List Representation

**Structure:**
```c
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
```

**Properties:**
- Space: O(V + E)
- More efficient for sparse graphs
- Each vertex has a list of adjacent vertices

---

## 4.2 Graph Traversals

### Depth First Search (DFS)

**Concept:** Explore as deeply as possible along one path before backtracking. Uses recursion (implicit stack) or explicit stack.

**DFS on Adjacency Matrix:**
```c
void dfs_recursive(int n, int a[n][MAXSIZE], int visited[], int u) {
    visited[u] = 1;
    printf("visited %c \n", u + 'A');
    for(int i = 0; i < n; ++i) {
        if(a[u][i] && !visited[i]) {
            dfs_recursive(n, a, visited, i);
        }
    }
}

void dfs(graph_t *ptr_graph, int u) {
    int visited[MAXSIZE];
    for(int i = 0; i < ptr_graph->n_vertices_; ++i)
        visited[i] = 0;
    dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_mat_, visited, u);
    printf("\n");
}
```

**DFS on Adjacency List:**
```c
void dfs_recursive(int n, list_t a[MAXSIZE], int visited[], int u) {
    visited[u] = 1;
    printf("visited %c \n", u + 'A');
    node_t* temp = a[u].head_;
    int v;
    while(temp) {
        v = temp->vertex_;
        if(!visited[v]) {
            dfs_recursive(n, a, visited, v);
        }
        temp = temp->next_;
    }
}
```

**DFS Traversal Example:** A → B → C → E → D → F → G → H

---

### Breadth First Search (BFS)

**Concept:** Visit neighbours of a given node before going to the next. Uses a queue.

**BFS on Adjacency Matrix:**
```c
void bfs(graph_t *ptr_graph, int u) {
    int n = ptr_graph->n_vertices_;
    queue_t q; init_queue(&q);
    int visited[MAXSIZE];
    for(int i = 0; i < n; ++i) visited[i] = 0;
    int v;
    visited[u] = 1; enqueue(&q, u);
    while(!is_empty(&q)) {
        v = dequeue(&q);
        printf("visiting : %c\n", v + 'A');
        for(int i = 0; i < n; ++i) {
            if(ptr_graph->adj_mat_[v][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
    deinit_queue(&q);
}
```

**BFS on Adjacency List:**
```c
void bfs(graph_t *ptr_graph, int u) {
    queue_t q; init_queue(&q);
    int visited[MAXSIZE];
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) visited[i] = 0;
    int v;
    visited[u] = 1; enqueue(&q, u);
    while(!is_empty(&q)) {
        u = dequeue(&q);
        printf("visiting : %c\n", u + 'A');
        node_t* temp = ptr_graph->adj_list_[u].head_;
        while(temp) {
            v = temp->vertex_;
            if(!visited[v]) {
                visited[v] = 1;
                enqueue(&q, v);
            }
            temp = temp->next_;
        }
    }
    deinit_queue(&q);
}
```

**BFS Traversal Example:** A, B, C, D, E, F, G, H

---

### DFS vs BFS Comparison

| Aspect | DFS | BFS |
|--------|-----|-----|
| Data Structure | Stack (implicit recursion) | Queue |
| Traversal Order | Deep first, then backtrack | Level by level |
| Path Finding | Finds a path, not necessarily shortest | Finds shortest path (unweighted) |
| Memory | O(h) where h = height | O(w) where w = max width |
| Connected Components | ✓ | ✓ |
| Cycle Detection | ✓ | ✓ |
| Topological Sort | ✓ | - |
| Bipartite Check | ✓ | ✓ |

---

## 4.3 Connected Components

**Concept:** Two vertices are connected if there's a path between them. A connected component = all vertices where every pair is connected.

**Algorithm:**
1. Initialize `visited[]` array to 0
2. Find unvisited vertex using `to_visit()`
3. Run DFS/BFS from that vertex → marks one component
4. Repeat until all vertices visited

```c
int to_visit(int v[], int n) {
    for(int i = 0; i < n; ++i)
        if(v[i] == 0) return i;
    return -1;
}

int connected_components(graph_t *ptr_graph) {
    int visited[MAXSIZE], count = 0;
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) visited[i] = 0;
    int u = to_visit(visited, ptr_graph->n_vertices_);
    while(u != -1) {
        printf("Component %d: ", ++count);
        dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_mat_, visited, u);
        // or bfs(ptr_graph, u, visited);
        printf("\n");
        u = to_visit(visited, ptr_graph->n_vertices_);
    }
    return count;
}
```

**Works with:** Adjacency Matrix + DFS, Adjacency Matrix + BFS, Adjacency List + DFS, Adjacency List + BFS

---

## 4.4 Path Finding

### Path using DFS (Adjacency Matrix)

```c
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

int find_path(graph_t *ptr_graph, int path[], int* ptr_len, int from, int to) {
    int visited[MAXSIZE];
    path[(*ptr_len)++] = from;
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) visited[i] = 0;
    return find_path_recursive(ptr_graph, path, ptr_len, from, to, visited);
}
```

**Key Idea:** Add to path when going deeper, remove when backtracking.

### Path using BFS (Adjacency List)

```c
int find_path_bfs(graph_t *ptr_graph, int parent[], int from, int to) {
    queue_t q; init_queue(&q);
    int visited[MAXSIZE] = {0};
    int parent[MAXSIZE];  // Track parent of each node
    for(int i = 0; i < n; ++i) parent[i] = -1;
    
    visited[from] = 1; enqueue(&q, from);
    while(!is_empty(&q)) {
        int u = dequeue(&q);
        node_t* temp = ptr_graph->adj_list_[u].head_;
        while(temp) {
            int v = temp->vertex_;
            if(!visited[v]) {
                visited[v] = 1;
                parent[v] = u;  // v was reached from u
                if(v == to) return 1;
                enqueue(&q, v);
            }
            temp = temp->next_;
        }
    }
    deinit_queue(&q);
    return 0;
}

// Reconstruct path from parent array
void fill_path(int parent[], int path[], int* ptr_len, int to) {
    while(parent[to] != -1) {
        path[(*ptr_len)++] = to;
        to = parent[to];
    }
    path[(*ptr_len)++] = to;
    reverse(path, *ptr_len);  // Reverse to get from→to order
}
```

---

## 4.5 Hash Tables

### Concepts

| Term | Definition |
|------|------------|
| **Key** | Unique identifier for a record |
| **Hash Function** | Maps key → array index (0 to TABLESIZE-1) |
| **Collision** | Different keys → same index |
| **Overflow** | Table full, can't insert more |

### Hash Functions

1. **Division Method:** `h(k) = k % TABLESIZE`
2. **Multiplication Method:** `h(k) = floor(TABLESIZE * frac(k * A))`
3. **Mid-square Method:** Square key, use middle digits
4. **Folding Method:** Split key, add parts (e.g., 123456 → 12+34+56 = 102)

### Collision Resolution

#### Open Hashing (Separate Chaining)
- **Structure:** Array of linked lists
- **Collision:** Append to list at that index
- **Pros:** Simple, graceful degradation, easy deletion
- **Cons:** Extra pointer memory, poor cache locality
- **Table Size:** Can store more keys than array size

```c
struct node { int key_; char word_[WORDSIZE]; struct node *next_; };
struct hash_table { struct node *head_[TABLESIZE]; };
```

#### Closed Hashing (Open Addressing)
- **Structure:** Single array, all keys in table
- **Collision:** Probe for next empty slot
- **Table Size ≥ #keys**
- **Pros:** Better cache performance, no pointers
- **Cons:** Clustering, sharp performance drop when dense, lazy deletion needed

**Probing Methods:**
1. **Linear Probing:** `index = (index + 1) % TABLESIZE`
2. **Quadratic Probing:** `index = (init_index + i*i) % TABLESIZE`
3. **Double Hashing:** `index = (init_index + i * hash2(key)) % TABLESIZE`

---

## 4.6 Hash Table Implementations

### 4.6.1 Separate Chaining (Open Hashing)

```c
#define TABLESIZE 19
#define WORDSIZE 32

struct node {
    int key_;
    char word_[WORDSIZE];
    struct node *next_;
};
typedef struct node node_t;

struct hash_table {
    struct node *head_[TABLESIZE];
};
typedef struct hash_table hash_table_t;

void init_hash_table(hash_table_t *ptr_hash) {
    for(int i = 0; i < TABLESIZE; ++i) ptr_hash->head_[i] = NULL;
}

void insert_word(hash_table_t *ptr_hash, int key, char s[]) {
    int index = key % TABLESIZE;
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->key_ = key; strcpy(temp->word_, s); temp->next_ = NULL;
    temp->next_ = ptr_hash->head_[index];
    ptr_hash->head_[index] = temp;
}

void delete_key(hash_table_t *ptr_hash, int key) {
    int index = key % TABLESIZE;
    node_t *prev = NULL, *curr = ptr_hash->head_[index];
    while(curr && curr->key_ != key) { prev = curr; curr = curr->next_; }
    if(!curr) return;  // Not found
    if(!prev) ptr_hash->head_[index] = curr->next_;
    else prev->next_ = curr->next_;
    free(curr);
}

char* search(hash_table_t *ptr_hash, int key) {
    int index = key % TABLESIZE;
    for(node_t* p = ptr_hash->head_[index]; p; p = p->next_)
        if(p->key_ == key) return p->word_;
    return "";
}
```

---

### 4.6.2 Linear Probing (Closed Hashing)

```c
#define TABLESIZE 19

struct node {
    int in_use_;  // 0 = free, 1 = occupied
    int key_;
    char word_[WORDSIZE];
};
typedef struct node node_t;

struct hash_table {
    struct node elem_[TABLESIZE];
    int count_;
};
typedef struct hash_table hash_table_t;

void insert_word(hash_table_t *ptr_hash_table, int key, char word[]) {
    if(ptr_hash_table->count_ == TABLESIZE) return;  // Full
    int index = key % TABLESIZE;
    while(ptr_hash_table->elem_[index].in_use_ != 0)
        index = (index + 1) % TABLESIZE;  // Linear probe
    ptr_hash_table->elem_[index].key_ = key;
    strcpy(ptr_hash_table->elem_[index].word_, word);
    ptr_hash_table->elem_[index].in_use_ = 1;
    ++ptr_hash_table->count_;
}

void delete_key(hash_table_t *ptr_hash_table, int key) {
    if(ptr_hash_table->count_ == 0) return;
    int index = key % TABLESIZE;
    int i = 0;
    while(i < ptr_hash_table->count_) {
        if(ptr_hash_table->elem_[index].in_use_) {
            ++i;
            if(ptr_hash_table->elem_[index].key_ == key) {
                ptr_hash_table->elem_[index].in_use_ = 0;
                --ptr_hash_table->count_;
                return;
            }
        }
        index = (index + 1) % TABLESIZE;
    }
}

char* search(hash_table_t *ptr_hash_table, int key) {
    int index = key % TABLESIZE;
    int i = 0;
    while(i < ptr_hash_table->count_) {
        if(ptr_hash_table->elem_[index].in_use_) {
            ++i;
            if(ptr_hash_table->elem_[index].key_ == key)
                return ptr_hash_table->elem_[index].word_;
        }
        index = (index + 1) % TABLESIZE;
    }
    return "";
}
```

---

### 4.6.3 Quadratic Probing

```c
// Only change from linear probing:
int index = key % TABLESIZE;
int init_index = index;
int i = 0;
while(i < TABLESIZE && ptr_hash_table->elem_[index].in_use_ != 0) {
    ++i;
    index = (init_index + i*i) % TABLESIZE;  // Quadratic step
}
```

---

### 4.6.4 Double Hashing

```c
struct hash_table {
    struct node elem_[TABLESIZE];
    int count_;
    int (*hash_fn_)(int);  // Secondary hash function
};

int hash_double(int key) { return 7 - key % 7; }  // Returns 1..7

void init_hash_table(hash_table_t *ptr_hash_table, int (*hash_fn)(int)) {
    // ... init count_ and in_use_
    ptr_hash_table->hash_fn_ = hash_fn;
}

// Probe sequence:
index = (init_index + i * ptr_hash_table->hash_fn_(key)) % TABLESIZE;
```

---

### Collision Resolution Comparison

| Method | Type | Space | Clustering | Deletion | Cache |
|--------|------|-------|------------|----------|-------|
| Separate Chaining | Open | Extra pointers | None | Easy | Poor |
| Linear Probing | Closed | Array only | Primary | Lazy delete | Excellent |
| Quadratic Probing | Closed | Array only | Secondary | Lazy delete | Good |
| Double Hashing | Closed | Array only | Minimal | Lazy delete | Good |

---

## 4.7 Tries (Prefix Trees)

### Concept
- Tree-based structure for string storage/retrieval
- Edges represent characters, not nodes
- Root = empty prefix
- Each node: array of child pointers (size = alphabet)
- `is_word_end` flag marks complete words
- **Not a binary tree** - each node can have many children (e.g., 256 for ASCII)

### Structure

```c
#define MAXSIZE 256  // Extended ASCII

struct node {
    struct node *child[MAXSIZE];
    int is_word_end;
};
typedef struct node node_t;

struct trie {
    node_t* root_;
};
typedef struct trie trie_t;
```

### Operations

#### Insert
```c
void insert_word(trie_t *ptr_tree, char* s) {
    node_t* curr = ptr_tree->root_;
    for(int i = 0; s[i]; ++i) {
        int idx = (unsigned char)s[i];
        if(!curr->child[idx]) {
            curr->child[idx] = (node_t*)calloc(1, sizeof(node_t));
        }
        curr = curr->child[idx];
    }
    curr->is_word_end = 1;
}
```

#### Search
```c
int search(trie_t *ptr_trie, char* s) {
    node_t* curr = ptr_trie->root_;
    for(int i = 0; s[i]; ++i) {
        int idx = (unsigned char)s[i];
        if(!curr->child[idx]) return 0;
        curr = curr->child[idx];
    }
    return curr->is_word_end;
}
```

#### Delete
```c
// Recursive: returns 1 if node can be deleted
int delete_recursive(node_t* curr, char* s, int depth) {
    if(!curr) return 0;
    if(s[depth] == '\0') {
        if(!curr->is_word_end) return 0;
        curr->is_word_end = 0;
        // Can delete if no children
        for(int i = 0; i < MAXSIZE; ++i) if(curr->child[i]) return 0;
        free(curr); return 1;
    }
    int idx = (unsigned char)s[depth];
    if(delete_recursive(curr->child[idx], s, depth + 1)) {
        free(curr->child[idx]);
        curr->child[idx] = NULL;
        if(curr->is_word_end) return 0;
        for(int i = 0; i < MAXSIZE; ++i) if(curr->child[i]) return 0;
        free(curr); return 1;
    }
    return 0;
}
```

#### All Prefix (Autocomplete)
```c
void all_prefix(trie_t *ptr_trie, char* s) {
    node_t* curr = ptr_trie->root_;
    for(int i = 0; s[i]; ++i) {
        int idx = (unsigned char)s[i];
        if(!curr->child[idx]) return;
        curr = curr->child[idx];
    }
    // Display all words from this node
    display_from_node(curr, s);
}
```

---

### Trie vs BST

| Feature | Trie | BST |
|---------|------|-----|
| Search Time | O(L) where L = string length | O(L log N) |
| Prefix Search | Natural (subtree) | Requires traversal |
| Space | O(Alphabet × N) | O(N) |
| Alphabet | Fixed size | Any comparable |

---

### Applications of Trie
- Autocomplete / Search suggestions
- Spell checkers / Auto-correct
- IP Routing (Longest Prefix Matching)
- Bioinformatics / Genome sequencing
- Keyword filtering / Content moderation
- Contact name search
- File system paths
- Word games (Scrabble, Boggle)

---

## 4.8 Suffix Trees

### Suffix Trie → Patricia Trie → Suffix Tree

**Suffix Trie:** Trie of all suffixes of string T
- Space: O(n²) where n = |T|
- Every suffix ends in leaf
- Every substring = prefix of some suffix

**Patricia Trie (Compressed Trie):**
- Merge "silly nodes" (internal nodes with exactly one child)
- Chains of single-child nodes → single edge with string label
- Space: O(n)

**Suffix Tree:**
- Patricia Trie of all suffixes of T$ (where $ = unique terminator)
- Each leaf labeled with suffix starting position
- Construction: O(n) with Ukkonen's algorithm (beyond course scope)
- Space: O(n)
- Search: O(m) where m = pattern length

---

## 4.9 Example Programs

### 4.9.1 Graph Adjacency Matrix + DFS/BFS

```c
// graph_adj_mat.c
#include <stdio.h>
#define MAXSIZE 10

struct graph { int n_vertices_, n_edges_; int adj_mat_[MAXSIZE][MAXSIZE]; };
typedef struct graph graph_t;

void init_graph(graph_t *g, int n, int e) { g->n_vertices_ = n; g->n_edges_ = e; }

void add_edge(graph_t *g, int from, int to) { g->adj_mat_[from][to] = 1; }

void dfs_recursive(int n, int a[][MAXSIZE], int visited[], int u) {
    visited[u] = 1; printf("%c ", u + 'A');
    for(int i = 0; i < n; ++i) if(a[u][i] && !visited[i]) dfs_recursive(n, a, visited, i);
}

void bfs(graph_t *g, int u) {
    int n = g->n_vertices_;
    int visited[MAXSIZE] = {0};
    int q[MAXSIZE], front = 0, rear = 0;
    visited[u] = 1; q[rear++] = u;
    while(front != rear) {
        int v = q[front++];
        printf("%c ", v + 'A');
        for(int i = 0; i < n; ++i) if(g->adj_mat_[v][i] && !visited[i]) {
            visited[i] = 1; q[rear++] = i;
        }
    }
}
```

### 4.9.2 Hash Table - Separate Chaining

```c
// hash_chaining.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLESIZE 19
#define WORDSIZE 32

struct node { int key_; char word_[WORDSIZE]; struct node *next_; };
typedef struct node node_t;

struct hash_table { node_t* head_[TABLESIZE]; };
typedef struct hash_table hash_table_t;

void insert(hash_table_t* h, int key, char* s) {
    int idx = key % TABLESIZE;
    node_t* n = malloc(sizeof(node_t)); n->key_ = key; strcpy(n->word_, s); n->next_ = h->head_[idx];
    h->head_[idx] = n;
}
```

### 4.9.3 Trie Implementation

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

void insert(trie_t* t, char* s) {
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
```

---

## 4.10 Summary: Unit 4 Key Topics

| Topic | Key Concepts | Implementations |
|-------|--------------|-----------------|
| Graph Representation | Adjacency Matrix, Adjacency List | C structs |
| Traversal | DFS (stack/recursion), BFS (queue) | Both representations |
| Connected Components | to_visit + DFS/BFS loop | 4 combinations |
| Path Finding | DFS (backtrack), BFS (parent array) | Matrix + DFS, List + BFS |
| Hash Tables | Key→Index, Collision, Overflow | 4 collision methods |
| Tries | Prefix tree, char edges, end flag | Array of pointers |
| Suffix Trees | Compressed trie of all suffixes | Ukkonen's algorithm O(n) |

---

## Exam-Relevant MCQ Patterns

1. **Graph Traversal:** "Which data structure is used for BFS?" → Queue
2. **DFS vs BFS:** "DFS finds shortest path?" → False (BFS does for unweighted)
3. **Hash Collision:** "Separate chaining uses what?" → Linked lists
4. **Linear Probing:** "Next index formula?" → (index + 1) % TABLESIZE
5. **Trie Search Time:** O(L) where L = string length
6. **Suffix Tree Space:** O(n) after compression
7. **Connected Components:** "Graph not connected → DFS from unvisited"
8. **Path Finding:** "BFS uses parent array, DFS uses path array + backtrack"