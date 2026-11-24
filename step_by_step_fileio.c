// ==========================================
// File I/O Step-by-Step: Binary Struct Array
// ==========================================
// Scenario: Save/load array of Student structs to binary file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll;
    char name[20];
    float marks;
} Student;

int main() {
    Student students[3] = {
        {101, "Alice", 95.5},
        {102, "Bob",   87.0},
        {103, "Carol", 92.5}
    };
    int n = 3;

    // ==========================================
    // STEP 1: OPEN FILE FOR WRITING (BINARY)
    // ==========================================
    // "wb" = write binary (creates new or truncates existing)
    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // ==========================================
    // STEP 2: WRITE COUNT FIRST (so we know how many to read back)
    // ==========================================
    // fwrite(address, size_of_each, count, file_pointer)
    fwrite(&n, sizeof(int), 1, fp);  // Write count (1 integer)

    // ==========================================
    // STEP 3: WRITE THE ARRAY OF STRUCTS
    // ==========================================
    // fwrite(array, size_of_each_element, count, file_pointer)
    fwrite(students, sizeof(Student), n, fp);

    // ==========================================
    // STEP 4: CLOSE FILE (flushes buffer to disk)
    // ==========================================
    fclose(fp);
    printf("Written %d students to file\n", n);

    // ==========================================
    // STEP 5: OPEN FILE FOR READING (BINARY)
    // ==========================================
    fp = fopen("students.dat", "rb");  // "rb" = read binary
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // ==========================================
    // STEP 6: READ COUNT FIRST
    // ==========================================
    int count;
    fread(&count, sizeof(int), 1, fp);  // Read 1 integer into &count

    // ==========================================
    // STEP 7: ALLOCATE MEMORY FOR EXACT COUNT
    // ==========================================
    Student *loaded = malloc(count * sizeof(Student));
    if (!loaded) { fclose(fp); return 1; }

    // ==========================================
    // STEP 8: READ ALL STRUCTS AT ONCE
    // ==========================================
    fread(loaded, sizeof(Student), count, fp);

    // ==========================================
    // STEP 9: CLOSE AND USE DATA
    // ==========================================
    fclose(fp);

    printf("Loaded %d students:\n", count);
    for (int i = 0; i < count; i++) {
        printf("  Roll: %d | Name: %s | Marks: %.1f\n",
               loaded[i].roll, loaded[i].name, loaded[i].marks);
    }

    free(loaded);
    return 0;
}