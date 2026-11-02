#ifndef LIST_H
#define LIST_H
#include "term.h"
// user: list of terms
struct node 
{
	term_t term_;
	struct node *next_;
};
typedef struct node node_t;

struct poly 
{
	node_t* head_;
};
typedef struct poly poly_t;

void init_poly(poly_t* ptr_poly);
void insert(poly_t* ptr_poly, int coeff, int expo);
void disp(poly_t* ptr_list);
int eval(poly_t* ptr_poly, int x);

#endif