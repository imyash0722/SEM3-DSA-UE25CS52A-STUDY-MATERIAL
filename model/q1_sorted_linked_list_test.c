#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node helper
Node* create_node(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = val;
    n->next = NULL;
    return n;
}


// --- Generated Implementation ---
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
// --- Test Verification ---

int main() {
    Node* head = NULL;
    insert_sorted(&head, 30);
    insert_sorted(&head, 10);
    insert_sorted(&head, 20);
    insert_sorted(&head, 50);
    insert_sorted(&head, 40);
    
    // Verify: 10 -> 20 -> 30 -> 40 -> 50
    int expected[] = {10, 20, 30, 40, 50};
    Node* curr = head;
    for (int i = 0; i < 5; i++) {
        assert(curr != NULL);
        assert(curr->data == expected[i]);
        Node* tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    assert(curr == NULL);
    printf("Q1 PASS: Sorted linked list insertion successful!\n");
    return 0;
}

