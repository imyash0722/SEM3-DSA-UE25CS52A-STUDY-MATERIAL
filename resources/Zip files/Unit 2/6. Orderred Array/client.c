#include <stdio.h>
#include "job.h"
#include "queue.h" 



int main()
{
	queue_t q;
	init_queue(&q);
	int opt;
	job_t jobx;
	int priority;
	int job_no = 1;
	printf("opt : 1 : enque; 2 : deque ; 0 : quit\n");
	scanf("%d", &opt);
	while(opt)
	{
		switch(opt)
		{
			case 1 : scanf("%d", &priority);
					 set_job(&jobx, job_no++, priority);
					 printf("Adding : ");
					 disp_job(&jobx);
					 enque(&q, &jobx);
					 break;
			case 2 : jobx = deque(&q);
					 printf("removing : ");
					 disp_job(&jobx);
					 break;
		}
		printf("opt : 1 : enque; 2 : deque ; 0 : quit\n");
		scanf("%d", &opt);
	}
}