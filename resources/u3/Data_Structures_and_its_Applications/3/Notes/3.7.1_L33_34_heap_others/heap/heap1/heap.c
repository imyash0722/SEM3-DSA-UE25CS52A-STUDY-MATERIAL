#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void init(heap_t *ptr_heap)
{
	ptr_heap->n_ = 0;
}

void deinit(heap_t *ptr_heap)
{
	ptr_heap->n_ = 0;
}

void disp(heap_t *ptr_heap)
{
	for(int i = 1; i <= ptr_heap->n_; ++i)
	{
		printf("%d ", ptr_heap->key_[i]);
	}
	printf("\n");
}

static void heapify(int a[], int n, int pos)
{
	int i = pos;
	int j = 2 * i;
	int val = a[i];
	int is_heap = 0;
	while(j <= n && ! is_heap)
	{
		if(j + 1 <= n && a[j+1] > a[j])
			++j;
		if(a[j] > val)
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

// indexed from 1 in both the arrays
void build_heap(heap_t *ptr_heap, int a[], int n)
{
	ptr_heap->n_ = n;
	for(int i = 1; i <= n; ++i)
	{
		ptr_heap->key_[i] = a[i];
	}
	for(int i = n / 2; i >= 1; --i)
	{
		heapify(ptr_heap->key_, ptr_heap->n_, i);
		disp(ptr_heap);
	}
}

