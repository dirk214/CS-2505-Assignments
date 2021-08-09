#include <stdio.h>

#define MAXLENGTH 50

int main()
{
	FILE* fi = fopen("ScoreData.txt", "r");
	FILE* fo = fopen("Results.txt", "w");
	char lineBuffer[MAXLENGTH];
	

	if ( fi == NULL )
	{ 
		printf("Error opening file ScoreData.txt.\n"); 
		return 1; 
	}

	while ( fgets(lineBuffer, MAXLENGTH, fi) != NULL ) 
	{ 
		int a = 0, b = 0;
		double c = 0, d = 0, e = 0, f = 0, g = 0, h = 0, i = 0, j = 0;
		sscanf(lineBuffer, "%d-%d %lf:%lf:%lf:%lf:%lf:%lf:%lf:%lf", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j);
		int count = 0;
		int test = 1;
		int testerArray[8] = {c, d, e, f, g, h, i, j};
		while (test !=0 && count < 8)
		{
			test = testerArray[count];
			if (test != 0)
			{
				count++;
			}
		}
		double sum = c + d + e + f + g + h + i + j;
		fprintf(fo, "%d%d: ", a, b);
		if (count == 0)
		{
			fprintf(fo, "no score data was read\n");
		}
		else
		{
			double average = sum/count;
			fprintf(fo, "%.2f on %d assignments\n", average, count);
		}
	}

	fclose(fi);
	fclose(fo);
	return 0;
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
