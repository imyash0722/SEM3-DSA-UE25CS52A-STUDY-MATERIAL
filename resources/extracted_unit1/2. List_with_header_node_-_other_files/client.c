#include <stdio.h>
#include "mylist.h"

int main()
{
	mylist_t l;
	init_list(&l);
	int a[] = { 20, 10, 50, 30, 40};
	int n = 5;
	for(int i = 0; i < n; ++i)
	{
		insert_list(&l, a[i]);
	}
	disp_list(&l);
	free_list(&l);
}
