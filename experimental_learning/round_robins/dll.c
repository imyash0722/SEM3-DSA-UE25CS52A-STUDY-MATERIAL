#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

void init(dll *ptrdll) {
	ptrdll->current = NULL;
}

void deinit(dll *ptrdll) {
	node* pres = ptrdll->current->next;
	while(pres != ptrdll->current) {
		node* temp = pres;
		pres = pres->next;
		free(temp);
	}
  free(ptrdll->current)
	ptrdll->current = NULL;
}

static node* createnode(job_t job) {
    node *temp;
    temp = (node*)malloc(sizeof(node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->job = job;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

void ins(dll* ptrdll, job_t job) {
	node *newNode = createnode(job);
	if(ptrdll->current == NULL) {
		ptrdll->current = ptrdll->current->next = ptrdll->current->prev = newNode;
	}	else {
    newNode->prev = ptrdll->current->prev;
    newNode->next = ptrdll->current;
		ptrdll->current->prev = newNode;
    if (ptrdll->current->next == ptrdll->current)
		  ptrdll->current->next = newNode;
	}
}

void disp(dll *ptrdll, bool reverse=0) {
  node_t *temp = ptrdll->current;
  printf("Forward:\n");
	if(temp != NULL)
	{
	  do {
			printf("%d %d %d\n", temp->job->jobid, temp->job->required, temp->job->done);
			temp = (reverse)?temp->prev:temp->next;
		} while (temp != ptr_dll->current);
	}
  printf("\n");
}

void process(dll *ptrdll) {
  timer = (required-done>=10)?10:required-done;
  
}

void process (dll_t *ptr_dll){
  if (ptrdll->current == NULL){
    printf("The list is empty");
  }
  else{
    node_t *temp = ptrdll->current;
    do {
      temp->job->done += 10;
      if(temp->job->done == temp->job->required || temp->job->done > temp->job->required){
        ptr_dll->current = temp;
        delete(ptrdll);
      }
      temp = temp->next;
    } while(temp != ptrdll->current);
  }
}

void del(dll *ptrdll) {
	if(ptr_dll->current == NULL) {
		printf("list is empty");
		return;
	}
	node_t *temp = ptr_dll->current;
	if(ptr_dll->current->next == ptr_dll->current->prev) {
		temp->next = temp->prev = NULL;
		free(temp);
		return;
	}
  ptr_dll->current->prev->next = ptr_dll->current->next;
  ptr_dll->current->next->prev = ptr_dll->current->prev;
	temp->next = temp->prev = NULL;
	free(temp);
}

