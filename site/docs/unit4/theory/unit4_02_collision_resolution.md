# Unit 4: Collision Resolution

## 💥 Collision Resolution

### Two Main Approaches

| Approach | Description | Pros | Cons |
|----------|-------------|------|------|
| **Open Hashing** (Separate Chaining) | Linked lists at each index | Simple, no overflow, easy delete | Extra memory for pointers, cache misses |
| **Closed Hashing** (Open Addressing) | Find next free slot in array | Better cache, no pointers | Clustering, hard delete, fixed size |

### Collision Visualization
```mermaid
graph TD
    K1[Key 40] --> H[Hash Function]
    K2[Key 59] --> H
    H --> I1[Index 2]
    H --> I2[Index 2]
    I1 --> C1[Collision!]
    I2 --> C1
    C1 --> Resolve[Resolve with...]
    Resolve --> Chaining[Separate Chaining]
    Resolve --> Probing[Open Addressing]
    
    style K1 fill:#e3f2fd,stroke:#1565c0
    style C1 fill:#ffcdd2,stroke:#c62828,stroke-width:2px
```

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

### Separate Chaining Visualization
```mermaid
graph TD
    Table["Hash Table"] --> I0["Index 0: NULL"]
    Table --> I1["Index 1: NULL"]
    Table --> I2["Index 2"]
    Table --> I3["Index 3: NULL"]
    
    I2 --> N1["(40, 'forty')"]
    N1 --> N2["(59, 'fifty-nine')"]
    N2 --> N3["(78, 'seventy-eight')"]
    N3 --> N4["(97, 'ninety-seven')"]
    
    style Table fill:#e3f2fd,stroke:#1565c0
    style N1 fill:#e8f5e9,stroke:#2e7d32
    style N2 fill:#e8f5e9,stroke:#2e7d32
    style N3 fill:#e8f5e9,stroke:#2e7d32
    style N4 fill:#e8f5e9,stroke:#2e7d32
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

### Separate Chaining Insert Flow
```mermaid
flowchart TD
    Start(["Insert"]) --> Hash["Compute Hash"]
    Front["Insert at Front"]
    Front --> Link["new->next = head[idx]"]
    Link --> Update["head[idx] = new"]
    Update --> Done["Done"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Done fill:#ffebee,stroke:#c62828
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

### Separate Chaining Search Flow
```mermaid
flowchart TD
    Start([Search]) --> Hash[Compute Hash]
    Hash --> Traverse[Traverse List]
    Traverse --> Match{Key Match?}
    Match -- Yes --> Return[Return Value]
    Match -- No --> Next[Next Node]
    Next --> End{End of List?}
    End -- No --> Traverse
    End -- Yes --> NotFound[Return ""]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Return fill:#e8f5e9,stroke:#2e7d32
    style NotFound fill:#ffcdd2,stroke:#c62828
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

### Linear Probing Visualization
```mermaid
graph LR
    subgraph Table[Hash Table - TABLESIZE=7]
        I0[0: empty]
        I1[1: 10]
        I2[2: 20]
        I3[3: 30]
        I4[4: 40]
        I5[5: empty]
        I6[6: empty]
    end
    
    Insert["Insert 50 (50%7=1)"] --> P1{"Index 1 occupied?"}
    P1 -- "Yes (10)" --> P2{"Index 2 occupied?"}
    P2 -- "Yes (20)" --> P3{"Index 3 occupied?"}
    P3 -- "Yes (30)" --> P4{"Index 4 occupied?"}
    P4 -- "Yes (40)" --> P5{"Index 5 occupied?"}
    P5 -- "No (Empty)" --> Place["Place 50 at Index 5"]
    
    style Table fill:#e3f2fd,stroke:#1565c0
    style Place fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
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

### Linear Probing Flow
```mermaid
flowchart TD
    Start(["Insert"]) --> Hash["Hash: idx = key % SIZE"]
    Hash --> Check{"Slot Empty?"}
    Check -- Yes --> Place["Place Here"]
    Check -- No --> Probe["idx = (idx + 1) % SIZE"]
    Probe --> Check
    Place --> Done["Done"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Done fill:#ffebee,stroke:#c62828
```

---

## 📐 Method 3: Quadratic Probing

### Probe Sequence
```c
idx = (init_idx + i*i) % TABLESIZE  // i = 0, 1, 2, ...
```

### Quadratic Probing Visualization
```mermaid
graph LR
    subgraph Table[Table Size: 11]
        I0[0]
        I1[1: X]
        I2[2]
        I3[3]
        I4[4]
        I5[5]
        I6[6]
        I7[7]
        I8[8]
        I9[9]
        I10[10]
    end
    
    Insert[Insert: hash=1] --> Try0[i=0: Index 1]
    Try0 --> Occupied{Occupied?}
    Occupied -- Yes --> Try1[i=1: +1²=2]
    Try1 --> Check2{Index 2 empty?}
    Check2 -- Yes --> Place[Place at 2]
    Occupied -- No --> Place
    
    style Table fill:#e3f2fd,stroke:#1565c0
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

### Probe Sequence Comparison
```mermaid
graph TD
    Start["Initial Index: 1"] --> LP["Linear: +1, +2, +3..."]
    Start --> QP["Quadratic: +1², +2², +3²... (+1, +4, +9...)"]
    Start --> DH["Double Hash: +1·h2, +2·h2, +3·h2..."]
    
    LP --> LPSeq["Indices: 1, 2, 3, 4, 5..."]
    QP --> QPSeq["Indices: 1, 2, 5, 10, 17... (mod M)"]
    DH --> DHSeq["Indices: 1, 1+h2, 1+2h2, 1+3h2... (mod M)"]
    
    style Start fill:#e3f2fd,stroke:#1565c0
    style LPSeq fill:#e8f5e9,stroke:#2e7d32
    style QPSeq fill:#fff3e0,stroke:#e65100
    style DHSeq fill:#f3e5f5,stroke:#7b1fa2
```

---

## 🔄 Method 4: Double Hashing

### Second Hash Function
```c
int hash2(int key) {
    return 7 - (key % 7);  // Returns 1..7 (prime < TABLESIZE)
}
```

### Double Hashing Visualization
```mermaid
graph TD
    Start["Hash: idx = key % 11"] --> Probe{"Collision?"}
    Probe -- No --> Place["Place"]
    Probe -- Yes --> DH["Double Hash: h2 = 7 - (key % 7)"]
    DH --> Step["Step = hash2(key)"]
    Step --> Probe2{"Next slot free?"}
    Probe2 -- Yes --> Place
    Probe2 -- No --> AddStep["idx = (idx + step) % SIZE"]
    
    style Start fill:#e3f2fd,stroke:#1565c0
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

### Probe Sequence Comparison
```mermaid
graph TD
    Start["Initial Index: 1"] --> LP["Linear: +1, +2, +3..."]
    Start --> QP["Quadratic: +1², +2², +3²... (+1, +4, +9...)"]
    Start --> DH["Double Hash: +1·h2, +2·h2, +3·h2..."]
    
    LP --> LPSeq["Indices: 1, 2, 3, 4, 5..."]
    QP --> QPSeq["Indices: 1, 2, 5, 10, 17... (mod M)"]
    DH --> DHSeq["Indices: 1, 1+h2, 1+2h2, 1+3h2... (mod M)"]
    
    style Start fill:#e3f2fd,stroke:#1565c0
    style LPSeq fill:#e8f5e9,stroke:#2e7d32
    style QPSeq fill:#fff3e0,stroke:#e65100
    style DHSeq fill:#f3e5f5,stroke:#7b1fa2
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

### Comparison Visualization
```mermaid
graph LR
    subgraph Clustering[Clustering Tendency]
        C1[Separate Chaining: None]
        C2[Double Hashing: Minimal]
        C3[Quadratic: Secondary]
        C4[Linear: Primary]
    end
    
    subgraph Cache[Cache Performance]
        CA1[Linear: Best]
        CA2[Quadratic: Good]
        CA3[Double Hash: Good]
        CA4[Chaining: Poor]
    end
    
    style C1 fill:#e8f5e9,stroke:#2e7d32
    style C2 fill:#e8f5e9,stroke:#2e7d32
    style C3 fill:#fff3e0,stroke:#e65100
    style C4 fill:#ffcdd2,stroke:#c62828
```

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Collision** | Two keys → same index |
| **Separate Chaining** | Linked lists at each index, simple |
| **Linear Probing** | Next slot, primary clustering |
| **Quadratic Probing** | i² steps, secondary clustering |
| **Double Hashing** | Second hash function, minimal clustering |

---

*Next: [Tries →](./unit4_03_tries.md)*