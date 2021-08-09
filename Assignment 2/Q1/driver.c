#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "reverse.h"

void test_reverse();

int main() 
{
   test_reverse();
   
   return 0;
}

void test_reverse()
{
   // You can hardwire value below and recompile to test your solution.
   uint64_t value = 12345;
   uint64_t result = reverse(value);

   printf("%21"PRIu64"%21"PRIu64"\n", value, result);
}
