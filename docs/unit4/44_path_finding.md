## 4.4 Path Finding


### Path using DFS (Adjacency Matrix)

```c
int find_path_recursive(graph_t *ptr_graph, int path[], int* ptr_len,
                        int from, int to, int visited[]) {
    visited[from] = 1;
    int n = ptr_graph->n_vertices_;
    for(int i = 0; i < n; ++i) {
        if(ptr_graph->adj_mat_[from][i] && !visited[i]) {
            path[(*ptr_len)++] = i;
            if(i == to) return 1;
            return find_path_recursive(ptr_graph, path, ptr_len, i, to, visited);
        }
    }
    --(*ptr_len);  // Backtrack
    return 0;
}

int find_path(graph_t *ptr_graph, int path[], int* ptr_len, int from, int to) {
    int visited[MAXSIZE];
    path[(*ptr_len)++] = from;
    for(int i = 0; i < ptr_graph->n_vertices_; ++i) visited[i] = 0;
    return find_path_recursive(ptr_graph, path, ptr_len, from, to, visited);
}
```

**Key Idea:** Add to path when going deeper, remove when backtracking.

### Path using BFS (Adjacency List)

```c
int find_path_bfs(graph_t *ptr_graph, int parent[], int from, int to) {
    queue_t q; init_queue(&q);
    int visited[MAXSIZE] = {0};
    int parent[MAXSIZE];  // Track parent of each node
    for(int i = 0; i < n; ++i) parent[i] = -1;
    
    visited[from] = 1; enqueue(&q, from);
    while(!is_empty(&q)) {
        int u = dequeue(&q);
        node_t* temp = ptr_graph->adj_list_[u].head_;
        while(temp) {
            int v = temp->vertex_;
            if(!visited[v]) {
                visited[v] = 1;
                parent[v] = u;  // v was reached from u
                if(v == to) return 1;
                enqueue(&q, v);
            }
            temp = temp->next_;
        }
    }
    deinit_queue(&q);
    return 0;
}

// Reconstruct path from parent array
void fill_path(int parent[], int path[], int* ptr_len, int to) {
    while(parent[to] != -1) {
        path[(*ptr_len)++] = to;
        to = parent[to];
    }
    path[(*ptr_len)++] = to;
    reverse(path, *ptr_len);  // Reverse to get from→to order
}
```

---