## 4.8 Suffix Trees


### Suffix Trie → Patricia Trie → Suffix Tree

**Suffix Trie:** Trie of all suffixes of string T
- Space: O(n²) where n = |T|
- Every suffix ends in leaf
- Every substring = prefix of some suffix

**Patricia Trie (Compressed Trie):**
- Merge "silly nodes" (internal nodes with exactly one child)
- Chains of single-child nodes → single edge with string label
- Space: O(n)

**Suffix Tree:**
- Patricia Trie of all suffixes of T$ (where $ = unique terminator)
- Each leaf labeled with suffix starting position
- Construction: O(n) with Ukkonen's algorithm (beyond course scope)
- Space: O(n)
- Search: O(m) where m = pattern length

---