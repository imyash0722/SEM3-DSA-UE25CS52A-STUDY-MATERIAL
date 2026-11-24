# File I/O Flowchart Explanation

## Binary Write Flowchart

```mermaid
flowchart TD
    Start(["Start"]) --> OpenW["Open File: fopen('file.dat', 'wb')"]
    OpenW --> CheckOpen{"File Opened?"}
    CheckOpen -- No --> ErrorW["Print Error & Exit"]
    CheckOpen -- Yes --> WriteCount["Write Count: fwrite(&n, sizeof(int), 1, fp)"]
    WriteCount --> WriteData["Write Array: fwrite(arr, sizeof(Struct), n, fp)"]
    WriteData --> CloseW["Close File: fclose(fp)"]
    CloseW --> EndW(["Write Complete"])
    
    style Start fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style ErrorW fill:#ffcdd2,stroke:#c62828
    style EndW fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style CheckOpen fill:#fff3e0,stroke:#e65100
```

## Binary Read Flowchart

```mermaid
flowchart TD
    Start(["Start"]) --> OpenR["Open File: fopen('file.dat', 'rb')"]
    OpenR --> CheckOpenR{"File Opened?"}
    CheckOpenR -- No --> ErrorR["Print Error & Exit"]
    CheckOpenR -- Yes --> ReadCount["Read Count: fread(&count, sizeof(int), 1, fp)"]
    ReadCount --> Alloc["Allocate Memory: malloc(count * sizeof(Struct))"]
    Alloc --> ReadData["Read Array: fread(ptr, sizeof(Struct), count, fp)"]
    ReadData --> CloseR["Close File: fclose(fp)"]
    CloseR --> Process["Process Data"]
    Process --> Free["Free Memory"]
    Free --> EndR(["Read Complete"])
    
    style Start fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style ErrorR fill:#ffcdd2,stroke:#c62828
    style EndR fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style CheckOpenR fill:#fff3e0,stroke:#e65100
```

## Combined Write → Read Flowchart

```mermaid
flowchart TD
    subgraph WritePhase["WRITE PHASE"]
        W1(["Start Write"]) --> W2["Open 'wb'"]
        W2 --> W3{"fopen OK?"}
        W3 -- No --> WErr["Error"]
        W3 -- Yes --> W4["Write Count"]
        W4 --> W5["Write Array"]
        W5 --> W6["Close File"]
    end
    
    subgraph ReadPhase["READ PHASE"]
        R1(["Start Read"]) --> R2["Open 'rb'"]
        R2 --> R3{"fopen OK?"}
        R3 -- No --> RErr["Error"]
        R3 -- Yes --> R5["Read Count"]
        R5 --> R6["Malloc Array"]
        R6 --> R7["Read Data"]
        R7 --> R8["Close File"]
        R8 --> R9["Process Data"]
        R9 --> R10["Free Memory"]
    end
    
    W6 -.->|File on Disk| R1
    
    style WritePhase fill:#e3f2fd,stroke:#1565c0
    style ReadPhase fill:#fff3e0,stroke:#e65100
    style WErr fill:#ffcdd2,stroke:#c62828
    style RErr fill:#ffcdd2,stroke:#c62828
```

## Detailed Step-by-Step with Decision Points

```mermaid
flowchart TD
    Start(["Program Start"]) --> Mode{"Write or Read?"}
    
    Mode -- Write --> WOpen["fopen('file.dat', 'wb')"]
    Mode -- Read --> ROpen["fopen('file.dat', 'rb')"]
    
    WOpen --> WCheck{"fp != NULL?"}
    ROpen --> RCheck{"fp != NULL?"}
    
    WCheck -- No --> WError["perror + exit"]
    RCheck -- No --> RError["perror + exit"]
    
    WCheck -- Yes --> WCount["fwrite(&count, sizeof(int), 1, fp)"]
    RCheck -- Yes --> RCount["fread(&count, sizeof(int), 1, fp)"]
    
    WCount --> WArray["fwrite(array, sizeof(Struct), n, fp)"]
    RCount --> RMalloc["malloc(count * sizeof(Struct))"]
    RMalloc --> RArray["fread(array, sizeof(Struct), count, fp)"]
    
    WArray --> WClose["fclose(fp)"]
    RArray --> RClose["fclose(fp)"]
    
    WClose --> WEnd(["Write Done"])
    RClose --> RProcess["Use Data"]
    RProcess --> RFree["free(ptr)"]
    RFree --> REnd(["Read Done"])
    
    style Start fill:#e8f5e9,stroke:#2e7d32,stroke-width:3px
    style WError fill:#ffcdd2,stroke:#c62828
    style RError fill:#ffcdd2,stroke:#c62828
    style WEnd fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style REnd fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style WCheck fill:#fff3e0,stroke:#e65100
    style RCheck fill:#fff3e0,stroke:#e65100
```

## Legend

| Symbol | Meaning |
|--------|---------|
| `([ ])` | Start/End (rounded) |
| `[ ]` | Process/Action (rectangle) |
| `{ }` | Decision (diamond) |
| `-->` | Flow direction |
| `.->` | Dotted line (file on disk) |
| `subgraph` | Grouped phase |

## Key Decision Points

| Decision | Check | If No | If Yes |
|----------|-------|-------|--------|
| `fp != NULL` | File opened? | Print error, exit | Continue |
| `fread/fwrite` | Items read/written == expected? | Handle error | Continue |
| `malloc` | Returned NULL? | Handle error | Continue |

## Memory Layout Visualization

```mermaid
graph LR
    subgraph File["students.dat on Disk"]
        F1["count: 3"] --> F2["Student 1"]
        F2 --> F3["Student 2"]
        F3 --> F4["Student 3"]
    end
    
    subgraph Memory["Memory After Read"]
        M1["count: 3"] --> M2["Student[0]"]
        M2 --> M3["Student[1]"]
        M3 --> M4["Student[2]"]
    end
    
    File -.->|fread| Memory
    
    style File fill:#e3f2fd,stroke:#1565c0
    style Memory fill:#e8f5e9,stroke:#2e7d32
```
