#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "bytes.h"


//
//
//
//
void bytes_init(bytes_t * const bytes)
{
	bytes->data = NULL;
	bytes->usage = 0;
	bytes->dim = DEFAULT_SIZE;
}


//
//
//
//
void bytes_free(bytes_t * const bytes)
{
	free(bytes->data);
	bytes->data = NULL;
}


//
//
//
//
void bytes_fprintf(FILE * out, const bytes_t * const bytes)
{
	const uint8_t *data = (bytes->data == NULL) ? bytes->dflt : bytes->data;

	fprintf(out, "          ");

	for (size_t b = 0; b < BYTES_PER_LINE; b++)
	{
		fprintf(out, "%02zx ", b);
	}
	fprintf(out, "\n");

	fprintf(out, "         ");
	fprintf(out, " -----------------------------------------------");
	fprintf(out, "\n");

 	for (size_t x = 0; x < bytes->usage; x += 16)
	{
		size_t min = (bytes->usage  >= x + BYTES_PER_LINE) 
				? x + BYTES_PER_LINE : bytes->usage; 

		fprintf(out, "%08zx  ", x);
	
		for (size_t y = x; y < min; y++)
		{ 
			fprintf(out, "%02"PRIx8" ", data[y]);
		}
		fprintf(out, "\n");
	}

	fprintf(out, "         ");
	fprintf(out, " -----------------------------------------------");
	fprintf(out, "\n");
	fprintf(out, "\n");
	
}


//
//
//
//
bool bytes_empty(const bytes_t * const bytes)
{
	return (bytes->usage);
}


//
//
// If bytes->data is Null return dflt is returned. Otherwise data is returned.
//
uint8_t * bytes_data(const bytes_t * const bytes)
{
	if (bytes->data == NULL)
	{
		return bytes->dflt;
	}
	return bytes->data;
}


//
//
//
//
size_t bytes_usage(const bytes_t * const bytes)
{
	return bytes->usage;
}


//
//
//
//
bool bytes_set(bytes_t * const bytes, size_t index, uint8_t val)
{
	if (index < bytes->usage)
	{
		bytes->data[index] = val;
	}
	else if (index <= DEFAULT_SIZE)
	{
		bytes->dflt[index] = val;
	}
	else
	{
		return false;
	}
	return true;
}


// Gets a 1 byte, 2 byte, 4 byte, or 8 byte value from *bytes, and
// interprets it as either a big or little endian value.
//
// Enumerations are provided for both the width (width_t) and byte
// order (endian_t). These enumerations can be used as more than just
// a constant to compare against. Since they are integer values they 
// might be used as part of the computation.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Post:
//	Tries to read a width sized value and interprets it as if it had
//	order, byte ordering. The result is stored in output variable, result. 
//
// Returns:
//	If there are enough bytes starting at index to get a width sized
//	value the function returns true, false otherwise.
//
// Examples:
//	If bytes->data (or dlft) contains the bytes: {0xDE, 0xAD, 0xBE, 0xEF} 
//
//	If we interpret it as a 4 byte value, then in big endian order it
//	is 0xDEADBEEF, the highest order byte is in the lowest index, 0.
//
//	In little endian order it would be interpreted as 0xEFBEADDE, 
//	the highest order byte is in the largest index, 3.
//
//
bool bytes_get(const bytes_t * const bytes, size_t index, 
		width_t width, endian_t order, uint64_t * const result)
{
	bool possible = true;
	if (width == BITS8)
	{
		
	}
	else if (width == BITS16)
	{
		if (order == LITTLE)
		{
			
		}
		else if (order == BIG)
		{
			for (int i = 0; i < 2; i++)
			{
				//*result << 8;
				//if (*bytes->dflt[index + i] != NULL)
				//{
				//	*result = *result + *bytes->dflt[index + i];
				//}
				//else
				//{
				//	possible = false;
				//}
			}
		}
	}
	else if (width == BITS32)
	{
		if (order == LITTLE)
		{
			
		}
		else if (order == BIG)
		{
			
		}
	}
	else if (width == BITS64)
	{
		if (order == LITTLE)
		{
			
		}
		else if (order == BIG)
		{
			
		}
	}
	else
	{
		possible = false;
	}
	return possible;
}


//
//
//
//
bool bytes_insert(bytes_t * bytes, size_t index, 
			const uint8_t * buf, size_t len)
{
	return false;

}


//
//
//
//
bool bytes_erase(bytes_t * const bytes, size_t index, size_t len)
{
  	if (index < bytes->usage)
    	{
      		for(int i = 0; i < len; i++)
    		{
      			bytes->data[index + i] = 0;
    		}
      		return true;
    	}
  	else if (index < DEFAULT_SIZE)
    	{
      		for (int i = 0; i < len; i++)
    		{
      			bytes->dflt[index + i] = 0;
    		}
      		return true;
    	}
  	else if (index + len > bytes->usage)
    	{
      		for (int i = 0; i < bytes->usage - index; i++)
    		{
      			bytes->data[index + i] = 0;
    		}
      		return true;
    	}
    	return false;
}


//
//
//
//
uint8_t * bytes_range(const bytes_t * const bytes, range_t *range)
{
	return NULL;
}


//
//
//
//
bool bytes_copy(bytes_t * const dest, const bytes_t * const src)
{
 
	*dest = malloc(sizeof(bytes_t));
	dest->usage = src->usage;
	dest->dim = src->dim;
   	if (src->usage > DEFAULT_SIZE)
   	{
        	dest->data = malloc(src->dim * sizeof(uint8_t));
   		if (dest->data == NULL)
        	{
        		return false;
        	}
     		for (int k = 0; k< src->usage; k++)
        	{
        		dest->data[k] = src->data[k];
       		}
     
   	}
   	else
   	{
      		for (int k = 0; k< DEFAULT_SIZE; k++)
     		{
        		dest->dflt[k] = src->dflt[k];
       		}
   	}
   	return true;
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
