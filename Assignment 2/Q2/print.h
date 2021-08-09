#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdint.h>

/* Prints the integer, value with commas to the file stream out and returns
 * the number of characters printed. 
 *
 * The result (e.g. 12,345) must printed character by character using the 
 * provided char_out() function. So when value = 12345, you'll print
 * '1', '2', ',', '3', '4', and '5', one by one. 
 *
 * To convert a digit (int) between 0 – 9 to a character simply add '0', 
 * e.g. 9 + '0' results in '9'. We'll discuss conversions like this in class.
 *
 * Example usage:
 *
 * print_with_commas(stdout, 1)     prints 1 to the screen and returns 1
 * print_with_commas(stdout, 123)   prints 123 to the screen and returns 3
 * print_with_commas(stdout, 1234)  prints 1,234 to the screen and returns 5
 * print_with_commas(stdout, 12345) prints 12,345 to the screen and returns 6
 *
 * Pre:
 *	out    - Points to an already opened file stream.
 *	value  - Has been initialized.
 *
 * Post:
 *	value is printed with commas using the provided char_out() function.
 *	
 * Restrictions:
 *	- You MUST use the provided char_out() function when printing.
 *	- You may NOT use other I/O, e.g. any printf() or scanf() variants.
 *	- You may NOT make any use of character/string variables or arrays.
 *	- You may NOT use math.h or string.h, nor any function declared within.
 *	- You may NOT use any additional libraries.
 *	- You may NOT use recursion.
 */
uint8_t print_with_commas(FILE *out, uint64_t value);

#endif
