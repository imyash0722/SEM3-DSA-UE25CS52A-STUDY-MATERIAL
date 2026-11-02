#include <stdio.h>
#include <stdlib.h>
struct X
{
	int a;
};
struct Y
{
	int b;
	struct X x;
};
#if 0
struct Z
{
	int c;
	struct Z z; // infinitely recursively included

};
#endif

// self referential structure
struct A
{
	int c;
	struct A *p;  
};

int main()
{
	printf("size : %lu\n", sizeof(struct X));
	printf("size : %lu\n", sizeof(struct Y));
	//printf("size : %lu\n", sizeof(struct Z));
	printf("size : %lu\n", sizeof(struct A));
	
	struct A one;
	one.c = 10;
	one.p = &one;
	printf("%d %d %d\n", one.c, one.p->c, one.p->p->c);
	

}











