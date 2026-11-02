#include <stdio.h>
#include "dll.h"

int main()
{
	dll mydll;
	initdll(&mydll);

    insertbegin(&mydll, 10);
    insertbegin(&mydll, 20);
    insertbegin(&mydll, 30);
    dispforward(&mydll);
    dispbackward(&mydll);
	
    
    insertend(&mydll, 5);
    printf("\nAfter inserting 5 at end:\n");
    dispforward(&mydll);

    insertafter(&mydll, 20, 25);
    printf("\nAfter inserting 25 after 20:\n");
    dispforward(&mydll);
 
    insertafter(&mydll, 30, 40);
    printf("\nAfter inserting 30 after 40:\n");
    dispforward(&mydll);


    deletebegin(&mydll);
    printf("\nAfter deleting from beginning:\n");
    dispforward(&mydll);
        
    deleteend(&mydll);
    printf("\nAfter deleting from end:\n");
    dispforward(&mydll);

    deletevalue(&mydll, 20);
    printf("\nAfter deleting 20:\n");
    dispforward(&mydll);

    return 0;
}
