#include <stdio.h>
#include <stdlib.h>

struct node
{
	int key_;
	struct node *next_;  
};
typedef struct node node_t;

void disp(node_t* q)
{
	while(q != NULL)
	{
		printf("%d ", q->key_);
		q = q->next_;
	}
}
void freelist(node_t* q)
{
	node_t* r;
	while(q != NULL)
	{
		r = q->next_;
		free(q);
		q = r;
	}

}
int main()
{
	node_t *p;
	p = (node_t*)malloc(sizeof(node_t));
	p->key_ = 20;
	p->next_ = (node_t*)malloc(sizeof(node_t));
	p->next_->key_ = 40;
	p->next_->next_ = (node_t*)malloc(sizeof(node_t));
	p->next_->next_->key_ = 60;
	p->next_->next_->next_ = NULL;
	disp(p);
	freelist(p);
}














	
