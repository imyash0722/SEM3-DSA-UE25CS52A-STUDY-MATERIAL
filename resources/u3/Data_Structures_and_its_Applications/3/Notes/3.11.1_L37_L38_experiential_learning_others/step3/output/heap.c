#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void init_heap(heap_t *ptr_heap, int (*compare)(int, int))
{
	ptr_heap->n_ = 0;
	ptr_heap->compare = compare;
}

void deinit_heap(heap_t *ptr_heap)
{
	ptr_heap->n_ = 0;
}

void disp(heap_t *ptr_heap)
{
	printf("\n displaying the heap \n");
	for(int i = 1; i <= ptr_heap->n_; ++i)
	{
		printf("%d ", ptr_heap->key_[i]);
	}
	printf("\n");
}

static void heapify(int a[], int n, int pos, int (*compare)(int, int))
{
	int i = pos;
	int j = 2 * i;
	int val = a[i];
	int is_heap = 0;
	while(j <= n && ! is_heap)
	{
//		if(j + 1 <= n && a[j+1] > a[j])
		if(j + 1 <= n && compare(a[j+1], a[j]))
			++j;
//		if(a[j] > val)
		if(compare(a[j], val))
		{
			a[i] = a[j];
			i = j;
			j = 2 * i;
		}
		else 
		{
			is_heap = 1;
		}

	}
	a[i] = val;
}
static void swap(int *p, int *q)
{
	int temp = *p;
	*p = *q;
	*q = temp;
}

void insert(heap_t *ptr_heap, int key)
{
	// add at the end
	// heapify upwards 
	int pos = ++ptr_heap->n_;
	if(pos > MAXSIZE)
	{
		printf("heap full\n"); exit(1);
	}
	ptr_heap->key_[pos] = key;
//	while(pos > 1 && ptr_heap->key_[pos] > ptr_heap->key_[pos/2])
	while(pos > 1 && ptr_heap->compare(ptr_heap->key_[pos], ptr_heap->key_[pos/2]))
	{
		swap(&ptr_heap->key_[pos], &ptr_heap->key_[pos/2]);
		pos = pos / 2;
	}
}
int delete_root(heap_t *ptr_heap)
{
	if(ptr_heap->n_ == 0)
	{
		printf("heap empty\n"); exit(1);
	}
	int res = ptr_heap->key_[1];
	ptr_heap->key_[1] = ptr_heap->key_[ptr_heap->n_];
	
	heapify(ptr_heap->key_, --ptr_heap->n_, 1, ptr_heap->compare);
	return res;
}

int peek_root(heap_t *ptr_heap)
{
	return ptr_heap->key_[1];
}

int get_size(heap_t *ptr_heap)
{
	return ptr_heap->n_;
}




