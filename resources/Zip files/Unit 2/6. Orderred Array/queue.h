#ifndef queue_H
#define queue_H 
#include "job.h"
#define MAXSIZE 10
struct queue 
{
	job_t key_[MAXSIZE];
	int n_; // # of elements
};
typedef struct queue queue_t;

void init_queue(queue_t *ptr_queue);
void deinit_queue(queue_t *ptr_queue);
void enque(queue_t *ptr_queue, job_t* ptr_job);
job_t deque(queue_t *ptr_queue);
int is_empty(queue_t *ptr_queue);
int is_full(queue_t *ptr_queue);


#endif