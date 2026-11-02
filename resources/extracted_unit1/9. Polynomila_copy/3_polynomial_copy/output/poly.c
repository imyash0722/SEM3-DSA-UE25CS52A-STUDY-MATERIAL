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

node_t* create_node(int coeff, int expo)
{
	node_t* temp;
	temp = (node_t*)malloc(sizeof(node_t));
	set_term(&temp->term_, coeff, expo);
	temp->next_ = NULL;
	return temp;
}

void copy_poly(poly_t* ptr_poly_new, poly_t* ptr_poly)
{
	node_t* pres = ptr_poly->head_;
	node_t* pres_new = ptr_poly_new->head_;
	// take care of first node 
	if(pres != NULL)
	{
		node_t* temp = create_node(pres->term_.coeff_,
				pres->term_.expo_);
		pres_new = ptr_poly_new->head_ = temp;
		pres = pres->next_;
	}
	
	while(pres != NULL)
	{
		node_t* temp = create_node(pres->term_.coeff_,
			pres->term_.expo_);
		pres_new->next_ = temp;
		pres_new = temp;
		pres = pres->next_;
	}
}









