#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

/* Main function */
int main()
{
    clist_t myclist;
	init_clist(&myclist);

    insert(&myclist, 10);
    disp_list(&myclist);
	getchar();
	
    insert(&myclist, 20);
    disp_list(&myclist);
	getchar();
	

	insert(&myclist, 30);
    disp_list(&myclist);
	getchar();
	

    insert(&myclist, 5);
    printf("After inserting 5 at beginning:\n");
    disp_list(&myclist);
	getchar();

    return 0;
}