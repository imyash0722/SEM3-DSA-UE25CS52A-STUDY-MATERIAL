# Unit 2: Stack Applications

## 🎯 Stack Applications - Deep Dive

### Application 1: Parentheses Matching

**Problem:** Check if parentheses in expression are balanced.

**Algorithm:**
```
For each character in string:
    If '(', '[', '{' → push to stack
    If ')', ']', '}' → 
        If stack empty → NOT balanced
        Pop and check if matching pair
After loop: if stack empty → balanced, else NOT balanced
```

**Matching Pairs:**
- `(` matches `)`
- `[` matches `]`
- `{` matches `}`

```c
int is_balanced(char *expr) {
    stack_t s; init_stack(&s);
    
    for (int i = 0; expr[i]; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{')
            push(&s, ch);
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (is_empty(&s)) return 0;
            char top = pop(&s);
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{'))
                return 0;
        }
    }
    return is_empty(&s);
}
```

**Example Traces:**
```
Input: "({[]})"     → BALANCED
Stack: ( → { → [ → pop[ matches ] → pop{ matches } → pop( matches ) → empty ✓

Input: "({[)]}"     → NOT BALANCED
Stack: ( → { → [ → pop[ but got ) → MISMATCH ✗
```

---

### Application 2: Infix to Postfix Conversion

**Definitions:**
- **Infix:** Operator between operands (A + B)
- **Postfix:** Operator after operands (A B +)
- **Prefix:** Operator before operands (+ A B)

**Why Postfix?** No parentheses needed, easy to evaluate with stack!

**Precedence Table:**
| Operator | Precedence |
|----------|------------|
| `^`      | 3 (highest)|
| `* / %`  | 2          |
| `+ -`    | 1          |

**Algorithm (Shunting Yard):**
```
For each token in infix:
    If operand → output
    If '(' → push to stack
    If ')' → pop and output until '('
    If operator:
        While stack not empty AND 
              precedence(top) >= precedence(current) AND top != '(':
            pop and output
        push current operator
After loop: pop remaining operators to output
```

```c
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infix_to_postfix(char *infix, char *postfix) {
    stack_t s; init_stack(&s);
    int j = 0;
    
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        
        if (isalnum(ch)) {
            postfix[j++] = ch;  // Operand goes to output
        } else if (ch == '(') {
            push(&s, ch);
        } else if (ch == ')') {
            while (!is_empty(&s) && peek(&s) != '(')
                postfix[j++] = pop(&s);
            pop(&s);  // Remove '('
        } else {  // Operator
            while (!is_empty(&s) && precedence(peek(&s)) >= precedence(ch))
                postfix[j++] = pop(&s);
            push(&s, ch);
        }
    }
    while (!is_empty(&s)) postfix[j++] = pop(&s);
    postfix[j] = '\0';
}
```

**Trace Example:**
```
Infix:  A + B * C
Step 1: A          → output: A
Step 2: +          → push +
Step 3: B          → output: AB
Step 4: *          → push * (higher precedence than +)
Step 5: C          → output: ABC
End:   pop * → output: ABC*  pop + → output: ABC*+

Postfix: ABC*+
```

---

### Application 3: Postfix Expression Evaluation

**Algorithm:**
```
For each token in postfix:
    If operand → push to stack
    If operator:
        pop operand2 (right)
        pop operand1 (left)
        result = operand1 operator operand2
        push result
Final result = pop stack
```

```c
int evaluate_postfix(char *postfix) {
    stack_t s; init_stack(&s);
    
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isdigit(ch)) {
            push(&s, ch - '0');  // Convert char to int
        } else {
            int b = pop(&s);  // Right operand
            int a = pop(&s);  // Left operand
            int result;
            switch(ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            push(&s, result);
        }
    }
    return pop(&s);
}
```

**Trace Example:**
```
Postfix:  3 4 + 5 *
Step 1: 3 → push 3      Stack: [3]
Step 2: 4 → push 4      Stack: [3, 4]
Step 3: + → pop 4, pop 3 → 3+4=7 → push 7   Stack: [7]
Step 4: 5 → push 5      Stack: [7, 5]
Step 5: * → pop 5, pop 7 → 7*5=35 → push 35  Stack: [35]
Result: 35
```

---

## 📝 Key Takeaways

| Application | Stack Usage |
|-------------|-------------|
| **Parentheses** | Push opening, pop and match closing |
| **Infix→Postfix** | Operators on stack, operands to output |
| **Postfix Eval** | Operands on stack, operators combine |

---

*Next: [Queue - Linked List Implementation →](./unit2_04_queue_linked_list.md)*