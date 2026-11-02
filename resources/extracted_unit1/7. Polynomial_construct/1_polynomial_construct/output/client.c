#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
int eval(poly_t ptr_poly)
{
	
}
int main()
{
	int coeff[] = { 5, 4, 3, 2, 1};
	int expo[] = { 2, 6, 0, 4, 8};
	int n = 5;
	poly_t mypoly;
	init_poly(&mypoly);
	for(int i = 0; i < n; ++i)
	{
		insert(&mypoly, coeff[i], expo[i]);
	}
	disp(&mypoly);
	

}