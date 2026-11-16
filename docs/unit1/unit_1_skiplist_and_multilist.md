# Unit 1: Skiplist and Multilist

## Skiplist

**Problem**: Searching in sorted linked list is O(n)

**Solution**: Multiple levels with "express lanes"

```
Level 2:  10 ──────────→ 40 ──────────→ 70 ─────→ 100
           ↓              ↓              ↓
Level 1:  10 ──→ 20 ──→ 40 ──→ 50 ──→ 70 ──→ 100
           ↓       ↓       ↓       ↓       ↓
Level 0:  10 → 20 → 30 → 40 → 50 → 60 → 70 → 80 → 90 → 100
```

**Search for 90:**
1. Level 2: 10 → 40 → 70 → (100 > 90, drop down)
2. Level 1: 70 → 100 (drop down)
3. Level 0: 70 → 80 → 90 (found!)

**Properties:**
- Bottom level = all elements
- Each higher level ≈ half nodes of level below
- Search/insert/delete: O(log n) expected
- Used in: Redis, LevelDB, concurrent data structures

## Multilist

**Concept**: One node participates in multiple lists

**Sparse Matrix Example:**
```
Row lists: Each row has list of non-zero elements
Col lists: Each column has list of non-zero elements
One physical node → appears in both row and column list
```

**Student-Course Example:**
- Student node → list of courses
- Course node → list of students
- Single enrollment node → in both lists

**Benefits:**
- Avoids duplicate data
- Single update point
- Multiple access paths

**Costs:**
- Complex pointer management
- Complex insertion/deletion