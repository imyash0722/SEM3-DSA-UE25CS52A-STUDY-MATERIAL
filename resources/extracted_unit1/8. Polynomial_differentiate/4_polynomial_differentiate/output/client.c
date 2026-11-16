#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

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
	printf("source :\n");
	disp(&mypoly);
	
	// copy the list 
	poly_t mypoly_new;
	init_poly(&mypoly_new);
	// dst, src
	diff_poly(&mypoly_new, &mypoly);
	printf("dst : \n");
	disp(&mypoly_new);
	
	
	
	

}