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
    Start(["Insert (key, word)"]) --> Hash["Compute idx = key % TABLESIZE"]
    Hash --> Alloc["Allocate node n: n->key = key, strcpy(n->word, word)"]
    Alloc --> Link["n->next = head[idx]"]
    Link --> Update["head[idx] = n (Insert at front)"]
    Update --> Done(["Done"])
    
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
    subgraph Table["Table (Size: 11)"]
        I0["0"]
        I1["1: X (Occupied)"]
        I2["2: X (Occupied)"]
        I3["3"]
        I4["4"]
        I5["5: Free"]
        I6["6"]
        I7["7"]
        I8["8"]
        I9["9"]
        I10["10"]
    end
    
    Insert["Insert key (Hash=1)"] --> Try0["i=0: idx = 1 (Occupied)"]
    Try0 --> Try1["i=1: idx = (1 + 1²) % 11 = 2 (Occupied)"]
    Try1 --> Try2["i=2: idx = (1 + 2²) % 11 = 5 (Free)"]
    Try2 --> Place["Place key at Index 5"]
    
    style Table fill:#e3f2fd,stroke:#1565c0
    style Try0 fill:#ffcdd2,stroke:#c62828
    style Try1 fill:#ffcdd2,stroke:#c62828
    style Place fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
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

### Double Hashing Flowchart
```mermaid
flowchart TD
    Start(["Insert (key, word)"]) --> Hash["Compute initial probe: idx = key % TABLESIZE, i = 0"]
    Hash --> CheckInit{"elem[idx].in_use?"}
    
    CheckInit -- "No (Slot Free)" --> Place["elem[idx] = (key, word); in_use = 1; count++"]
    Place --> Done(["Done"])
    
    CheckInit -- "Yes (Collision)" --> CalcStep["Compute step size: step = 7 - (key % 7)"]
    CalcStep --> CheckFull{"i < TABLESIZE?"}
    
    CheckFull -- "Yes" --> NextProbe["i = i + 1; idx = (init_idx + i * step) % TABLESIZE"]
    NextProbe --> CheckSlot{"elem[idx].in_use?"}
    
    CheckSlot -- "No (Slot Free)" --> Place
    CheckSlot -- "Yes (Collision)" --> CheckFull
    
    CheckFull -- "No" --> Full["Error: Hash Table Full / Max Probes Reached"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Done fill:#e8f5e9,stroke:#2e7d32
    style Full fill:#ffebee,stroke:#c62828
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

### Double Hashing Trace Walkthrough
*Example: Table Size $M = 11$, Primary Hash $h_1(key) = key \pmod{11}$, Secondary Hash $h_2(key) = 7 - (key \pmod 7)$.*
*All three keys below initially collide at Index 3 ($25 \pmod{11} = 47 \pmod{11} = 69 \pmod{11} = 3$), but Double Hashing assigns distinct step sizes, dispersing them across the table without clustering:*

```mermaid
flowchart TD
    subgraph Collisions["Colliding Keys at Initial Index 3 (mod 11)"]
        K1["Key 25: 25 % 11 = 3"]
        K2["Key 47: 47 % 11 = 3 (Collision)"]
        K3["Key 69: 69 % 11 = 3 (Collision)"]
    end

    subgraph Steps["Secondary Hash: step = 7 - (key % 7)"]
        S2["47: step = 7 - (47 % 7) = 2"]
        S3["69: step = 7 - (69 % 7) = 1"]
    end

    subgraph Placements["Dispersed Slot Placements in Table (M=11)"]
        P1["Slot 3: Key 25 (Placed at Initial Index, i=0)"]
        P2["Slot 5: Key 47 ((3 + 1*2) % 11, i=1)"]
        P3["Slot 4: Key 69 ((3 + 1*1) % 11, i=1)"]
    end

    K1 --> P1
    K2 --> S2 --> P2
    K3 --> S3 --> P3

    style K1 fill:#e3f2fd,stroke:#1565c0
    style K2 fill:#fff3e0,stroke:#e65100
    style K3 fill:#f3e5f5,stroke:#7b1fa2
    style P1 fill:#e8f5e9,stroke:#2e7d32
    style P2 fill:#e8f5e9,stroke:#2e7d32
    style P3 fill:#e8f5e9,stroke:#2e7d32
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