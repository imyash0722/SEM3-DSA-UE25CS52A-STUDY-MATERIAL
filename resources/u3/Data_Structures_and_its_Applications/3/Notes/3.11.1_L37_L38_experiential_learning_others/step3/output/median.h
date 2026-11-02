#ifndef MEDIAN_H
#define MEDIAN_H 
#include "heap.h"
struct median
{
	heap_t left_;
	heap_t right_;
};
typedef struct median median_t;
void init_median(median_t *ptr_median, heap_t* left, heap_t* right, 
	int (*max)(int, int), int (*min)(int, int));
void insert_median(median_t *ptr_median, int key);
int find_median(median_t *ptr_median);
void deinit_median(median_t *ptr_median);
#endif