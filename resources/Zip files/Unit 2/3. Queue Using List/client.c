#include <stdio.h>
#include "queue.h" 

int main()
{
	queue_t q;
	init_queue(&q);
	int opt;
	int val;
	printf("opt : 1 : enqueue; 2 : dequeue ; 0 : quit\n");
	scanf("%d", &opt);
	while(opt)
	{
		switch(opt)
		{
			case 1 : scanf("%d", &val);
					 enqueue(&q, val);
					 break;
			case 2 : val = dequeue(&q);
					 if(val != 0)
						 printf("dequeue %d\n", val);
					 break;
		}
		printf("opt : 1 : enqueue; 2 : dequeue ; 0 : quit\n");
		scanf("%d", &opt);
	}
	deinit_queue(&q);
}