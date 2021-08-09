#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include  "array_ops.h"


int main()
{
	int tester[ARRAY_MAX_SIZE];
	for (int i = 1; i <= 10; i++)
	{
		tester[i - 1] = i;
	}

	int src[ARRAY_MAX_SIZE];
	src[0] = 25;
	src[1] = 63;
	src[2] = 98;
	src[3] = 77;
	src[4] = 104;	

	for (int i = 0; i < 10; i++)
	{
		printf("tester[%d] = %d\n", i, tester[i]);
	}
	
	for (int i = 0; i < 5; i++)
	{
		printf("src[%d] = %d\n", i, src[i]);
	}

	array_insert(tester, 15, src, 5, 5);

	for (int i = 0; i < 15; i++)
	{
		printf("tester[%d] = %d\n", i, tester[i]);
	}
	return 0;
}
