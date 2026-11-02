#ifndef DLLH
#define DLLH

typedef struct job {
  int jobid;
  int required;
  int done;
} job_t;

typedef struct node {	
    job_t *job;
    struct node *prev;
    struct node *next;
} node;

typedef struct DLL {
	node *current;
} dll;

void init(dll *ptrdll);
void deinit(dll *ptrdll);

void ins(dll *ptrdll, job_t job);

void disp_forward(dll *ptrdll);
void disp_backward(dll *ptrdll);

void del(dll *ptrdll);
#endif

