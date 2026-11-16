#include <stdio.h>
#include <stdlib.h>
#include "median.h"
#define DEBUG 0
//init_median(&median, &h_left, &h_right, max, min);
void init_median(median_t *ptr_median, heap_t* left, heap_t* right, 
	int (*max)(int, int), int (*min)(int, int))
{
	init_heap(&ptr_median->left_, max);
	init_heap(&ptr_median->right_, min);
	
}
void insert_median(median_t *ptr_median, int key)
{
	int left_n = get_size(&ptr_median->left_);
	int right_n = get_size(&ptr_median->right_);
	if(left_n == 0 || 
		key <= peek_root(&ptr_median->left_))
	{
		insert(&ptr_median->left_, key);
	}
	else 
	{
		insert(&ptr_median->right_, key);
	}
	left_n = get_size(&ptr_median->left_);
	right_n = get_size(&ptr_median->right_);
	if(left_n > right_n + 1)
	{
		insert(&ptr_median->right_, delete_root(&ptr_median->left_));
	}
	else if(right_n > left_n)
	{
		insert(&ptr_median->left_, delete_root(&ptr_median->right_));
	}
	if(DEBUG)
	{
		printf("max heap : ");
		disp(&ptr_median->left_);
		printf("min heap : ");
		disp(&ptr_median->right_);
		printf("--------------------------\n");
	}
}

double find_median(median_t *ptr_median)
{
	double find_median(median_t *m) {
    int l = get_size(&m->left_);
	int r = get_size(&m->right_);
    if (l + r == 0)		
	{ 
		printf("no elements\n"); exit(1);
	}
    if (l > r) 
	{	
		return (double)peek_root(&m->left_);
	}
    return (peek_root(&m->left_) + (double)peek_root(&m->right_)) / 2.0;
}

}


void deinit_median(median_t *ptr_median)
{
	deinit_heap(&ptr_median->left_);
	deinit_heap(&ptr_median->right_);
	
}
