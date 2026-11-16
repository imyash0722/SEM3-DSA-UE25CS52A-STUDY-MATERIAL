#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(queue_t *ptr_queue)
{
	init(&ptr_queue->q_);
}

void deinit_queue(queue_t *ptr_queue)
{
	deinit(&ptr_queue->q_);
}



void enqueue(queue_t *ptr_queue, int key)
{
	insert(&ptr_queue->q_, key);

}
int dequeue(queue_t *ptr_queue)
{
	return delete_max(&ptr_queue->q_);
}
