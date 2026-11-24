# Unit 4: Hashing & Hash Tables

## 🔑 Hashing - Complete Walkthrough

### What is Hashing?

> **Hashing** maps keys to array indices using a **hash function**.
> - Goal: O(1) average case for insert, search, delete
> - Key → Hash Function → Index (0 to TABLESIZE-1)

### Hashing Process Visualization
```mermaid
flowchart LR
    Key[Key] --> Hash[Hash Function]
    Hash --> Index[Array Index]
    Index --> Table[Hash Table]
    
    style Key fill:#e3f2fd,stroke:#1565c0
    style Hash fill:#fff3e0,stroke:#e65100
    style Index fill:#e8f5e9,stroke:#2e7d32
    style Table fill:#f3e5f5,stroke:#7b1fa2
```

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

### Division Method Visualization
```mermaid
flowchart LR
    K[Key: 40] --> Mod[Modulo 19]
    Mod --> R[Result: 2]
    R --> Table[(Index 2)]
    
    K2[Key: 59] --> Mod2[Modulo 19]
    Mod2 --> R2[Result: 2]
    R2 --> Table2[(Index 2)]
    
    Table -.->|COLLISION!| Table2
    
    style K fill:#e3f2fd,stroke:#1565c0
    style K2 fill:#e3f2fd,stroke:#1565c0
    style Mod fill:#fff3e0,stroke:#e65100
    style Mod2 fill:#fff3e0,stroke:#e65100
    style R fill:#e8f5e9,stroke:#2e7d32
    style R2 fill:#e8f5e9,stroke:#2e7d32
    style Table fill:#ffcdd2,stroke:#c62828
    style Table2 fill:#ffcdd2,stroke:#c62828
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

### Hash Function Comparison
```mermaid
graph TD
    HF[Hash Functions] --> Div[Division Method]
    HF --> Mult[Multiplication Method]
    HF --> Mid[Mid-Square]
    HF --> Fold[Folding]
    HF --> String[String Hash]
    
    Div --> DivPros[Simple, fast]
    Div --> DivCons[Clustering if not prime]
    Mult --> MultPros[Good distribution]
    Mult --> MultCons[Complex]
    Mid --> MidPros[Simple]
    Mid --> MidCons[Not uniform]
    Fold --> FoldPros[Good for strings]
    Fold --> FoldCons[Complex]
    
    style HF fill:#e3f2fd,stroke:#1565c0
    style Div fill:#e8f5e9,stroke:#2e7d32
    style Mult fill:#fff3e0,stroke:#e65100
    style Mid fill:#fce4ec,stroke:#c2185b
    style String fill:#f3e5f5,stroke:#7b1fa2
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Hashing** | Key → Index via hash function, O(1) average |
| **Hash Functions** | Division (prime table), Multiplication, Folding |
| **Collision** | Two keys → same index |

---

*Next: [Collision Resolution →](./unit4_02_collision_resolution.md)*