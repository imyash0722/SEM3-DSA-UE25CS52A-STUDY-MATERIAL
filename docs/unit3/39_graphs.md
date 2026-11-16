## 3.9 Graphs


### Definition
**G = (V, E)**
- V: Set of vertices (nodes)
- E: Set of edges (connections)

### Terminology
- **Adjacent**: Connected by edge
- **Incident**: Edge touches vertex
- **Degree**: Edges incident (undirected)
- **In-degree/Out-degree**: Directed edges in/out
- **Path**: Sequence of vertices
- **Cycle**: Path returning to start
- **Connected**: Path between every pair
- **Weighted**: Edges have values (cost, distance, time)

### Special Graphs
- **Eulerian**: Traverse each edge exactly once, return to start
  - Condition: All vertices have even degree
- **Hamiltonian**: Visit each vertex exactly once, return to start
  - No simple condition (NP-complete)

### Representations

#### Adjacency Matrix
```c
// V × V matrix
int adj[MAXV][MAXV];
adj[u][v] = 1;  // Edge exists
adj[u][v] = w;  // Weight (weighted)
// Space: O(V²)
// Edge check: O(1)
```

#### Adjacency List
```c
struct node {
    int vertex_;
    int weight_;     // For weighted graphs
    struct node* next_;
};
typedef struct node node_t;

node_t* adj[MAXV];  // Array of linked lists
// Space: O(V + E)
// Traverse neighbors: O(degree)
```

### Example Graph
```
V = {A, B, C, D, E, F, G, H}
E = {AB, AC, BC, BD, CE, DE, DF, FG, EG, GH, FH}

Adjacency List:
A → B, C
B → A, C, D
C → A, B, E
D → B, E, F
E → C, D, G
F → D, G, H
G → E, F, H
H → F, G

Degree: deg(A)=2, deg(B)=3, deg(H)=2
Σdeg(v) = 2|E| = 22
```

### Graph Algorithms (Overview)

#### BFS (Breadth-First Search) - Uses Queue
```c
void bfs(int start) {
    queue_t q; init_queue(&q);
    int visited[MAXV] = {0};
    enque(&q, start); visited[start] = 1;
    
    while (!is_empty(&q)) {
        int u = deque(&q);
        for (node_t* p = adj[u]; p; p = p->next_)
            if (!visited[p->vertex_]) {
                visited[p->vertex_] = 1;
                enque(&q, p->vertex_);
            }
    }
}
```

#### DFS (Depth-First Search) - Uses Stack
```c
void dfs(int start) {
    stack_t s; init_stack(&s);
    int visited[MAXV] = {0};
    push(&s, start); visited[start] = 1;
    
    while (!is_empty(&s)) {
        int u = pop(&s);
        for (node_t* p = adj[u]; p; p = p->next_)
            if (!visited[p->vertex_]) {
                visited[p->vertex_] = 1;
                push(&s, p->vertex_);
            }
    }
}
```

#### Dijkstra's Shortest Path - Uses Priority Queue (Min-Heap)
```c
void dijkstra(int src) {
    int dist[MAXV]; for (i) dist[i] = INF;
    dist[src] = 0;
    
    pqueue_t pq; init_pqueue(&pq);
    enqueue(&pq, src, 0);  // (vertex, distance)
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);  // Extract min distance
        for (node_t* p = adj[u]; p; p = p->next_) {
            int v = p->vertex_;
            int w = p->weight_;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                enqueue(&pq, v, dist[v]);  // Decrease key
            }
        }
    }
}
```

#### Prim's MST - Uses Priority Queue
```c
void prim(int start) {
    int key[MAXV]; for (i) key[i] = INF;
    int parent[MAXV]; for (i) parent[i] = -1;
    key[start] = 0;
    
    pqueue_t pq; init_pqueue(&pq);
    for (i) enqueue(&pq, i, key[i]);
    
    while (!is_empty(&pq)) {
        int u = dequeue_min(&pq);
        for (node_t* p = adj[u]; p; p = p->next_) {
            int v = p->vertex_;
            int w = p->weight_;
            if (in_queue(v) && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                decrease_key(&pq, v, w);
            }
        }
    }
}
```

### Applications
1. **Road Networks** - vertices = cities, edges = roads (weights = distance/time)
2. **Social Networks** - vertices = people, edges = friendships
3. **Computer Networks** - vertices = routers, edges = links
4. **Course Prerequisites** - directed edges = must take before
5. **Web Pages** - vertices = pages, directed edges = hyperlinks
6. **Project Scheduling** - vertices = tasks, edges = dependencies
7. **Software Dependencies** - vertices = modules, edges = imports