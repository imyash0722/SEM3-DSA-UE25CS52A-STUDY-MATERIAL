#include <stdio.h>
#include "median.h"
int max (int x, int y)
{
	return x > y;
}
int min (int x, int y)
{
	return x < y;
}
int main()
{
	heap_t h_left; // max_heap
	heap_t h_right; // min_heap

	median_t median;
	init_median(&median, &h_left, &h_right, max, min);
	int a[] = {10, 30, 20, 15, 5, 2, 40, 60, 50, 3};
	int n = 10;
	for(int i = 0; i < n; ++i)
	{
		insert_median(&median, a[i]);
		printf("%lf ", find_median(&median));
	}
	printf("\n");
	deinit_median(&median);
}