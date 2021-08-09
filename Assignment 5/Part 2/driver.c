#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "BinaryInt.h" 



int main()
{
	uint8_t tester[32];
	tester[0] = 1;
	tester[1] = 0;
	tester[2] = 0;
	tester[3] = 0;
	tester[4] = 0;
	tester[5] = 1;
	tester[6] = 1;
	tester[7] = 1;
	tester[8] = 0;
	tester[9] = 0;
	tester[10] = 0;
	tester[11] = 1;
	tester[12] = 0;
	tester[13] = 0;
	tester[14] = 1;
	tester[15] = 0;
	tester[16] = 1;
	tester[17] = 0;
	tester[18] = 0;
	tester[19] = 0;
	tester[20] = 0;
	tester[21] = 0;
	tester[22] = 0;
	tester[23] = 0;
	tester[24] = 0;
	tester[25] = 0;
	tester[26] = 0;
	tester[27] = 0;
	tester[28] = 0;
	tester[29] = 0;
	tester[30] = 0;
	tester[31] = 0;
	int32_t out = BI_ToDecimal(tester);
	printf("Value: %d" , out);
	
	return 0;
}
