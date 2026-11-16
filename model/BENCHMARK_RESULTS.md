# DSA Benchmark Report: qwen2.5-coder:7b

- **Date**: 2026-11-16 15:55:43
- **System**: AMD Ryzen 7 7735HS (8C/16T) + Radeon 680M
- **Overall Score**: **3/3 (100.0%) Passed**
- **Average Generation Speed**: **4.95 tokens/sec**

## Summary Table

| ID | Problem | Status | Speed (tok/s) | Latency (s) |
| :--- | :--- | :--- | :--- | :--- |
| `q1_sorted_linked_list` | Singly Linked List - Sorted Insertion | ✅ PASS | 5.02 | 40.21s |
| `q2_max_heapify` | Binary Max-Heap - Sift-Down Heapify | ✅ PASS | 4.95 | 29.13s |
| `q3_bst_delete` | Binary Search Tree - Node Deletion | ✅ PASS | 4.88 | 41.56s |

## Detailed Test Outputs

### Singly Linked List - Sorted Insertion (`q1_sorted_linked_list`)

**Status**: `PASS`

```c
void insert_sorted(Node** head, int val) {
    Node* new_node = create_node(val);
    if (*head == NULL || (*head)->data >= val) {
        new_node->next = *head;
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->data < val) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
```

### Binary Max-Heap - Sift-Down Heapify (`q2_max_heapify`)

**Status**: `PASS`

```c
void max_heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, n, largest);
    }
}
```

### Binary Search Tree - Node Deletion (`q3_bst_delete`)

**Status**: `PASS`

```c
Node* delete_node(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = find_min(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }

    return root;
}
```

