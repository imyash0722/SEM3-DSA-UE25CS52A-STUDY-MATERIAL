#ifndef HEAP_H
#define HEAP_H

#define MAXSIZE 200

struct heap 
{
	int key_[MAXSIZE];
	int n_;
};
typedef struct heap  heap_t;

void init(heap_t *ptr_heap);
void deinit(heap_t *ptr_heap);
void disp(heap_t *ptr_heap);
void insert(heap_t *ptr_heap, int key);


void build_heap(heap_t *ptr_heap, int a[], int n);


#endif
