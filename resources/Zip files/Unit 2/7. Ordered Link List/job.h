#ifndef JOB_H
#define JOB_H
struct job 
{
	int job_no_;
	int priority_;
};
typedef struct job job_t;

void set_job(job_t* ptr_job, int job_no, int priority);
void disp_job(job_t* ptr_job);
int get_priority(job_t* ptr_job);

#endif
