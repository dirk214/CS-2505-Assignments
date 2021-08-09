#include "Untangle.h"

uint8_t Untangle(uint8_t* Buffer, FILE* Log)
{
	uint8_t count = 0;
	uint16_t referencer = *((uint16_t*) Buffer);
	while (referencer != 0)
	{
		uint8_t* cBuff = Buffer;
		int amount = Buffer[referencer];
		char Word[amount + 1];
		Word[amount] = '\0';
		fprintf(Log, "%04X: ", referencer);
		for (int i = 0; i < amount; i++)
		{
			Word[i] = Buffer[referencer + 1];
			referencer++;
		}
		for (int i = 0; i < amount; i++)
		{
			if ((Word[i] >= 65) & (Word[i] <= 90))
			{
				if (Word[i] - 13 < 65)
				{
					int temp = Word[i] - 65;
					temp = 13 - temp;
					Word[i] = 90 - temp + 1;				
				}
				else
				{
					Word[i] = Word[i] - 13;
				}
			}
			else if ((Word[i] >= 97) & (Word[i] <= 122))
			{
				if (Word[i] - 13 < 97)
				{
					int tems = Word[i] - 97;
					tems = 13 - tems;
					Word[i] = 122 - tems + 1;					
				}
				else
				{
					Word[i] = Word[i] - 13;
				}
			}
		}
		fprintf(Log, "%s\n", Word);
		cBuff += referencer + 1;
		uint16_t referencermox = *((uint16_t*) cBuff);
		referencer = referencermox;
		for (int i = 0; i < amount; i++)
		{
			Word[i] = 0;
		}
		count++;
	}
	return count;
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
