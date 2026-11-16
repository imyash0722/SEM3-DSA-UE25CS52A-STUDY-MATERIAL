# Unit 1: Stack Applications

## 1. Well-Formed Parentheses

```c
// Single type: ()
stack_t mystack; init_stack(&mystack);
while ((ch = *s++) != '\0') {
    if (ch == '(') push(&mystack, 'x');
    else if (ch == ')') {
        if (!is_empty(&mystack)) pop(&mystack);
        else is_valid = 0;
    }
}
if (is_valid && is_empty(&mystack))  // Well-formed
```

## 2. Well-Formed Brackets: (), [], {}

```c
// Push MATCHING closing bracket
if (ch == '(') push(&mystack, ')');
else if (ch == '[') push(&mystack, ']');
else if (ch == '{') push(&mystack, '}');
else if (ch == ')' || ch == ']' || ch == '}') {
    if (!is_empty(&mystack)) {
        if (ch != pop(&mystack)) is_valid = 0;
    } else is_valid = 0;
}
```

## 3. Postfix Expression Evaluation

```
Infix:    3 + 4        →  Postfix: 3 4 +
Infix:    5 * 6 + 7    →  Postfix: 5 6 * 7 +
Infix:    (3 + 4) * 5  →  Postfix: 3 4 + 5 *
```

**Algorithm:**
```c
// Stack of operands (int)
while ((ch = *s++) != '\0') {
    if (isdigit(ch)) {
        val = val * 10 + ch - '0';
        is_num = 1;
    } else if (ch == ' ' && is_num) {
        push(&mystack, val); val = 0; is_num = 0;
    } else if (is_operator(ch)) {
        val1 = pop(&mystack);  // Second operand
        val2 = pop(&mystack);  // First operand
        switch(ch) {
            case '+': push(&mystack, val2 + val1); break;
            case '-': push(&mystack, val2 - val1); break;
            case '*': push(&mystack, val2 * val1); break;
            case '/': push(&mystack, val2 / val1); break;
        }
    }
}
result = pop(&mystack);
```

## 4. Infix to Postfix Conversion

**Algorithm uses stack of operators:**
```
Input:  5 * 6 + 7 * 8
Output: 5 6 * 7 8 * +
```

```c
while ((ch = *s++) != '\0') {
    if (ch == ')') {
        while ((ch1 = pop(&mystack)) != '(') output ch1;
    }
    else if (is_operator(ch) || ch == '(') {
        if (is_empty(&mystack)) push(&mystack, ch);
        else {
            while (!is_empty(&mystack) && 
                   prec_in_str(ch) < prec_in_stack(peek(&mystack))) {
                output pop(&mystack);
            }
            push(&mystack, ch);
        }
    }
    else output operand ch;
}
while (!is_empty(&mystack)) output pop(&mystack);
```

**Precedence rules:**
- In string: `(` has highest, in stack: `(` has lowest
- Left-associative: pop when precedence equal
- Right-associative: push when precedence equal

---