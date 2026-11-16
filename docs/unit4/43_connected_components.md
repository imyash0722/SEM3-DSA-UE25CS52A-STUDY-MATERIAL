## 4.3 Connected Components


**Concept:** Two vertices are connected if there's a path between them. A connected component = all vertices where every pair is connected.

**Algorithm:**
1. Initialize `visited[]` array to 0
2. Find unvisited vertex using `to_visit()`
3. Run DFS/BFS from that vertex → marks one component
4. Repeat until all vertices visited

```c
int to_visit(int v[], int n) {
    for(int i = 0; i < n; ++i)
        if(v[i] == 0) return i;
    return -1;
}

int connected_components(graph_t *ptr_graph) {
    int visited[MAXSIZE], count = 0;
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) visited[i] = 0;
    int u = to_visit(visited, ptr_graph->n_vertices_);
    while(u != -1) {
        printf("Component %d: ", ++count);
        dfs_recursive(ptr_graph->n_vertices_, ptr_graph->adj_mat_, visited, u);
        // or bfs(ptr_graph, u, visited);
        printf("\n");
        u = to_visit(visited, ptr_graph->n_vertices_);
    }
    return count;
}
```

**Works with:** Adjacency Matrix + DFS, Adjacency Matrix + BFS, Adjacency List + DFS, Adjacency List + BFS

---