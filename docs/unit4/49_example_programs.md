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