## 3.4 Expression Trees


### Postfix to Expression Tree

**Algorithm:**
1. Scan postfix left to right
2. **Operand**: Create node, push to stack
3. **Operator**: Pop 2 nodes, create operator node with them as children, push result

```
Postfix: 3 4 + 5 *
Stack evolution:
  push 3     → [3]
  push 4     → [3, 4]
  +          → pop 4,3; create (+, 3, 4); push → [(+)]
  push 5     → [(+), 5]
  *          → pop 5, (+); create (*, (+), 5); push → [(*)]
Result: * root with left=+ and right=5
```

### Structure
```c
struct node {
    char ch_;           // Operand (digit) or operator
    struct node *left_, *right_;
};
typedef struct node node_t;

struct stack {
    node_t* key_[MAXSIZE];
    int top_;
};
typedef struct stack stack_t;
```

### Stack Operations
```c
node_t* create_node(char ch) {
    node_t* temp = (node_t*)malloc(sizeof(node_t));
    temp->ch_ = ch; temp->left_ = temp->right_ = NULL;
    return temp;
}

void push_operand(stack_t* s, char ch) {
    if (!is_full(s)) s->key_[++s->top_] = create_node(ch);
}

void push_operator(stack_t* s, char ch) {
    if (!is_full(s)) {
        node_t* temp = create_node(ch);
        temp->right_ = pop(s);   // First popped = right operand
        temp->left_ = pop(s);    // Second popped = left operand
        s->key_[++s->top_] = temp;
    }
}
```

### Evaluation (Recursive)
```c
int eval_recursive(node_t* root) {
    if (!root->left_ && !root->right_)  // Leaf = operand
        return root->ch_ - '0';
    
    int left = eval_recursive(root->left_);
    int right = eval_recursive(root->right_);
    
    switch (root->ch_) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}

int eval(stack_t* s) {
    return eval_recursive(pop(s));  // Final tree on stack
}
```

---