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