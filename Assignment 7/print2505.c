#include <stdio.h>
#include <stdint.h>

#include "char_out.h"
#include "print2505.h"

//
//
//
//
int print2505(FILE *out, const char *format, const uint8_t *data)
{
	int char_count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format ==  '%')
			{
				char_out(out, *format);
				format++;
				char_count++;
			}
			else if (*(format + 1) == 'l')
			{
				int n = *format % 48;
				if (n == 1 || n == 2 || n == 4 || n == 8)
				{
					char_out(out, '0');
					char_out(out, 'x');
					for (int i = 1; i <= n; i++)
					{
						int dif = n - i;						
						uint8_t temps = *((uint8_t*) data + dif);
						uint8_t cc = ((temps & 0xf0) >> 4);
						uint8_t dd = (temps & ~0xf0);
						char c = '0';
						char d = '0';
						if (cc >= 10)
						{
							if (cc == 10)
							{
								c = 'a';
							}
							else if (cc == 11)
							{
								c = 'b';
							}
							else if (cc == 12)
							{
								c = 'c';
							}
							else if (cc == 13)
							{
							c = 'd';
							}
							else if (cc == 14)
							{
								c = 'e';
							}
							else if (cc == 15)
							{
								c = 'f';
							}
						}
						else
						{
							c = cc + '0';
						}
						if (dd >= 10)
						{
							if (dd == 10)
							{
								d = 'a';
							}
							else if (dd == 11)
							{
								d = 'b';
							}
							else if (dd == 12)
							{
								d = 'c';
							}
							else if (dd == 13)
							{
								d = 'd';
							}
							else if (dd == 14)
							{
								d = 'e';
							}
							else if (dd == 15)
							{
								d = 'f';
							}
						}
						else
						{
							d = dd + '0';
						}
						if (i == 1)
						{
							if (cc == 0)
							{
								char_out(out, d);
								char_count++;
							}
							else
							{
								char_out(out, c);
								char_out(out, d);
								char_count+=2;
							}
						}
						else
						{
							char_out(out, c);
							char_out(out, d);
							char_count+=2;
						}

					}
					format += 2;
					data += n;
					char_count+=2;
				}
				else
				{
					return -1;
				}
			}
			else if (*(format + 1) == 'b')
			{
				int n = *format % 48;
				if (n == 1 || n == 2 || n == 4 || n == 8)
				{
					char_out(out, '0');
					char_out(out, 'x');
					for (int i = 1; i <= n; i++)
					{
						uint8_t temps = *((uint8_t*) data);
						uint8_t cc = ((temps & 0xf0) >> 4);
						uint8_t dd = (temps & ~0xf0);
						char c = '0';
						char d = '0';
						if (cc >= 10)
						{
							if (cc == 10)
							{
								c = 'a';
							}
							else if (cc == 11)
							{
								c = 'b';
							}
							else if (cc == 12)
							{
								c = 'c';
							}
							else if (cc == 13)
							{
								c = 'd';
							}
							else if (cc == 14)
							{
								c = 'e';
							}
							else if (cc == 15)
							{
								c = 'f';
							}
						}
						else
						{
							c = cc + '0';
						}
						if (dd >= 10)
						{
							if (dd == 10)
							{
								d = 'a';
							}
							else if (dd == 11)
							{
								d = 'b';
							}
							else if (dd == 12)
							{
								d = 'c';
							}
							else if (dd == 13)
							{
								d = 'd';
							}
							else if (dd == 14)
							{
								d = 'e';
							}
							else if (dd == 15)
							{
								d = 'f';
							}
						}
						else
						{
							d = dd + '0';
						}
						if (i == 1)
						{
							if (temps == 0)
							{
								
							}
							else if (cc == 0)
							{
								char_out(out, d);
								char_count++;
							}
							else
							{
								char_out(out, c);
								char_out(out, d);
								char_count+=2;
							}
						}
						else
						{
							char_out(out, c);
							char_out(out, d);
							char_count+=2;
						}
						
						++data;
					}
				format += 2;
				char_count+=2;
				}
				else
				{
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
		else
		{
			char_out(out, *format);
			char_count++;
			format++;
		}
	}

	return char_count;
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
