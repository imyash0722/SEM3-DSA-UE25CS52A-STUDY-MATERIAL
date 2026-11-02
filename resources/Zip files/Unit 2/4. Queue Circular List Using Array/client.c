#include <stdio.h>
#include "queue.h" 

int main()
{
	queue_t q;
	init_queue(&q);
	int opt;
	int val;
	printf("opt : 1 : enque; 2 : deque ; 0 : quit\n");
	scanf("%d", &opt);
	while(opt)
	{
		switch(opt)
		{
			case 1 : scanf("%d", &val);
					 enque(&q, val);
					 break;
			case 2 : val = deque(&q);
					 if(val != 0)
						 printf("deque %d\n", val);
					 break;
		}
		printf("opt : 1 : enque; 2 : deque ; 0 : quit\n");
		scanf("%d", &opt);
	}
}