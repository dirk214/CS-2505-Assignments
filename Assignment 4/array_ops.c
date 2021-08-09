#include "array_ops.h"

// 
//	
//
// 
bool array_cmp(int lhs[], size_t lusage, int rhs[], size_t rusage)
{
	if (lusage != rusage)
		return false;
	else
	{
		for (int i = 0; i < lusage; i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
	}
	return true;
}

// 
//	
//
//
size_t array_append(int dest[], size_t dusage, int src[], size_t susage)
{
	if (dusage + susage > ARRAY_MAX_SIZE)
		return dusage;
	else
	{
		for (int i = 0; i < susage; i++)
		{
			dest[dusage + i] = src[i];
		}
		return dusage + susage;
	}
}

//
//
//
//
size_t array_insert(int dest[], size_t dusage, 
			int src[], size_t susage, size_t index)
{
	if (dusage + susage > ARRAY_MAX_SIZE || index > dusage)
		return dusage;	
	else
	{
		int cdest[ARRAY_MAX_SIZE];
		for (int l = 0; l < dusage; l++)
		{
			cdest[l] = dest[l];
		}
		for (int i = 0; i < susage; i++)
		{			
			for (int z = 0; z < dusage; z++)
			{
				dest[index + z + 1 + i] = cdest[index + z];
			}
			dest[index + i] = src[i];
		}
		return dusage + susage;
	}
}


//
// 
//
//
size_t array_erase(int array[], size_t usage, size_t index, size_t count)
{
	if (index >= usage)
		return usage;
	else
	{
		int carray[usage + 1];
		for (int i = 0; i < usage; i++)
		{
			carray[i] = array[i];
		}
		for (int i = 0; i < count; i++)
		{
			for (int g = 0; g < usage; g++)
			{
				array[index + g] = carray[index + g + 1];
			}
		}
		return usage - count;
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
