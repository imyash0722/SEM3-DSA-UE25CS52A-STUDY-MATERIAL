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