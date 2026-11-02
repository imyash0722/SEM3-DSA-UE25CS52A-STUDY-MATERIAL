#include <stdio.h>
#include "dll.h"

int main()
{
	dll_t mydll;
	init_dll(&mydll);
    insert_end(&mydll, 10);
    insert_end(&mydll, 20);
    insert_end(&mydll, 30);

    disp_forward(&mydll);
    disp_backward(&mydll);
	

    insert_begin(&mydll, 5);
    printf("\nAfter inserting 5 at beginning:\n");
    disp_forward(&mydll);


	insert_after(&mydll, 20, 25);
    printf("\nAfter inserting 25 after 20:\n");
    disp_forward(&mydll);

 
	insert_after(&mydll, 30, 40);
    printf("\nAfter inserting 40 after 30:\n");
    disp_forward(&mydll);


    delete_begin(&mydll);
    printf("\nAfter deleting from beginning:\n");
    disp_forward(&mydll);


    delete_end(&mydll);
    printf("\nAfter deleting from end:\n");
    disp_forward(&mydll);
	

    delete_value(&mydll, 20);
    printf("\nAfter deleting 20:\n");
    disp_forward(&mydll);

    

    return 0;
}