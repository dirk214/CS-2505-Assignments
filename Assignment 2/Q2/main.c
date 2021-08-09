#include <stdio.h>

#include "print.h"

int main()
{
	print_with_commas(stdout, 1);
	printf(" ");
	print_with_commas(stdout, 123);
	printf(" ");
	print_with_commas(stdout, 1234);
	printf(" ");
	print_with_commas(stdout, 12345);

	return 0;
}
