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