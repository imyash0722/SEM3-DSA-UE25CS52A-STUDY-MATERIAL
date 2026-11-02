#ifndef queue_H
#define queue_H 
#include "heap.h"
struct node
{
	int key_;
	struct node* next_;
};
typedef struct node node_t;

struct queue 
{
	heap_t q_;
};
typedef struct queue queue_t;

void init_queue(queue_t *ptr_queue);
void deinit_queue(queue_t *ptr_queue);
void enqueue(queue_t *ptr_queue, int key);
int dequeue(queue_t *ptr_queue);
int is_empty(queue_t *ptr_queue);
int is_full(queue_t *ptr_queue);


#endif