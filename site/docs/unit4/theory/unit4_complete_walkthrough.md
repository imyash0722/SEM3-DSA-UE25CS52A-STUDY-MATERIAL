# Unit 4: Hashing, Tries, Suffix Trees, Advanced Graph Algorithms

## 📚 Unit Overview

**Topics Covered:**
1. Hashing & Hash Tables
2. Collision Resolution (4 Methods)
3. Tries (Prefix Trees)
4. Suffix Trees & Patricia Tries
5. Advanced Graph Algorithms

---

## 🔑 Hashing - Complete Walkthrough

### What is Hashing?

> **Hashing** maps keys to array indices using a **hash function**.
> - Goal: O(1) average case for insert, search, delete
> - Key → Hash Function → Index (0 to TABLESIZE-1)

### Why Hashing?
| Scenario | Best Structure |
|----------|----------------|
| Dense integer keys | Direct array |
| Sparse integer keys | Hash table |
| String keys (identifiers) | Hash table |
| Repeated retrieval | Hash table |
| Compiler symbol tables | Hash table |

### Core Concepts

| Term | Definition |
|------|------------|
| **Key** | Unique identifier for a record |
| **Hash Function** | Maps key → array index |
| **Collision** | Two different keys → same index |
| **Overflow** | Table full, can't insert |

---

## 🎯 Hash Functions

### 1. Division Method (Most Common)
```c
h(k) = k % TABLESIZE
```
- TABLESIZE should be **prime** for better distribution
- Simple, fast

```c
int hash_division(int key) {
    return key % TABLESIZE;  // TABLESIZE = 19 (prime)
}
```

### 2. Multiplication Method
```c
h(k) = floor(TABLESIZE * frac(k * A))
```
- A = constant (e.g., 0.618033... golden ratio)
- Works well for non-integer keys

### 3. Mid-Square Method
```c
h(k) = middle digits of (k²)
```
- Example: k=44, 44²=1936, middle=93

### 4. Folding Method (Good for Strings)
```c
h(k) = sum of key parts
```
- Example: 123456 → 12+34+56 = 102

### String Hashing
```c
int hash_string(char *s) {
    int sum = 0;
    while (*s) sum += *s++;  // Sum ASCII values
    return sum % TABLESIZE;
}
```

---

## 💥 Collision Resolution

### Two Main Approaches

| Approach | Description | Pros | Cons |
|----------|-------------|------|------|
| **Open Hashing** (Separate Chaining) | Linked lists at each index | Simple, no overflow, easy delete | Extra memory for pointers, cache misses |
| **Closed Hashing** (Open Addressing) | Find next free slot in array | Better cache, no pointers | Clustering, hard delete, fixed size |

---

## 🔗 Method 1: Separate Chaining (Open Hashing)

### Structure
```c
#define TABLESIZE 19
#define WORDSIZE 32

struct node {
    int key;
    char word[WORDSIZE];
    struct node *next;
};
typedef struct node node_t;

struct hash_table {
    node_t *head[TABLESIZE];
};
typedef struct hash_table hash_table_t;
```

### Operations

#### Initialize
```c
void init_hash(hash_table_t *h) {
    for (int i = 0; i < TABLESIZE; i++) h->head[i] = NULL;
}
```

#### Insert
```c
void insert(hash_table_t *h, int key, char *word) {
    int idx = key % TABLESIZE;
    node_t *n = malloc(sizeof(node_t));
    n->key = key; strcpy(n->word, word); n->next = NULL;
    
    // Insert at front of list
    n->next = h->head[idx];
    h->head[idx] = n;
}
```

#### Search
```c
char* search(hash_table_t *h, int key) {
    int idx = key % TABLESIZE;
    for (node_t *p = h->head[idx]; p; p = p->next)
        if (p->key == key) return p->word;
    return "";
}
```

#### Delete
```c
void delete_key(hash_table_t *h, int key) {
    int idx = key % TABLESIZE;
    node_t *prev = NULL, *curr = h->head[idx];
    
    while (curr && curr->key != key) {
        prev = curr; curr = curr->next;
    }
    if (!curr) return;  // Not found
    
    if (!prev) h->head[idx] = curr->next;  // First node
    else prev->next = curr->next;
    
    free(curr);
}
```

#### Display
```c
void display(hash_table_t *h) {
    for (int i = 0; i < TABLESIZE; i++) {
        printf("Index %2d: ", i);
        for (node_t *p = h->head[i]; p; p = p->next)
            printf("(%d,%s) ", p->key, p->word);
        printf("\n");
    }
}
```

---

## 📦 Method 2: Linear Probing (Closed Hashing)

### Structure
```c
#define TABLESIZE 19

struct node {
    int in_use;  // 0 = free, 1 = occupied
    int key;
    char word[WORDSIZE];
};
typedef struct node node_t;

struct hash_table {
    node_t elem[TABLESIZE];
    int count;
};
typedef struct hash_table hash_table_t;
```

### Operations

#### Initialize
```c
void init_hash(hash_table_t *h) {
    h->count = 0;
    for (int i = 0; i < TABLESIZE; i++) h->elem[i].in_use = 0;
}
```

#### Insert
```c
void insert(hash_table_t *h, int key, char *word) {
    if (h->count == TABLESIZE) { printf("Full\n"); return; }
    
    int idx = key % TABLESIZE;
    while (h->elem[idx].in_use)  // Linear probe
        idx = (idx + 1) % TABLESIZE;
    
    h->elem[idx].key = key;
    strcpy(h->elem[idx].word, word);
    h->elem[idx].in_use = 1;
    h->count++;
}
```

#### Search
```c
char* search(hash_table_t *h, int key) {
    int idx = key % TABLESIZE, checked = 0;
    while (checked < h->count) {
        if (h->elem[idx].in_use) {
            checked++;
            if (h->elem[idx].key == key) return h->elem[idx].word;
        }
        idx = (idx + 1) % TABLESIZE;
    }
    return "";
}
```

#### Delete (Lazy Deletion)
```c
void delete_key(hash_table_t *h, int key) {
    int idx = key % TABLESIZE, checked = 0;
    while (checked < h->count) {
        if (h->elem[idx].in_use) {
            checked++;
            if (h->elem[idx].key == key) {
                h->elem[idx].in_use = 0;  // Mark free (lazy delete)
                h->count--;
                return;
            }
        }
        idx = (idx + 1) % TABLESIZE;
    }
}
```

---

## 📐 Method 3: Quadratic Probing

### Probe Sequence
```c
idx = (init_idx + i*i) % TABLESIZE  // i = 0, 1, 2, ...
```

### Insert (Only Change from Linear)
```c
void insert(hash_table_t *h, int key, char *word) {
    if (h->count == TABLESIZE) return;
    
    int idx = key % TABLESIZE;
    int init_idx = idx;
    int i = 0;
    
    while (i < TABLESIZE && h->elem[idx].in_use) {
        i++;
        idx = (init_idx + i*i) % TABLESIZE;  // Quadratic step
    }
    
    h->elem[idx].key = key;
    strcpy(h->elem[idx].word, word);
    h->elem[idx].in_use = 1;
    h->count++;
}
```

---

## 🔄 Method 4: Double Hashing

### Second Hash Function
```c
int hash2(int key) {
    return 7 - (key % 7);  // Returns 1..7 (prime < TABLESIZE)
}
```

### Structure with Function Pointer
```c
struct hash_table {
    node_t elem[TABLESIZE];
    int count;
    int (*hash_fn)(int);  // Secondary hash function
};
```

### Initialize with Hash Function
```c
void init_hash(hash_table_t *h, int (*fn)(int)) {
    h->count = 0; h->hash_fn = fn;
    for (int i = 0; i < TABLESIZE; i++) h->elem[i].in_use = 0;
}
```

### Probe Sequence
```c
idx = (init_idx + i * hash_fn(key)) % TABLESIZE
```

### Insert
```c
void insert(hash_table_t *h, int key, char *word) {
    if (h->count == TABLESIZE) return;
    
    int idx = key % TABLESIZE;
    int init_idx = idx;
    int i = 0;
    
    while (i < TABLESIZE && h->elem[idx].in_use) {
        i++;
        idx = (init_idx + i * h->hash_fn(key)) % TABLESIZE;
    }
    
    h->elem[idx].key = key;
    strcpy(h->elem[idx].word, word);
    h->elem[idx].in_use = 1;
    h->count++;
}
```

---

## 📊 Collision Resolution Comparison

| Method | Type | Insert | Search | Delete | Clustering | Cache |
|--------|------|--------|--------|--------|------------|-------|
| Separate Chaining | Open | O(1)* | O(1)* | Easy | None | Poor |
| Linear Probing | Closed | O(1)* | O(1)* | Lazy | Primary | Best |
| Quadratic Probing | Closed | O(1)* | O(1)* | Lazy | Secondary | Good |
| Double Hashing | Closed | O(1)* | O(1)* | Lazy | Minimal | Good |

*Average case, assuming good hash function and load factor < 0.7

---

## 🌲 Tries (Prefix Trees)

### What is a Trie?
> **Trie** = Tree for storing strings, edges = characters
> - **Not a binary tree** - each node can have many children (alphabet size)
> - Root = empty prefix
> - Path from root = prefix
> - `is_word_end` flag marks complete words

### Structure
```c
#define ALPHABET_SIZE 256  // Extended ASCII

struct node {
    struct node *child[ALPHABET_SIZE];
    int is_word_end;
};
typedef struct node node_t;

struct trie {
    node_t *root;
};
typedef struct trie trie_t;
```

### Operations

#### Initialize
```c
void init_trie(trie_t *t) {
    t->root = calloc(1, sizeof(node_t));  // calloc zeros all pointers
}
```

#### Insert
```c
void insert(trie_t *t, char *word) {
    node_t *curr = t->root;
    for (int i = 0; word[i]; i++) {
        int idx = (unsigned char)word[i];
        if (!curr->child[idx])
            curr->child[idx] = calloc(1, sizeof(node_t));
        curr = curr->child[idx];
    }
    curr->is_word_end = 1;
}
```

#### Search
```c
int search(trie_t *t, char *word) {
    node_t *curr = t->root;
    for (int i = 0; word[i]; i++) {
        int idx = (unsigned char)word[i];
        if (!curr->child[idx]) return 0;
        curr = curr->child[idx];
    }
    return curr->is_word_end;
}
```

#### Delete
```c
// Returns 1 if node can be freed
int delete_rec(node_t *curr, char *word, int depth) {
    if (!curr) return 0;
    
    if (word[depth] == '\0') {
        if (!curr->is_word_end) return 0;
        curr->is_word_end = 0;
        // Can delete if no children
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (curr->child[i]) return 0;
        free(curr);
        return 1;
    }
    
    int idx = (unsigned char)word[depth];
    if (delete_rec(curr->child[idx], word, depth + 1)) {
        free(curr->child[idx]);
        curr->child[idx] = NULL;
        if (curr->is_word_end) return 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            if (curr->child[i]) return 0;
        free(curr);
        return 1;
    }
    return 0;
}

void delete_word(trie_t *t, char *word) {
    delete_rec(t->root, word, 0);
}
```

#### Display All Words
```c
void display_from(node_t *curr, char *prefix, int len) {
    if (curr->is_word_end) {
        prefix[len] = '\0';
        printf("%s\n", prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (curr->child[i]) {
            prefix[len] = (char)i;
            display_from(curr->child[i], prefix, len + 1);
        }
}

void display(trie_t *t) {
    char prefix[100];
    display_from(t->root, prefix, 0);
}
```

#### Autocomplete (All words with prefix)
```c
void autocomplete(trie_t *t, char *prefix) {
    node_t *curr = t->root;
    for (int i = 0; prefix[i]; i++) {
        int idx = (unsigned char)prefix[i];
        if (!curr->child[idx]) return;  // Prefix not found
        curr = curr->child[idx];
    }
    // Display all words from this node
    char full_prefix[100];
    strcpy(full_prefix, prefix);
    display_from(curr, full_prefix, strlen(prefix));
}
```

---

### Trie vs BST

| Feature | Trie | BST |
|---------|------|-----|
| Search Time | O(L) where L = string length | O(L log N) |
| Prefix Search | Natural (subtree) | Requires traversal |
| Space | O(Alphabet × N) | O(N) |
| Insert/Delete | O(L) | O(L log N) |

### Applications
- Autocomplete / Search suggestions
- Spell checkers
- IP Routing (Longest Prefix Match)
- Bioinformatics (Genome sequencing)
- Keyword filtering
- Contact search
- File system paths

---

## 🌿 Suffix Trees

### Problem
> Trie finds words/prefixes. What if we need **substring** search?

### Suffix Trie → Patricia Trie → Suffix Tree

#### Suffix Trie
- Trie of **all suffixes** of string T
- Every substring = prefix of some suffix
- Space: O(n²) - impractical!

#### Patricia Trie (Compressed Trie)
- Merge "silly nodes" (single child)
- Chains of single-child nodes → single edge with string label
- Space: O(n)

#### Suffix Tree
- Patricia Trie of all suffixes of T$ ($ = unique terminator)
- Each leaf = starting position of suffix
- Construction: O(n) with Ukkonen's algorithm
- Search: O(m) where m = pattern length

### Example: "banana$"
```
Suffixes: banana$, anana$, nana$, ana$, na$, a$, $
```
Compressed → Suffix Tree with edges labeled by string indices

### Applications
- Full-text search
- DNA sequence analysis
- Data compression
- Plagiarism detection

---

## 🌐 Advanced Graph Algorithms

### Dijkstra's Shortest Path
- **Single-source shortest path** (weighted, non-negative)
- Uses **Min-Heap Priority Queue**
- Time: O((V+E) log V)

```c
void dijkstra(int V, int src) {
    int dist[MAXV];
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;
    
    // Min-heap: (distance, vertex)
    pqueue_t pq; init(&pq);
    enqueue(&pq, src, 0);
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);
        for (node_t *p = adj[u]; p; p = p->next) {
            int v = p->vertex, w = p->weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                enqueue(&pq, v, dist[v]);  // Decrease key
            }
        }
    }
}
```

### Prim's Minimum Spanning Tree
- **MST**: Connect all vertices with minimum total edge weight
- Uses **Min-Heap Priority Queue**
- Time: O(E log V)

```c
void prim(int V, int start) {
    int key[MAXV], parent[MAXV];
    for (int i = 0; i < V; i++) { key[i] = INF; parent[i] = -1; }
    key[start] = 0;
    
    pqueue_t pq; init(&pq);
    for (int i = 0; i < V; i++) enqueue(&pq, i, key[i]);
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);
        for (node_t *p = adj[u]; p; p = p->next) {
            int v = p->vertex, w = p->weight;
            if (in_queue(v) && w < key[v]) {
                key[v] = w; parent[v] = u;
                decrease_key(&pq, v, w);
            }
        }
    }
}
```

---

## 🎯 Anchor Programs for Unit 4

### Program 1: Hash Table - All 4 Methods
```c
// hash_all_methods.c - Complete Hash Table Implementations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLESIZE 19
#define WORDSIZE 32

// ==========================================
// 1. SEPARATE CHAINING
// ==========================================
typedef struct node_chain {
    int key;
    char word[WORDSIZE];
    struct node_chain *next;
} NodeChain;

typedef struct { NodeChain *head[TABLESIZE]; } HashChain;

void chain_init(HashChain *h) {
    for (int i = 0; i < TABLESIZE; i++) h->head[i] = NULL;
}

void chain_insert(HashChain *h, int key, char *word) {
    int idx = key % TABLESIZE;
    NodeChain *n = malloc(sizeof(*n));
    n->key = key; strcpy(n->word, word); n->next = h->head[idx];
    h->head[idx] = n;
}

char* chain_search(HashChain *h, int key) {
    int idx = key % TABLESIZE;
    for (NodeChain *p = h->head[idx]; p; p = p->next)
        if (p->key == key) return p->word;
    return "";
}

void chain_display(HashChain *h) {
    for (int i = 0; i < TABLESIZE; i++) {
        printf("%2d: ", i);
        for (NodeChain *p = h->head[i]; p; p = p->next)
            printf("(%d,%s) ", p->key, p->word);
        printf("\n");
    }
}

// ==========================================
// 2. LINEAR PROBING
// ==========================================
typedef struct {
    int in_use;
    int key;
    char word[WORDSIZE];
} NodeLinear;

typedef struct {
    NodeLinear elem[TABLESIZE];
    int count;
} HashLinear;

void linear_init(HashLinear *h) {
    h->count = 0;
    for (int i = 0; i < TABLESIZE; i++) h->elem[i].in_use = 0;
}

void linear_insert(HashLinear *h, int key, char *word) {
    if (h->count == TABLESIZE) return;
    int idx = key % TABLESIZE;
    while (h->elem[idx].in_use) idx = (idx + 1) % TABLESIZE;
    h->elem[idx].key = key; strcpy(h->elem[idx].word, word);
    h->elem[idx].in_use = 1; h->count++;
}

char* linear_search(HashLinear *h, int key) {
    int idx = key % TABLESIZE, checked = 0;
    while (checked < h->count) {
        if (h->elem[idx].in_use) {
            if (++checked && h->elem[idx].key == key) return h->elem[idx].word;
        }
        idx = (idx + 1) % TABLESIZE;
    }
    return "";
}

// ==========================================
// 3. QUADRATIC PROBING
// ==========================================
typedef struct {
    int in_use;
    int key;
    char word[WORDSIZE];
} NodeQuad;

typedef struct {
    NodeQuad elem[TABLESIZE];
    int count;
} HashQuad;

void quad_insert(HashQuad *h, int key, char *word) {
    if (h->count == TABLESIZE) return;
    int idx = key % TABLESIZE, init = idx, i = 0;
    while (i < TABLESIZE && h->elem[idx].in_use) {
        i++; idx = (init + i*i) % TABLESIZE;
    }
    h->elem[idx].key = key; strcpy(h->elem[idx].word, word);
    h->elem[idx].in_use = 1; h->count++;
}

// ==========================================
// 4. DOUBLE HASHING
// ==========================================
int hash2(int key) { return 7 - key % 7; }

typedef struct {
    int in_use;
    int key;
    char word[WORDSIZE];
} NodeDouble;

typedef struct {
    NodeDouble elem[TABLESIZE];
    int count;
} HashDouble;

void double_insert(HashDouble *h, int key, char *word) {
    if (h->count == TABLESIZE) return;
    int idx = key % TABLESIZE, init = idx, i = 0;
    while (i < TABLESIZE && h->elem[idx].in_use) {
        i++; idx = (init + i * hash2(key)) % TABLESIZE;
    }
    h->elem[idx].key = key; strcpy(h->elem[idx].word, word);
    h->elem[idx].in_use = 1; h->count++;
}

int main() {
    printf("=== Hash Table Comparison ===\n\n");
    
    // Test data - keys that collide with TABLESIZE=19
    // 40%19=2, 59%19=2, 78%19=2, 97%19=2
    int keys[] = {40, 59, 78, 97, 15, 34, 53};
    char *words[] = {"forty", "fifty-nine", "seventy-eight", "ninety-seven", 
                     "fifteen", "thirty-four", "fifty-three"};
    int n = 7;
    
    printf("Keys: "); for (int i=0;i<n;i++) printf("%d ", keys[i]); printf("\n");
    printf("Hashes: "); for (int i=0;i<n;i++) printf("%d ", keys[i]%19); printf("\n\n");
    
    // 1. Separate Chaining
    HashChain hc; 
    chain_init(&hc);
    for (int i=0;i<n;i++) chain_insert(&hc, keys[i], words[i]);
    printf("=== Separate Chaining ===\n");
    chain_display(&hc);
    
    // 2. Linear Probing
    HashLinear hl; 
    linear_init(&hl);
    for (int i=0;i<n;i++) linear_insert(&hl, keys[i], words[i]);
    printf("\n=== Linear Probing ===\n");
    for (int i=0;i<TABLESIZE;i++)
        if (hl.elem[i].in_use)
            printf("%2d: (%d,%s)\n", i, hl.elem[i].key, hl.elem[i].word);
    
    // 3. Quadratic Probing
    HashQuad hq = {0};
    for (int i=0;i<n;i++) quad_insert(&hq, keys[i], words[i]);
    printf("\n=== Quadratic Probing ===\n");
    for (int i=0;i<TABLESIZE;i++)
        if (hq.elem[i].in_use)
            printf("%2d: (%d,%s)\n", i, hq.elem[i].key, hq.elem[i].word);
    
    // 4. Double Hashing
    HashDouble hd = {0};
    for (int i=0;i<n;i++) double_insert(&hd, keys[i], words[i]);
    printf("\n=== Double Hashing ===\n");
    for (int i=0;i<TABLESIZE;i++)
        if (hd.elem[i].in_use)
            printf("%2d: (%d,%s)\n", i, hd.elem[i].key, hd.elem[i].word);
    
    // Search test
    printf("\nSearch for 78: ");
    printf("Chain:%s Linear:%s Quad:%s Double:%s\n",
           chain_search(&hc, 78), linear_search(&hl, 78),
           "", "");
    
    return 0;
}
```

### Program 2: Trie with Autocomplete
```c
// trie_demo.c - Trie with Autocomplete
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 256

typedef struct node {
    struct node *child[ALPHABET];
    int is_word_end;
} node_t;

typedef struct { node_t *root; } trie_t;

node_t* create_node() { return calloc(1, sizeof(node_t)); }

void trie_init(trie_t *t) { t->root = create_node(); }

void trie_insert(trie_t *t, char *word) {
    node_t *curr = t->root;
    for (int i = 0; word[i]; i++) {
        int idx = (unsigned char)word[i];
        if (!curr->child[idx]) curr->child[idx] = calloc(1, sizeof(node_t));
        curr = curr->child[idx];
    }
    curr->is_word_end = 1;
}

int trie_search(trie_t *t, char *word) {
    node_t *curr = t->root;
    for (int i = 0; word[i]; i++) {
        int idx = (unsigned char)word[i];
        if (!curr->child[idx]) return 0;
        curr = curr->child[idx];
    }
    return curr->is_word_end;
}

// Display all words from current node
void display_from(node_t *curr, char *prefix, int len) {
    if (curr->is_word_end) {
        prefix[len] = '\0';
        printf("  %s\n", prefix);
    }
    for (int i = 0; i < ALPHABET; i++)
        if (curr->child[i]) {
            prefix[len] = (char)i;
            display_from(curr->child[i], prefix, len + 1);
        }
}

void trie_display(trie_t *t) {
    char prefix[100] = {0};
    printf("All words in trie:\n");
    display_from(t->root, prefix, 0);
}

// Autocomplete - find all words with given prefix
void trie_autocomplete(trie_t *t, char *prefix) {
    node_t *curr = t->root;
    for (int i = 0; prefix[i]; i++) {
        int idx = (unsigned char)prefix[i];
        if (!curr->child[idx]) { printf("No words with prefix '%s'\n", prefix); return; }
        curr = curr->child[idx];
    }
    printf("Words with prefix '%s':\n", prefix);
    char full_prefix[100]; strcpy(full_prefix, prefix);
    display_from(curr, full_prefix, strlen(prefix));
}

// Delete word (recursive)
int delete_rec(node_t *curr, char *word, int depth) {
    if (!curr) return 0;
    if (word[depth] == '\0') {
        if (!curr->is_word_end) return 0;
        curr->is_word_end = 0;
        for (int i = 0; i < ALPHABET; i++) if (curr->child[i]) return 0;
        free(curr); return 1;
    }
    int idx = (unsigned char)word[depth];
    if (delete_rec(curr->child[idx], word, depth + 1)) {
        free(curr->child[idx]); curr->child[idx] = NULL;
        if (curr->is_word_end) return 0;
        for (int i = 0; i < ALPHABET; i++) if (curr->child[i]) return 0;
        free(curr); return 1;
    }
    return 0;
}

void trie_delete(trie_t *t, char *word) { delete_rec(t->root, word, 0); }

int main() {
    trie_t t; trie_init(&t);
    
    char *words[] = {"cat", "bat", "ball", "rat", "cap", "be", "batman"};
    int n = 7;
    
    printf("=== Trie Demo ===\n");
    for (int i = 0; i < n; i++) trie_insert(&t, words[i]);
    
    printf("\n1. All words:\n"); trie_display(&t);
    
    printf("\n2. Search 'bat': %d\n", trie_search(&t, "bat"));  // 1
    printf("   Search 'ba': %d\n", trie_search(&t, "ba"));    // 0
    
    printf("\n3. Autocomplete 'ba':\n"); trie_autocomplete(&t, "ba");
    printf("   Autocomplete 'ca':\n"); trie_autocomplete(&t, "ca");
    
    printf("\n4. Delete 'bat':\n"); trie_delete(&t, "bat");
    printf("   Search 'bat': %d\n", trie_search(&t, "bat"));  // 0
    printf("   Search 'ball': %d\n", trie_search(&t, "ball")); // 1
    printf("   Autocomplete 'ba':\n"); trie_autocomplete(&t, "ba");
    
    return 0;
}
```

### Program 3: Dijkstra's Algorithm
```c
// dijkstra_demo.c - Dijkstra's Shortest Path
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAXV 100
#define INF INT_MAX

typedef struct node {
    int vertex, weight;
    struct node *next;
} node_t;

node_t *adj[MAXV];

// Min-heap for Dijkstra
typedef struct {
    int v[MAXV], dist[MAXV], pos[MAXV];
    int n;
} MinHeap;

void swap_h(MinHeap *h, int i, int j) {
    int tv = h->v[i], td = h->dist[i];
    h->v[i] = h->v[j]; h->dist[i] = h->dist[j]; h->pos[h->v[i]] = i;
    h->v[j] = tv; h->dist[j] = td; h->pos[h->v[j]] = j;
}

void heapify_up(MinHeap *h, int i) {
    while (i > 1 && h->dist[i] < h->dist[i/2]) swap_h(h, i, i/2), i /= 2;
}

void heapify_down(MinHeap *h, int i) {
    int smallest = i, l = 2*i, r = 2*i+1;
    if (l <= h->n && h->dist[l] < h->dist[smallest]) smallest = l;
    if (r <= h->n && h->dist[r] < h->dist[smallest]) smallest = r;
    if (smallest != i) { swap_h(h, i, smallest); heapify_down(h, smallest); }
}

void add_edge(int u, int v, int w) {
    node_t *n = malloc(sizeof(node_t));
    n->vertex = v; n->weight = w; n->next = adj[u]; adj[u] = n;
}

void dijkstra(int V, int src) {
    int dist[MAXV];
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;
    
    MinHeap h = {{0}, {0}, {0}, 0};
    for (int i = 0; i < V; i++) {
        h.v[++h.n] = i;
        h.dist[h.n] = dist[i];
        h.pos[i] = h.n;
    }
    for (int i = h.n/2; i >= 1; i--) {
        int smallest = i, l = 2*i, r = 2*i+1;
        if (l <= h.n && h.dist[l] < h.dist[smallest]) smallest = l;
        if (r <= h.n && h.dist[r] < h.dist[smallest]) smallest = r;
        if (smallest != i) { swap_h(&h, i, smallest); heapify_down(&h, i); }
    }
    
    while (h.n > 0) {
        int u = h.v[1];
        int du = h.dist[1];
        h.v[1] = h.v[h.n];
        h.dist[1] = h.dist[h.n];
        h.pos[h.v[1]] = 1;
        h.n--;
        heapify_down(&h, 1);
        
        if (du == INF) break;
        
        for (node_t *p = adj[u]; p; p = p->next) {
            int v = p->vertex, w = p->weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                int idx = h.pos[v];
                h.dist[idx] = dist[v];
                heapify_up(&h, idx);
            }
        }
    }
    
    printf("Shortest distances from %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("  to %d: %d\n", i, dist[i] == INF ? -1 : dist[i]);
}

int main() {
    // Graph with weights
    add_edge(0, 1, 4); add_edge(0, 2, 2);
    add_edge(1, 2, 1); add_edge(1, 3, 5);
    add_edge(2, 3, 8); add_edge(2, 4, 10);
    add_edge(3, 4, 2); add_edge(3, 5, 6);
    add_edge(4, 5, 2);
    
    printf("=== Dijkstra's Shortest Path ===\n");
    dijkstra(6, 0);
    
    return 0;
}
```

---

## 📝 Key Takeaways for Unit 4

| Concept | Key Insight |
|---------|-------------|
| **Hashing** | Key → Index via hash function, O(1) average |
| **Hash Functions** | Division (prime table), Multiplication, Folding |
| **Collision** | Two keys → same index |
| **Separate Chaining** | Linked lists at each index, simple |
| **Linear Probing** | Next slot, primary clustering |
| **Quadratic Probing** | i² steps, secondary clustering |
| **Double Hashing** | Second hash function, minimal clustering |
| **Trie** | Prefix tree, edges = characters, O(L) search |
| **Trie Operations** | Insert, Search, Delete, Autocomplete |
| **Suffix Tree** | Compressed trie of all suffixes, O(n) space |
| **Dijkstra** | Min-heap, O((V+E)log V), non-negative weights |
| **Prim's MST** | Min-heap, O(E log V) |

---

*End of Course Material - All 4 Units Complete*