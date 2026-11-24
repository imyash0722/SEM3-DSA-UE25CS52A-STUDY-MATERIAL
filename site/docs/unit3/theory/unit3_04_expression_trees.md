# Unit 3: Expression Trees

## 🌿 Expression Trees

### Concept
- **Leaves**: Operands (numbers)
- **Internal nodes**: Operators (+, -, *, /)
- **Inorder** = Infix expression
- **Postorder** = Postfix expression
- **Preorder** = Prefix expression

### Expression Tree Example
```mermaid
graph TD
    A["*"] --> B["+"]
    A --> C["5"]
    B --> D["3"]
    B --> E["4"]
    
    style A fill:#ffebee,stroke:#c62828,stroke-width:3px
    style B fill:#fff3e0,stroke:#e65100,stroke-width:2px
    style C fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style D fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    style E fill:#e8f5e9,stroke:#2e7d32,stroke-width:2px
    
    Infix["Infix: (3+4)*5"] -.-> A
    Postfix["Postfix: 3 4 + 5 *"] -.-> A
    Prefix["Prefix: * + 3 4 5"] -.-> A
```

### Build from Postfix
```c
node_t* build_expression_tree(char *postfix) {
    node_t *stack[100];
    int top = -1;
    
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            // Operand: create node, push
            node_t *n = malloc(sizeof(node_t));
            n->key = ch; n->left = n->right = NULL;
            stack[++top] = n;
        } else {
            // Operator: pop 2, create node, push
            node_t *n = malloc(sizeof(node_t));
            n->key = ch;
            n->right = stack[top--];  // First popped = right
            n->left = stack[top--];   // Second popped = left
            stack[++top] = n;
        }
    }
    return stack[top];  // Root
}
```

### Build Process Visualization (Postfix: 3 4 + 5 *)
```mermaid
flowchart TD
    subgraph Step1["Step 1: Push 3"]
        S1["Stack: [3]"]
    end
    
    subgraph Step2["Step 2: Push 4"]
        S2["Stack: [3, 4]"]
    end
    
    subgraph Step3["Step 3: Operator +"]
        S3["Pop 4, Pop 3"] --> Create1["Create '+' node"]
        Create1 --> Push1["Push '+' node"]
        S3Result["Stack: [+]"]
    end
    
    subgraph Step4["Step 4: Push 5"]
        S4["Stack: [+, 5]"]
    end
    
    subgraph Step5["Step 5: Operator *"]
        S5["Pop 5, Pop +"] --> Create2["Create '*' node"]
        Create2 --> Push2["Push '*' node"]
        S5Result["Stack: [*] = ROOT"]
    end
    
    Step1 --> Step2 --> Step3 --> Step4 --> Step5
    
    style S3Result fill:#fff3e0,stroke:#e65100
    style S5Result fill:#e8f5e9,stroke:#2e7d32,stroke-width:3px
```

### Evaluate Expression Tree
```c
int eval(node_t *root) {
    if (!root->left && !root->right)  // Leaf = operand
        return root->key - '0';
    
    int left = eval(root->left);
    int right = eval(root->right);
    
    switch(root->key) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}
```

### Evaluation Visualization (Postorder Traversal)
```mermaid
graph TD
    Root[*] --> Left[+]
    Root --> Right[5]
    Left --> L1[3]
    Left --> R1[4]
    
    %% Evaluation order
    L1 -.->|1: eval 3| E1[3]
    R1 -.->|2: eval 4| E2[4]
    Left -.->|3: 3+4=7| E3[7]
    Right -.->|4: eval 5| E4[5]
    Root -.->|5: 7*5=35| E5[35]
    
    style Root fill:#ffebee,stroke:#c62828,stroke-width:3px
    style Left fill:#fff3e0,stroke:#e65100
    style E5 fill:#e8f5e9,stroke:#2e7d32,stroke-width:3px
```

---

## 📝 Key Takeaways

| Concept | Key Point |
|---------|-----------|
| **Expression Tree** | Leaves=operands, internal=operators |
| **Build from Postfix** | Stack-based, O(n) |
| **Evaluate** | Recursive postorder traversal |

---

*Next: [Threaded Binary Trees →](./unit3_05_threaded_binary_trees.md)*