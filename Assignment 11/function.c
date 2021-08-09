
#include <stdlib.h>
#include <stdint.h>

// Your pids here: cater, dirk214
//
//

// Fill in your answers in the comments below, one line per answer.

// Q1A:1 because you have enough space for 5 integers and you have to account for rbp 
// Q1B:while loop and the while loop instructions #7-#23, the loop test is at the end of the loop and it checks to see if b < P1
// Q1C:the if statement is from #19-#22,looking at if the remainder is 0 you return 0 and if not you return 1
// Q1E:finding prime numbers
//
int Q1(int P1)
{
  int b = 2;

  while(b < P1)
    {
	if(P1%b != 0)
	  {
	    
	    b++;
	  }
	else
	  {
	return 0;
	  }
      }
    
	return 1;
}


// Q2B: 
//finding the greater of the 2 variables
//
//
int Q2(int P1, int P2)
{
  if (P1 >= P2)
    {
      return P1;
    }
	return P2;
}


// Q3 Functions, fill in the function bodies

// Q3A
//print out a char variable
//
//
void char_out(char P1)
{
  putchar(P1);
}


// Q3B
//converting a number to a letter
//
//
void sub_mystery(uint64_t P1)
{
  if(P1 > 9)
    {
      char p = P1 + 55;
      char_out(p);
    }
  else
    {
  char c = P1 + 48;
  char_out(c);
    }
} 

// Q3C
//
//converts a number to hexidecimal
//
int mystery(uint64_t P1)
{
  uint64_t local1 = P1;
  uint64_t local2 = 1;
  uint64_t local3 = 0;
  while(local1 > 15)
    {
      local2 = local2 << 4;
      local1 = local1 >> 4;
    }
  while(local2 != 0)
    {
      local1 = P1;
      uint64_t r = local1%local2;
      local1 = local1/local2;
      sub_mystery(local1);
      local3++;
      P1 = r;
      local2 = local2 >> 4;
    }
  return local3;
}
