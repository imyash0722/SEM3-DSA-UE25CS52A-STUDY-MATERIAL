# Unit 4: Tries (Prefix Trees)

## 🌲 Tries (Prefix Trees)

### What is a Trie?
> **Trie** = Tree for storing strings, edges = characters
> - **Not a binary tree** - each node can have many children (alphabet size)
> - Root = empty prefix
> - Path from root = prefix
> - `is_word_end` flag marks complete words

### Trie Structure Visualization
```mermaid
graph TD
    Root["Root (empty)"] --> A[a]
    A --> T[t]
    T --> C1[c]
    C1 --> E1[e]
    
    Root --> B[b]
    B --> A1[a]
    A1 --> T1[t]
    
    Root --> C[c]
    C --> A2[a]
    A2 --> T2[t]
    
    Root --> R[r]
    R --> A3[a]
    A3 --> T3[t]
    
    style Root fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style A fill:#e8f5e9,stroke:#2e7d32
    style B fill:#fff3e0,stroke:#e65100
    style C fill:#f3e5f5,stroke:#7b1fa2
    style R fill:#fff8e1,stroke:#f57f17
```

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

### Insert Visualization (Inserting "cat", "car", "card")
```mermaid
graph TD
    subgraph Step1["Insert 'cat'"]
        R1[Root] --> C1[c]
        C1 --> A1[a]
        T1["t: is_word_end=1"]
        A1 --> T1
    end
    
    subgraph Step2["Insert 'car'"]
        R2[Root] --> C2[c]
        C2 --> A2[a]
        T2["t: is_word_end=1"]
        R2b["r: is_word_end=1"]
        A2 --> T2
        A2 --> R2b
    end
    
    subgraph Step3["Insert 'card'"]
        R3[Root] --> C3[c]
        C3 --> A3[a]
        T3["t: is_word_end=1"]
        R3b["r: is_word_end=1"]
        D3["d: is_word_end=1"]
        A3 --> T3
        A3 --> R3b
        R3b --> D3
    end
    
    style R1 fill:#e3f2fd,stroke:#1565c0
    style A1 fill:#e8f5e9,stroke:#2e7d32
    style T1 fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style R2b fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
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

### Search Visualization
```mermaid
flowchart TD
    Start(["Search 'car'"]) --> Root["Start at Root"]
    Root --> C{"c"}
    C --> FoundC{"Exists?"}
    FoundC -- Yes --> A{"a"}
    A --> FoundA{"Exists?"}
    FoundA -- Yes --> R{"r"}
    R --> FoundR{"Exists?"}
    FoundR -- Yes --> CheckEnd{"is_word_end?"}
    CheckEnd -- Yes --> Found["FOUND"]
    CheckEnd -- No --> NotFound["NOT FOUND"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Found fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style NotFound fill:#ffcdd2,stroke:#c62828
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

### Delete Visualization
```mermaid
flowchart TD
    Start(["Delete 'car'"]) --> R1["Root: c"]
    R1 --> A1[a]
    A1 --> R1b[r]
    R1b --> CheckEnd{"is_word_end=1?"}
    CheckEnd -- Yes --> Unset["Unset is_word_end"]
    Unset --> CheckChildren{"Children?"}
    CheckChildren -- "Yes (d)" --> Keep["Keep Node"]
    CheckChildren -- No --> Free["Free Node"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Keep fill:#e8f5e9,stroke:#2e7d32
    style Free fill:#ffcdd2,stroke:#c62828
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

### Autocomplete Visualization
```mermaid
graph TD
    Root[Root] --> C[c]
    C --> A[a]
    A --> T["t: word_end"]
    A --> R["r: word_end"]
    R --> D["d: word_end"]
    
    Search["Search prefix 'ca'"] --> C
    C --> A
    A --> Results{"Results from here"}
    Results --> T
    Results --> R
    R --> D
    
    style Root fill:#e3f2fd,stroke:#1565c0
    style Results fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Trie** | Prefix tree, edges = characters, O(L) search |
| **Trie Operations** | Insert, Search, Delete, Autocomplete |

---

*Next: [Suffix Trees →](./unit4_04_suffix_trees.md)*