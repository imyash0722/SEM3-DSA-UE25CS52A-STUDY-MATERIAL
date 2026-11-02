#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
// implementation of queue using a circular list 
// To make the logic simpler, we use the same condition for 
// is_empty and is_full.
// if they are equal 
void init_queue(queue_t *ptr_queue)
{
	// could be any valid index in the array
	ptr_queue->rear_ = ptr_queue->front_ = 0; 
}

void deinit_queue(queue_t *ptr_queue)
{
	ptr_queue->rear_ = ptr_queue->front_ = 0;
}



void enque(queue_t *ptr_queue, int key)
{
	int temp;
	temp = ++ptr_queue->rear_ % MAXSIZE;
	ptr_queue->rear_ = temp;
	if(! is_full(ptr_queue))
	{
		ptr_queue->key_[temp] = key;
	}	
	else 
	{
		ptr_queue->rear_ = (ptr_queue->rear_ - 1 + MAXSIZE) % MAXSIZE;
		printf("queue full; cannot push\n");
	}
}
int deque(queue_t *ptr_queue)
{
	if(! is_empty(ptr_queue))
	{
		int key;  int temp = ++ptr_queue->front_ % MAXSIZE;
		key = ptr_queue->key_[temp];
		ptr_queue->front_ = temp;
		return key;
	}
	else 
	{
		printf("queue empty; cannot pop\n");
		return '\0';
	}
}
// to be called before deque before incrementing
int is_empty(queue_t *ptr_queue)
{
	return ptr_queue->front_ == ptr_queue->rear_;
}

// to be called in enque after incrementing
int is_full(queue_t *ptr_queue)
{
	return ptr_queue->front_ == ptr_queue->rear_;
}