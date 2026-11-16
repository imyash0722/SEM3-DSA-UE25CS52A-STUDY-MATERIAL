#include <stdio.h>
#include "term.h"


void set_term(term_t* ptr_term, int coeff, int expo)
{
	ptr_term->coeff_ = coeff;
	ptr_term->expo_ = expo;
}

void disp_term(term_t* ptr_term)
{
	printf("%d X ^ %d\n", ptr_term->coeff_, ptr_term->expo_);
}

int compare_exponents(term_t* left, term_t* right)
{
	return left->expo_ - right->expo_;
}
int val(term_t* ptr_term, int x) 
{
	int res = 1;
	int expo = ptr_term->expo_;
	for(int i = 1; i <= expo; ++i)
	{
		res *= x;
	}
	return ptr_term->coeff_ * res;
}
