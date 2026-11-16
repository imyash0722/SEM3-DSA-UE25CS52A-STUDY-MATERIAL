#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int k) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = k;
    n->left = n->right = NULL;
    return n;
}

Node* bst_insert(Node* root, int k) {
    if (!root) return create_node(k);
    if (k < root->key) root->left = bst_insert(root->left, k);
    else if (k > root->key) root->right = bst_insert(root->right, k);
    return root;
}

static Node* find_min(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}


// --- Generated Implementation ---
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
// --- Test Verification ---

int main() {
    Node* root = NULL;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) root = bst_insert(root, vals[i]);
    
    // Case 1: Delete leaf node (20)
    root = delete_node(root, 20);
    assert(root->left->left == NULL);
    
    // Case 2: Delete node with 1 child (30 has child 40)
    root = delete_node(root, 30);
    assert(root->left->key == 40);
    
    // Case 3: Delete root node with 2 children (50)
    root = delete_node(root, 50);
    assert(root->key == 60);
    assert(root->right->left == NULL);
    
    printf("Q3 PASS: BST deletion successful!\n");
    return 0;
}

