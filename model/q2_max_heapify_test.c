#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static inline void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}


// --- Generated Implementation ---
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
// --- Test Verification ---

int main() {
    // Array violating max-heap at index 0 (root=4, left=14, right=7)
    int heap[] = {4, 14, 7, 2, 8, 1};
    int n = sizeof(heap) / sizeof(heap[0]);
    max_heapify(heap, n, 0);
    
    // After max_heapify at 0: root should be 14, left child 8, right child 7
    assert(heap[0] == 14);
    assert(heap[1] == 8);
    assert(heap[2] == 7);
    assert(heap[3] == 2);
    assert(heap[4] == 4);
    assert(heap[5] == 1);
    
    printf("Q2 PASS: Max-heapify sift-down successful!\n");
    return 0;
}

