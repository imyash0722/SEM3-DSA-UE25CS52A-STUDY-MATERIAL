## 4.1 Graph Representations & Traversals


### 4.1.1 Adjacency Matrix Representation

**Structure:**
```c
#define MAXSIZE 10
struct graph {
    int n_vertices_;  // # of vertices
    int n_edges_;     // # of edges
    int adj_mat_[MAXSIZE][MAXSIZE];
};
typedef struct graph graph_t;
```

**Adjacency Matrix Properties:**
- V × V matrix
- `adj_mat_[i][j] = 1` if edge from vertex i to j (unweighted)
- `adj_mat_[i][j] = weight` if weighted
- For undirected graph: matrix is symmetric
- Space: O(V²)

**Interface:**
```c
void init_graph(graph_t *ptr_graph, int n_vertices, int n_edges);
void add_edge(graph_t *ptr_graph, int from, int to);
void dfs(graph_t *ptr_graph, int u);
void bfs(graph_t *ptr_graph, int u);
void disp(graph_t *ptr_graph);
void deinit_graph(graph_t *ptr_graph);
```

### 4.1.2 Adjacency List Representation

**Structure:**
```c
struct node {
    int vertex_;
    struct node* next_;
};
typedef struct node node_t;

struct list {
    node_t* head_;
    node_t* tail_;
};
typedef struct list list_t;

struct graph {
    int n_vertices_;
    int n_edges_;
    list_t adj_list_[MAXSIZE];
};
typedef struct graph graph_t;
```

**Properties:**
- Space: O(V + E)
- More efficient for sparse graphs
- Each vertex has a list of adjacent vertices

---