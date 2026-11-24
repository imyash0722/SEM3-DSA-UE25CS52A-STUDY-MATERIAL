// file_io_demo.c - Complete File I/O Demo for DSA
// Demonstrates reading/writing data structures to files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define FILENAME "students.dat"

// ==========================================
// Data Structure
// ==========================================
typedef struct {
    int roll;
    char name[MAX_NAME];
    float marks;
} Student;

// ==========================================
// WRITE: Binary File
// ==========================================
void write_binary_file() {
    Student students[] = {
        {101, "Alice", 95.5},
        {102, "Bob", 87.0},
        {103, "Charlie", 92.5},
        {104, "Diana", 88.0},
        {105, "Eve", 91.5}
    };
    int count = 5;

    FILE *fp = fopen(FILENAME, "wb");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }

    // Write count first
    fwrite(&count, sizeof(int), 1, fp);
    
    // Write all students
    fwrite(students, sizeof(Student), count, fp);
    
    fclose(fp);
    printf("Binary file written: %d students\n", count);
}

// ==========================================
// READ: Binary File
// ==========================================
void read_binary_file() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("Error opening file for reading");
        return;
    }

    int count;
    fread(&count, sizeof(int), 1, fp);

    Student *students = malloc(count * sizeof(Student));
    fread(students, sizeof(Student), count, fp);

    printf("\n--- Binary File Contents ---\n");
    for (int i = 0; i < count; i++) {
        printf("Roll: %d | Name: %-10s | Marks: %.1f\n", 
               students[i].roll, students[i].name, students[i].marks);
    }

    free(students);
    fclose(fp);
}

// ==========================================
// WRITE: Text File (CSV)
// ==========================================
void write_csv_file() {
    Student students[] = {
        {101, "Alice", 95.5},
        {102, "Bob", 87.0},
        {103, "Charlie", 92.5}
    };
    int count = 3;

    FILE *fp = fopen("students.csv", "w");
    if (!fp) {
        perror("Error opening CSV file");
        return;
    }

    // Header
    fprintf(fp, "Roll,Name,Marks\n");
    
    // Data rows
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%s,%.1f\n", 
                students[i].roll, students[i].name, students[i].marks);
    }

    fclose(fp);
    printf("CSV file written\n");
}

// ==========================================
// READ: Text File (CSV)
// ==========================================
void read_csv_file() {
    FILE *fp = fopen("students.csv", "r");
    if (!fp) {
        perror("Error opening CSV file");
        return;
    }

    char line[200];
    // Skip header
    fgets(line, sizeof(line), fp);

    printf("\n--- CSV File Contents ---\n");
    while (fgets(line, sizeof(line), fp)) {
        Student s;
        // Parse CSV line
        if (sscanf(line, "%d,%49[^,],%f", &s.roll, s.name, &s.marks) == 3) {
            printf("Roll: %d | Name: %-10s | Marks: %.1f\n", s.roll, s.name, s.marks);
        }
    }

    fclose(fp);
}

// ==========================================
// WRITE: Linked List to File
// ==========================================
typedef struct Node {
    int data;
    struct Node* next;
} Node;

void write_linked_list(Node* head, const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) return;

    // Count nodes
    int count = 0;
    for (Node* curr = head; curr; curr = curr->next) count++;

    fwrite(&count, sizeof(int), 1, fp);
    
    for (Node* curr = head; curr; curr = curr->next) {
        fwrite(&curr->data, sizeof(int), 1, fp);
    }
    
    fclose(fp);
}

Node* read_linked_list(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) return NULL;

    int count;
    fread(&count, sizeof(int), 1, fp);

    Node *head = NULL, *tail = NULL;
    
    for (int i = 0; i < count; i++) {
        int data;
        fread(&data, sizeof(int), 1, fp);
        
        Node* newNode = malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;
        
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    fclose(fp);
    return head;
}

// ==========================================
// WRITE: BST to File (Preorder traversal)
// ==========================================
typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;

void write_bst_preorder(TreeNode* root, FILE* fp) {
    if (!root) {
        int marker = -1;  // Marker for NULL
        fwrite(&marker, sizeof(int), 1, fp);
        return;
    }
    fwrite(&root->key, sizeof(int), 1, fp);
    write_bst_preorder(root->left, fp);
    write_bst_preorder(root->right, fp);
}

TreeNode* read_bst_preorder(FILE* fp) {
    int key;
    if (fread(&key, sizeof(int), 1, fp) != 1) return NULL;
    if (key == -1) return NULL;  // NULL marker
    
    TreeNode* node = malloc(sizeof(TreeNode));
    node->key = key;
    node->left = read_bst_preorder(fp);
    node->right = read_bst_preorder(fp);
    return node;
}

// ==========================================
// Helper: Create Sample Linked List
// ==========================================
Node* create_sample_list() {
    Node *head = NULL, *tail = NULL;
    for (int i = 1; i <= 5; i++) {
        Node* n = malloc(sizeof(Node));
        n->data = i * 10;
        n->next = NULL;
        if (!head) head = tail = n;
        else { tail->next = n; tail = n; }
    }
    return head;
}

// Helper: Create Sample BST
TreeNode* create_sample_bst() {
    TreeNode* root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        // Simple BST insert
        TreeNode* n = malloc(sizeof(TreeNode));
        n->key = keys[i]; n->left = n->right = NULL;
        if (!root) { root = n; continue; }
        
        TreeNode *curr = root, *parent = NULL;
        while (curr) {
            parent = curr;
            if (keys[i] < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        if (keys[i] < parent->key) parent->left = n;
        else parent->right = n;
    }
    return root;
}

// ==========================================
// Main
// ==========================================
int main() {
    printf("=== DSA File I/O Demo ===\n\n");

    // 1. Binary file (struct array)
    write_binary_file();
    read_binary_file();

    // 2. CSV file
    write_csv_file();
    read_csv_file();

    // 3. Linked List
    Node* list = create_sample_list();
    write_linked_list(list, "list.dat");
    Node* loaded = read_linked_list("list.dat");
    printf("\n--- Linked List from File ---\n");
    for (Node* p = loaded; p; p = p->next) printf("%d ", p->data);
    printf("\n");

    // 4. BST
    TreeNode* bst = create_sample_bst();
    FILE* fp = fopen("bst.dat", "wb");
    write_bst_preorder(bst, fp);
    fclose(fp);
    
    fp = fopen("bst.dat", "rb");
    TreeNode* loaded_bst = read_bst_preorder(fp);
    fclose(fp);
    
    // Verify with inorder traversal
    void inorder(TreeNode* n) {
        if (n) { inorder(n->left); printf("%d ", n->key); inorder(n->right); }
    }
    printf("\n--- BST Inorder from File ---\n");
    inorder(loaded_bst);
    printf("\n");

    return 0;
}