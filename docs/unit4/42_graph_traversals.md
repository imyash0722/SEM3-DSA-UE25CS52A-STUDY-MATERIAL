## 4.2 Graph Traversals


### Depth First Search (DFS)

**Concept:** Explore as deeply as possible along one path before backtracking. Uses recursion (implicit stack) or explicit stack.

**DFS on Adjacency Matrix:**
```c
void dfs_recursive(int n, int a[n][MAXSIZE], int visited[], int u) {
    visited[u] = 1;
    printf("visited %c \n", u + 'A');
    for(int i = 0; i < n; ++i) {
        if(a[u][i] && !visited[i]) {
            dfs_recursive(n, a, visited, i);
        }
    }
}

void dfs(graph_t *ptr_graph, int u) {
    int visited[MAXSIZE];
    for(int i = 0; i < ptr_graph->n_vertices_; ++i)
        visited[i] = 0;
    dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_mat_, visited, u);
    printf("\n");
}
```

**DFS on Adjacency List:**
```c
void dfs_recursive(int n, list_t a[MAXSIZE], int visited[], int u) {
    visited[u] = 1;
    printf("visited %c \n", u + 'A');
    node_t* temp = a[u].head_;
    int v;
    while(temp) {
        v = temp->vertex_;
        if(!visited[v]) {
            dfs_recursive(n, a, visited, v);
        }
        temp = temp->next_;
    }
}
```

**DFS Traversal Example:** A → B → C → E → D → F → G → H

---

### Breadth First Search (BFS)

**Concept:** Visit neighbours of a given node before going to the next. Uses a queue.

**BFS on Adjacency Matrix:**
```c
void bfs(graph_t *ptr_graph, int u) {
    int n = ptr_graph->n_vertices_;
    queue_t q; init_queue(&q);
    int visited[MAXSIZE];
    for(int i = 0; i < n; ++i) visited[i] = 0;
    int v;
    visited[u] = 1; enqueue(&q, u);
    while(!is_empty(&q)) {
        v = dequeue(&q);
        printf("visiting : %c\n", v + 'A');
        for(int i = 0; i < n; ++i) {
            if(ptr_graph->adj_mat_[v][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
    deinit_queue(&q);
}
```

**BFS on Adjacency List:**
```c
void bfs(graph_t *ptr_graph, int u) {
    queue_t q; init_queue(&q);
    int visited[MAXSIZE];
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) visited[i] = 0;
    int v;
    visited[u] = 1; enqueue(&q, u);
    while(!is_empty(&q)) {
        u = dequeue(&q);
        printf("visiting : %c\n", u + 'A');
        node_t* temp = ptr_graph->adj_list_[u].head_;
        while(temp) {
            v = temp->vertex_;
            if(!visited[v]) {
                visited[v] = 1;
                enqueue(&q, v);
            }
            temp = temp->next_;
        }
    }
    deinit_queue(&q);
}
```

**BFS Traversal Example:** A, B, C, D, E, F, G, H

---

### DFS vs BFS Comparison

| Aspect | DFS | BFS |
|--------|-----|-----|
| Data Structure | Stack (implicit recursion) | Queue |
| Traversal Order | Deep first, then backtrack | Level by level |
| Path Finding | Finds a path, not necessarily shortest | Finds shortest path (unweighted) |
| Memory | O(h) where h = height | O(w) where w = max width |
| Connected Components | ✓ | ✓ |
| Cycle Detection | ✓ | ✓ |
| Topological Sort | ✓ | - |
| Bipartite Check | ✓ | ✓ |

---