#include "BinaryInt.h"
#include <inttypes.h>

// Internal representation stores bits so that coefficient of 2^i is at index i.

/**
 *   Initializes BinInt[] so that the elements correspond to the 2's complement
 *   representation of the 32-bit integer Src.
 * 
 *   Pre:   BinInt[] is of dimension 32
 *   Post:  For i = 0 to 31, BinInt[i] == 2^i bit of Src
 */
void BI_Create(uint8_t BinInt[], int32_t Src) 
{
   int32_t Mask = 0x01;
   for (int pos = 0; pos < NUM_BITS; pos++) {
      BinInt[pos] = ( Src & Mask) ? 1 : 0;
      Mask = Mask << 1;
   }
}

/**
 *   Converts a BinInt[] to its decimal representation.
 * 
 *   Pre:   Num[] is of dimension 32
 *          Num[] stores a 2's complement representation integer 
 *   Ret:   The decimal value.
 *    
 */
int32_t BI_ToDecimal(const uint8_t Num[])
{
	int32_t sum = 0;
	if (Num[31] == 1)
	{
		BI_Neg(Num, Num);
		for (int i = 1; i <= 30; i++)
		{
			if (Num[i] == 1)
			{
				int adder = 1;
				for (int j = 0; j < i; j++)
				{
					adder = adder * 2;
				}
				sum += adder;
			}
		}
		if (Num[0] == 1)
		{
			sum += 1;
		}
		sum = sum * -1;
	}
	else
	{
		for (int i = 1; i <= 30; i++)
		{
			if (Num[i] == 1)
			{
				int adder = 1;
				for (int j = 0; j < i; j++)
				{
					adder = adder * 2;
				}
				sum += adder;
			}
		}
		if (Num[0] == 1)
		{
			sum += 1;
		}
	}
	return sum;
}


/**
 *   Computes sum of 2's complement representations of integer values.
 * 
 *   Pre:   Sum[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement representations
 *   Post:  Sum[] == Left[] + Right[], if possible
 *   Ret:   false if overflow occurs when computing sum of Left[] and Right[];
 *          true otherwise
 */
bool BI_Add(uint8_t Sum[], const uint8_t Left[], const uint8_t Right[]) 
{
	
	int rr = 0;
	int pt = 0;
	int rs = Right[31];
	int ls = Left[31];

	
	for (int i = 0; i <= 31; i++)
	{				pt = Left[i] + Right[i] + rr;
		if (pt == 3)
		{				
			rr = 1;
			Sum[i] = 1;
		}
		else if (pt == 2)
		{
			rr = 1;
			Sum[i] = 0;
		}
		else if (pt == 1)
		{
			rr = 0;
			Sum[i] = 1;
		}
		else
		{
			rr = 0;
			Sum[i] = 0;
		}
	}

	if (Left[31] == 1 && Right[31] == 1 && Sum[31] == 0)
	{
		return false;
	}
	else if (Left[31] == 0 && Right[31] == 0 && Sum[31] == 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 *   Computes difference of 2's complement representations of integer values.
 * 
 *   Pre:   Diff[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement representations
 *   Post:  Diff[] == Left[] - Right[], if possible
 *   Ret:   false if overflow occurs when computing difference of Left[]
 *          and Right[]; true otherwise 
 */
bool BI_Sub(uint8_t Diff[], const uint8_t Left[], const uint8_t Right[]) 
{
	BI_Neg(Right, Right);
	return BI_Add(Diff, Left, Right);
}

/**
 *   Computes negation of 2's complement representation of integer value.
 * 
 *   Pre:   Neg[] and Right[] are of dimension 32
 *          Right[] stores a 2's complement representation
 *   Post:  Neg[] = -Right[]
 *   Ret:   false if negation cannot be correctly represented; 
 *          true otherwise
 */
bool BI_Neg(uint8_t Neg[], const uint8_t Right[]) 
{
	int found = 0;
	int spot = 0;
	for (int i = 0; i <= 31; i++)
	{
		if (Right[i] == 1 && found == 0)
		{
			found = 1;
			spot = i;
		}
	}
	
	if ((found == 0 && spot == 0) || (found == 1 && spot == 31))
	{
		return false;
	}
	else
	{
		for (int j = 0; j <= 31 - spot; j++)
		{
			if (Right[j + spot] == 1)
			{
				Neg[j + spot] = 0;
			}
			else
			{
				Neg[j + spot] = 1;
			}
		}
	
		Neg[spot] = 1;
		return true;
	}
}

/**
 *   Prints 2's complement representation, with formatting.
 * 
 *   Pre:   fp is open on an output stream
 *          BinInt[] is of dimension 32 and stores a 2's complement
 *             representation
 *          prefix and suffix are each NULL or point to a C-string
 *   Post:  the bits represented in BinInt[] have been written, preceded by
 *          prefix (if not NULL) and followed by suffix (if not NULL)
 */
void BI_fprintf(FILE* fp, const uint8_t BinInt[], char* prefix, char* suffix) 
{
   if ( prefix != NULL)
      fprintf(fp, prefix);
      
   for (int pos = NUM_BITS - 1; pos >= 0; pos--) {
       if ( pos < NUM_BITS - 1 && pos % 4 == 3 )
          fprintf(fp, " ");
     
      fprintf(fp, "%"PRIu8, BinInt[pos]);
   }
   
   if ( suffix != NULL)
      fprintf(fp, suffix);
}





//   On my honor:
//
//   - I have not discussed the C language code in my program with
//     anyone other than my instructor or the teaching assistants 
//     assigned to this course.
//
//   - I have not used C language code obtained from another student,
//     or any other unauthorized source, either modified or unmodified.  
//
//   - If any C language code or documentation used in my program 
//    was obtained from an allowed source, such as a text book or course
//    notes, that has been clearly noted with a proper citation in
//    the comments of my program.
//
//   <Andrew Herbert>
