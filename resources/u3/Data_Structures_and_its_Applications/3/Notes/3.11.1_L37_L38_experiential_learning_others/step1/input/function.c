#include <stdio.h>
#include "function.h"

void mymap(int a[], int b[], int n, int (*op)(int))
{
	for(int i = 0; i < n; ++i)
	{
		b[i] = op(a[i]);
	}
}
// TODO 
// select only those which satisfy the function; copy to b; 
// store in *ptr_m the number of elements in b 
void myfilter(int a[], int n, int b[], int *ptr_m, int (*op)(int));
// start with an initial value 
// traverse the array a 
// apply the function op - requires two parameters - init and the element
// update the init. Repeat.
// Ultimately return one value
int myreduce(int a[], int n, int init, int (*op)(int, int));