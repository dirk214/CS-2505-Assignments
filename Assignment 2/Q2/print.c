#include "print.h"
#include "char_out.h"

static uint64_t find(uint64_t num);

uint8_t print_with_commas(FILE *out, uint64_t value)
{
	uint64_t count = 0;
	uint64_t copy = value;
	
	while (copy != 0)
    	{
      		copy = copy / 10;
		count++;
    	}
  	
	if (value == 0)
	{
    		count = 1;
	}

	uint64_t cc = count;
  	if (cc <= 3)
    	{
      		if (value / 100 != 0)
        	{
        		char one = value/100;
        		char_out(out, one + '0');
        	}
      		if (value / 10 != 0)
        	{
        		char two = (value / 10) % 10;
        		char_out(out, two + '0');
        	}
        	char three = value % 10;
      		char_out(out, three + '0');
    	}
  	else if (cc >= 4)
    	{
      		if (cc % 3 == 1)
    		{
      			uint64_t t = find(cc - 1);
      			char one = value / t;
      			char_out(out, one + '0');
      			char_out(out, ',');
      			count++;
     			value = value % t;
      			cc--;
    		}
      		else if (cc % 3 == 2)
 		{
      			uint64_t t = find (cc - 2);
      			char one = value / t / 10;
      			char_out(out, one + '0');
      			char two = value / t % 10;
      			char_out(out, two +'0');
      			char_out(out, ',');
      			count++;
      			value = value % t;
      			cc = cc - 2;
       
    		}
      		while (cc / 3 != 1)
    		{
       			uint64_t t = find(cc - 3);
       			char one = ( value / t ) / 100;
       			char two = value / t / 10 % 10;
       			char three = value / t % 10;
       			char_out(out, one + '0');
      			char_out(out, two  + '0');
      			char_out(out, three +'0');
      			char_out(out, ',');
      			count++;
      			cc = cc - 3;
      			value = value % t;
    		}
      		char one = value / 100;
      		char two = value / 10 % 10;
      		char three = value % 10;
      		char_out(out, one + '0');
      		char_out(out, two +'0');
      		char_out(out, three + '0');
    	}
 
  	return count;
}

	uint64_t find(uint64_t num)
	{
  		uint64_t x;
  		uint64_t pos = 1;
  		for (x = 0; x < num; x++)
    		{
      			pos = pos * 10;
    		}
  		return pos;
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
