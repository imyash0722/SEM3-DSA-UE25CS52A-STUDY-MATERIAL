#ifndef queue_H
#define queue_H 

struct node
{
	int key_;
	struct node* next_;
};
typedef struct node node_t;

struct queue 
{
	node_t* front_;
	node_t* rear_;
};
typedef struct queue queue_t;

void init_queue(queue_t *ptr_queue);
void deinit_queue(queue_t *ptr_queue);
void enqueue(queue_t *ptr_queue, int key);
int dequeue(queue_t *ptr_queue);
int is_empty(queue_t *ptr_queue);
int is_full(queue_t *ptr_queue);


#endif