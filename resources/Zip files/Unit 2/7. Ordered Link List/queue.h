#ifndef queue_H
#define queue_H 
#define MAXSIZE 100

struct node
{
	job_t jobx_;
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
void enque(queue_t *ptr_queue, job_t *ptr_job);
job_t deque(queue_t *ptr_queue);
int is_empty(queue_t *ptr_queue);
int is_full(queue_t *ptr_queue);


#endif