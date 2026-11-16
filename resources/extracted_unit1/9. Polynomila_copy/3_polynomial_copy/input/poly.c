#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

void init_poly(poly_t *ptr_poly)
{
	ptr_poly->head_ = NULL;
}

void disp(poly_t *ptr_poly)
{
	node_t* pres = ptr_poly->head_;
	while(pres != NULL)
	{
		//printf("%d ", pres->key_);
		disp_term(&pres->term_);
		pres = pres->next_;
	}
	printf("\n");
}

int eval(poly_t* ptr_poly, int x)
{
	node_t* pres = ptr_poly->head_;
	int res = 0;
	while(pres != NULL)
	{
		res += val(&pres->term_, x);
		pres = pres->next_;
	}
	return res;
}

void insert(poly_t* ptr_poly, int coeff, int expo) 
{
	node_t* temp;
	temp = (node_t*)malloc(sizeof(node_t));
	set_term(&temp->term_, coeff, expo);
	temp->next_ = NULL;
	
	// 1. empty poly 
	if(ptr_poly->head_ == NULL)
	{
		ptr_poly->head_ = temp;
		temp->next_ = NULL;
	}
	else // find the position
	{
		node_t* prev = NULL; 
		node_t* pres = ptr_poly->head_;
		//while(pres != NULL && pres->key_ < temp->key_)
		while(pres != NULL && 
			compare_exponents(&pres->term_, &temp->term_) > 0)
		{
			prev = pres;
			pres = pres->next_;
		}
		// beginning 
		if(prev == NULL)
		{
			ptr_poly->head_ = temp;
			temp->next_ = pres;
		}
		else // middle or end 
		{
			prev->next_ = temp;
			temp->next_ = pres;
		}
	}
	
}











