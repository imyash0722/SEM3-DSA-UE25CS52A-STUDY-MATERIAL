#include <stdio.h> 
#include "function.h" 
int sq(int x) { return x * x; } 
void disp(int a[], int n)
{
	for(int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
int main()
{
	int a[] = {1, 2, 3, 4, 5};
	int n = 5;
	int b[5];
	mymap(a, b, n, sq);
	disp(a, n);
	disp(b, n);
	
}