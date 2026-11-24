# Unit 3: Graphs

## 🌐 Graphs

### Definition
> **G = (V, E)** where V = vertices, E = edges

### Representations

#### 1. Adjacency Matrix
```c
int adj[MAXV][MAXV];
adj[u][v] = 1;  // Edge exists
adj[u][v] = w;  // Weight (weighted)
```
- Space: O(V²)
- Edge check: O(1)

### Adjacency Matrix Visualization
```mermaid
graph TD
    subgraph Matrix[Adjacency Matrix: 8x8]
        direction TB
        A[A] -->|1| B[B]
        A -->|1| C[C]
        B[B] -->|1| A
        B -->|1| C
        B -->|1| D[D]
        C[C] -->|1| A
        C -->|1| B
        C -->|1| E[E]
        D[D] -->|1| B
        D -->|1| E
        D -->|1| F[F]
        E[E] -->|1| C
        E -->|1| D
        E -->|1| G[G]
        F[F] -->|1| D
        F -->|1| G
        F -->|1| H[H]
        G[G] -->|1| E
        G -->|1| H
        H[H] -->|1| F
        H -->|1| G
    end
    
    style A fill:#e3f2fd,stroke:#1565c0
    style B fill:#e3f2fd,stroke:#1565c0
    style C fill:#e3f2fd,stroke:#1565c0
    style D fill:#e3f2fd,stroke:#1565c0
    style E fill:#e3f2fd,stroke:#1565c0
    style F fill:#e3f2fd,stroke:#1565c0
    style G fill:#e3f2fd,stroke:#1565c0
    style H fill:#e3f2fd,stroke:#1565c0
```

#### 2. Adjacency List
```c
struct node {
    int vertex;
    int weight;
    struct node *next;
};
typedef struct node node_t;

node_t *adj[MAXV];  // Array of linked lists
```
- Space: O(V + E)
- Traverse neighbors: O(degree)

### Adjacency List Visualization
```mermaid
graph LR
    subgraph AdjList["Adjacency List: Vertex -> Neighbors"]
        direction TB
        HeadA["A"] --> A_B["B"] --> A_C["C"] --> A_NULL["NULL"]
        HeadB["B"] --> B_A["A"] --> B_C["C"] --> B_D["D"] --> B_NULL["NULL"]
        HeadC["C"] --> C_A["A"] --> C_B["B"] --> C_E["E"] --> C_NULL["NULL"]
        HeadD["D"] --> D_B["B"] --> D_E["E"] --> D_F["F"] --> D_NULL["NULL"]
        HeadE["E"] --> E_C["C"] --> E_D["D"] --> E_G["G"] --> E_NULL["NULL"]
        HeadF["F"] --> F_D["D"] --> F_G["G"] --> F_H["H"] --> F_NULL["NULL"]
        HeadG["G"] --> G_E["E"] --> G_F["F"] --> G_H["H"] --> G_NULL["NULL"]
        HeadH["H"] --> H_F["F"] --> H_G["G"] --> H_NULL["NULL"]
    end
    
    style HeadA fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadB fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadC fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadD fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadE fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadF fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadG fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style HeadH fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
```

### Example Graph Visualization
```mermaid
graph LR
    A[A] --- B[B]
    A --- C[C]
    B --- C
    B --- D[D]
    C --- E[E]
    D --- E
    D --- F[F]
    E --- G[G]
    F --- G
    F --- H[H]
    G --- H
    
    style A fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    style B fill:#e3f2fd,stroke:#1565c0
    style C fill:#e3f2fd,stroke:#1565c0
    style D fill:#e3f2fd,stroke:#1565c0
    style E fill:#e3f2fd,stroke:#1565c0
    style F fill:#e3f2fd,stroke:#1565c0
    style G fill:#e3f2fd,stroke:#1565c0
    style H fill:#e3f2fd,stroke:#1565c0
```

### Traversals

#### BFS (Breadth-First Search) - Uses Queue
```c
void bfs(int start) {
    queue_t q; init(&q);
    int visited[MAXV] = {0};
    enqueue(&q, start); visited[start] = 1;
    
    while (!is_empty(&q)) {
        int u = dequeue(&q);
        printf("%d ", u);
        for (node_t *p = adj[u]; p; p = p->next)
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                enqueue(&q, p->vertex);
            }
    }
}
```

### BFS Visualization
```mermaid
graph TD
    Start["Start: A"] --> Q1["Queue: [A]"]
    Q1 --> V1["Visit A, Enqueue B, C"]
    V1 --> Q2["Queue: [B, C]"]
    Q2 --> V2["Visit B, Enqueue D"]
    V2 --> Q3["Queue: [C, D]"]
    Q3 --> V3["Visit C, Enqueue E"]
    V3 --> Q4["Queue: [D, E]"]
    Q4 --> V4["Visit D, Enqueue F"]
    V4 --> Q5["Queue: [E, F]"]
    Q5 --> V5["Visit E, Enqueue G"]
    V5 --> Q6["Queue: [F, G]"]
    Q6 --> V6["Visit F, Enqueue H"]
    V6 --> Q7["Queue: [G, H]"]
    Q7 --> V7["Visit G"]
    V7 --> Q8["Queue: [H]"]
    Q8 --> V8["Visit H"]
    V8 --> Done["Done - Order: A, B, C, D, E, F, G, H"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Done fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

#### DFS (Depth-First Search) - Uses Stack
```c
void dfs(int start) {
    stack_t s; init(&s);
    int visited[MAXV] = {0};
    push(&s, start); visited[start] = 1;
    
    while (!is_empty(&s)) {
        int u = pop(&s);
        printf("%d ", u);
        for (node_t *p = adj[u]; p; p = p->next)
            if (!visited[p->vertex]) {
                visited[p->vertex] = 1;
                push(&s, p->vertex);
            }
    }
}
```

### DFS Visualization
```mermaid
graph TD
    Start["Start: A"] --> S1["Stack: [A]"]
    S1 --> V1["Visit A, Push C, B"]
    V1 --> S2["Stack: [C, B]"]
    S2 --> V2["Pop B, Visit B, Push D"]
    V2 --> S3["Stack: [C, D]"]
    S3 --> V3["Pop D, Visit D, Push E, F"]
    V3 --> S4["Stack: [C, E, F]"]
    S4 --> V4["Pop F, Visit F, Push G, H"]
    V4 --> S5["Stack: [C, E, G, H]"]
    S5 --> V5["Pop H, Visit H"]
    V5 --> S6["Stack: [C, E, G]"]
    S6 --> V6["Pop G, Visit G"]
    V6 --> S7["Stack: [C, E]"]
    S7 --> V7["Pop E, Visit E"]
    V7 --> S8["Stack: [C]"]
    S8 --> V8["Pop C, Visit C"]
    V8 --> Done["Stack Empty - Traversal: A, B, D, F, H, G, E, C"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Done fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### BFS vs DFS Comparison
```mermaid
graph LR
    subgraph BFS["BFS - Breadth First Search"]
        BF1["Uses Queue"]
        BF2["Level by Level"]
        BF3["Shortest Path (Unweighted)"]
        BF4["More Memory"]
    end
    
    subgraph DFS["DFS - Depth First Search"]
        DF1["Uses Stack"]
        DF2["Deep First"]
        DF3["Topological Sort"]
        DF4["Cycle Detection"]
        DF5["Less Memory"]
    end
    
    style BFS fill:#e3f2fd,stroke:#1565c0
    style DFS fill:#fff3e0,stroke:#e65100
```

### Graph Algorithms

#### Dijkstra's Shortest Path (Weighted, Non-negative)
- Uses **Min-Heap Priority Queue**
- Time: O((V+E) log V)

### Dijkstra's Algorithm Visualization
```mermaid
graph TD
    Start["Start: Source=0"] --> Init["dist[0]=0, others=∞"]
    Init --> PQ["Min-Heap: (0,0)"]
    PQ --> Extract["Extract Min: u"]
    Extract --> Relax{"Relax edges from u"}
    Relax -- Update --> Update["Update dist[v], decrease-key in heap"]
    Update --> Extract
    Extract --> Done{"Heap Empty?"}
    Done -- No --> Extract
    Done -- Yes --> Result["Shortest Paths"]
    
    style Start fill:#e8f5e9,stroke:#2e7d32
    style Result fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

#### Prim's MST (Minimum Spanning Tree)
- Uses **Min-Heap Priority Queue**
- Time: O(E log V)

### Prim's MST Visualization
```mermaid
graph TD
    Start["Start: Any Vertex"] --> MST["MST Set: {start}"]
    MST --> Edges["All edges from MST"]
    Edges --> MinEdge["Min weight edge to outside vertex"]
    MinEdge --> Add["Add vertex to MST"]
    Add --> MST
    Add --> Done{"All vertices in MST?"}
    Done -- No --> Edges
    Done -- Yes --> Result["MST Complete"]
    
    style Start fill:#e3f2fd,stroke:#1565c0
    style Result fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
```

### Prim's MST Example
```mermaid
graph LR
    A[A] ---|1| B[B]
    A ---|4| C[C]
    B ---|2| C
    B ---|5| D[D]
    C ---|3| D
    D ---|6| E[E]
    
    style A fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style B fill:#e8f5e9,stroke:#2e7d32
    style C fill:#e8f5e9,stroke:#2e7d32
    style D fill:#e8f5e9,stroke:#2e7d32
    style E fill:#e8f5e9,stroke:#2e7d32
    
    MST["MST: A-B(1), B-C(2), C-D(3), D-E(6) Total=12"]
```

---

## 📝 Key Takeaways

| Concept | Key Insight |
|---------|-------------|
| **Graph** | V vertices, E edges, Matrix/List |
| **BFS** | Queue, shortest path (unweighted) |
| **DFS** | Stack, topological sort, cycles |
| **Dijkstra** | Min-heap, weighted shortest path |
| **Prim** | Min-heap, MST |

---

*Next: [Unit 3 Anchor Programs →](./unit3_10_anchor_programs.md)*