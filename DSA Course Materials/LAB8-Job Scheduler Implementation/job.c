#include <stdio.h>
#include "job.h"

void set_job(job_t* ptr_job, int job_no, int priority)
{
	ptr_job->job_no = job_no;
	ptr_job->priority = priority;
}

void disp_job(job_t* ptr_job)
{
	printf("job # : %d priority : %d\n", 
		ptr_job->job_no, ptr_job->priority);
}

int get_priority(job_t* ptr_job)
{
	return ptr_job->priority;
}