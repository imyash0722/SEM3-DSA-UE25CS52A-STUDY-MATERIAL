#ifndef queue_H
#define queue_H 

#define MAXSIZE 5
struct queue 
{
	int key_[MAXSIZE];
	int front_;
	int rear_;
};
typedef struct queue queue_t;

void init_queue(queue_t *ptr_queue);
void deinit_queue(queue_t *ptr_queue);
void enque(queue_t *ptr_queue, int ch);
int deque(queue_t *ptr_queue);
int is_empty(queue_t *ptr_queue);
int is_full(queue_t *ptr_queue);


#endif