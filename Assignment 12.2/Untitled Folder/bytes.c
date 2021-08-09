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
	if (bytes->usage == 0)
	{
		return true;
	}
	return false;
}



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
bool bytes_set(bytes_t * const bytes, size_t index, uint8_t val)
{
	if (index < bytes->usage)
	{
		if (bytes->usage > DEFAULT_SIZE)
		{
			*(bytes->data + index) = val;
		}
		else
		{
			bytes->dflt[index] = val;
		}
		return true;
	}
	return false;
}


//
//
bool bytes_get(const bytes_t * const bytes, size_t index, 
		width_t width, endian_t order, uint64_t * const result)
{
	uint8_t* temp = bytes_data(bytes);
	int bit = 0;
    	*result = 0;
    	if (width == BITS8)
    	{
    	    bit = 1;
    	}
    	else if (width == BITS16)
   	{
        	bit = 2;
    	}
    	else if (width == BITS32)
    	{
    	    bit = 4;
    	}
    	else if (width == BITS64)
    	{
    	    bit = 8;
    	}
    	if(index + bit > bytes->usage)
    	{
    		return false;
    	}
    	if (order == BIG)
    	{
    		for(int i = 0; i < bit; i++)
    		{
      			uint8_t ja = temp[i + index];
      			*result = *result * 256;
      			*result = *result + ja;
     		}
       
    	}
    	else if (order == LITTLE)
    	{
      		for(int i = bit - 1; i >= 0; i--)
    		{
      			uint8_t ja = temp[i + index];
      			*result = *result * 256;
      			*result = *result + ja;
    		}
    	}
    	return true;
}



//
bool bytes_insert(bytes_t * bytes, size_t index, 
			const uint8_t * buf, size_t len)
{
	if (bytes->usage + len > bytes->dim)
    	{
      		if(bytes->data == NULL)
    		{
      			bytes->data = malloc((2*(bytes->usage + len))* sizeof(uint8_t));
      			if (bytes->data == NULL)
    			{
      				return false;
    			}
      			bytes->dim = 2 * (bytes->usage);
      			for(int i = 0; i < DEFAULT_SIZE; i++)
    			{
      				bytes->data[i] = bytes->dflt[i];
    			}
    		}
      		else
    		{
      			bytes->data = realloc(bytes->data, 2 * (bytes->usage + len)* sizeof(uint8_t));
      			bytes->dim = 2 * (bytes->usage);
    		}       
    	}
  	else if(index > bytes->usage)
    	{
      		return false;
    	}
	uint8_t* data = bytes_data(bytes);
  	int n = index;
      	for (int i = bytes->usage - 1; i >= n; i--)
        {
        	data[i+len] = data[i];
        }
      	for(int i = 0; i < len; i++)
        {
      		data[index + i] = buf[i];
        }
      	bytes->usage = len + bytes->usage;
  	return true;
}



//
bool bytes_erase(bytes_t * const bytes, size_t index, size_t len)
{
	if(index < bytes->usage && bytes->usage != 0)
    	{
      		if (index + len <= bytes->usage)
    		{
      			for(int j = 0; j < len; j++)
    			{
      				for(int k = index; k < bytes->usage; k++)
    				{
      					bytes->data[k] = bytes->data[k + 1];
    				}
    			}
			bytes->usage = bytes->usage - len;
    		}
      		else
    		{
       			for(int j = 0; j < bytes->usage - index; j++)
    			{
      				for(int k = index; k < bytes->usage; k++)
    				{
      					bytes->data[k] = bytes->data[k + 1];
    				}
    			}
			int sub = bytes->usage - index;
			bytes->usage = bytes->usage - sub;
    		}
      		return true;
    	}
  	else if(index < DEFAULT_SIZE)
    	{
      		if (index + len <= DEFAULT_SIZE)
    		{
      			for(int j = 0; j < len; j++)
    			{
      				for(int k = index; k < DEFAULT_SIZE; k++)
    				{
      					bytes->dflt[k] = bytes->dflt[k + 1];
    				}
    			}
    		}
     		else
    		{
       			for(int j = 0; j < len - DEFAULT_SIZE; j++)
    			{
      				for(int k = index; k < DEFAULT_SIZE; k++)
    				{
      					bytes->dflt[k] = bytes->dflt[k + 1];
    				}
    			}
    		}
      		return true;
    	}
    	return false;
}


//
uint8_t * bytes_range(const bytes_t * const bytes, range_t *range)
{
	if(range->start >= range->stop && range->step > 0)
    	{
      		return NULL;
    	}
  	else if(range->start <= range->stop && range->step < 0)
  	{
      		return NULL;
    	}
  	else
    	{
      		if(bytes->usage == 0)
    		{
      			uint8_t ja = range->start;
      			range->start = range->start + range->step;
      			return &bytes->dflt[ja];
    		}
      		else
    		{
      			uint8_t* ja = &bytes->data[range->start];
      			range->start = range->start + range->step;
      			return ja;
    		}
    	}
}


//
//
//
//
bool bytes_copy(bytes_t * const dest, const bytes_t * const src)
{
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

//







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
