// bigMesa.c

#define MIN_MESA_LENGTH 5

/**
 *  Given an array of nonnegative integers, a mesa is a sequence of 5 or
 *  more identical values.  The length of a mesa is the number of values
 *  in the sequence, and the mass of a mesa is the sum of the values in
 *  the sequence.
 *
 *  bigMesa() determines the mesa of maximum mass in the array that is
 *  passed into it.  bigMesa() reports its results by setting three extern
 *  variables:  mesaStart, mesaEnd and mesaMass.
 *
 * Pre:  A[0:A_Size - 1] are nonnegative integers.
 * Post: mesaStart = index of first element of most massive mesa
 *       mesaEnd   = index of last element of most massive mesa
 *       mesaMass  = sum of elements in most massive mesa
 *       All are set to zero if no mesa is found.
 *
 * Restrictions:
 *    You may not use a second array.
 */ 
void bigMesa(int A[], int A_Size) 
{

   // Link to the caller-supplied variables to report results:
   extern int mesaMass;
   extern int mesaStart;
   extern int mesaEnd;
   
   // Set default values in case no mesa is found in the array:
   mesaMass  = 0;
   mesaStart = 0;
   mesaEnd  = 0;
   
   // Actual solution code goes here:
	
	int lastindex = 0;
	int currentmass = 0;	
	int current = 1;
	int max = 1;
	int maxmass = 0;	

	for (int i = 0; i < A_Size - 1; i++)
	{
		if (A[i] == A[i+1])
		{
			current++;
			currentmass += A[i];
			if (currentmass > maxmass && current >= 5)
			{
				max = current;
				maxmass = currentmass;
				lastindex = i + 1;
			}
		}
		else
		{
			current = 1;
			currentmass = 0;
		}
	}
	if (max >= 5)
	{
		mesaEnd = lastindex;
		mesaStart = lastindex - max + 1;
		mesaMass = maxmass + A[mesaStart];
	}


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
