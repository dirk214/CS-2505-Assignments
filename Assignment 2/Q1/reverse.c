#include "reverse.h"

uint64_t reverse(uint64_t value)
{
	uint64_t Accum = 0;
	while(value > 0)
	{
		Accum = Accum*10 + value%10;
		value = value/10;
	}

	return Accum;
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
