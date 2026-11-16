# Unit 4: Suffix Trees

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

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Suffix Tree** | Compressed trie of all suffixes, O(n) space |
| **Search** | O(m) where m = pattern length |

---

*Next: [Advanced Graph Algorithms →](./unit4_05_advanced_graph_algorithms.md)*