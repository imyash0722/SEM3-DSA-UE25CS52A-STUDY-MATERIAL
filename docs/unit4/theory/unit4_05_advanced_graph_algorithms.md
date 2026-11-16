# Unit 4: Advanced Graph Algorithms

## 🌐 Advanced Graph Algorithms

### Dijkstra's Shortest Path
- **Single-source shortest path** (weighted, non-negative)
- Uses **Min-Heap Priority Queue**
- Time: O((V+E) log V)

```c
void dijkstra(int V, int src) {
    int dist[MAXV];
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;
    
    // Min-heap: (distance, vertex)
    pqueue_t pq; init(&pq);
    enqueue(&pq, src, 0);
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);
        for (node_t *p = adj[u]; p; p = p->next) {
            int v = p->vertex, w = p->weight;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                enqueue(&pq, v, dist[v]);  // Decrease key
            }
        }
    }
}
```

### Prim's Minimum Spanning Tree
- **MST**: Connect all vertices with minimum total edge weight
- Uses **Min-Heap Priority Queue**
- Time: O(E log V)

```c
void prim(int V, int start) {
    int key[MAXV], parent[MAXV];
    for (int i = 0; i < V; i++) { key[i] = INF; parent[i] = -1; }
    key[start] = 0;
    
    pqueue_t pq; init(&pq);
    for (int i = 0; i < V; i++) enqueue(&pq, i, key[i]);
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);
        for (node_t *p = adj[u]; p; p = p->next) {
            int v = p->vertex, w = p->weight;
            if (in_queue(v) && w < key[v]) {
                key[v] = w; parent[v] = u;
                decrease_key(&pq, v, w);
            }
        }
    }
}
```

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Dijkstra** | Min-heap, O((V+E)log V), non-negative weights |
| **Prim's MST** | Min-heap, O(E log V) |

---

*Next: [Unit 4 Anchor Programs →](./unit4_06_anchor_programs.md)*