#ifndef REVERSE_H
#define REVERSE_H

#include <stdint.h>

/**
 * Forms an integer by reversing the order each digit in value.
 *
 * Examples:
 *     reverse(1) = 1
 *     reverse(12) = 21
 *     reverse(123) = 321
 *     reverse(1234) = 4321
 *     reserve(12345) = 54321
 *
 * Pre:      value has been initialized. You may assume the reversed number
 *           will not have leading zeros.
 * 
 * Returns:  the integer formed by reversing each digit in value
 *
 * Restrictions:
 *	You may use any integer operations supported in C.  You may also
 *	use any selection (if, if..else, etc) or iteration (for, while)
 *	constructs.
 *
 *	You may not use an array or string, nor may you perform 
 *	any I/O operations. Similarly you may not use math.h and string.h.
 *
 */ 
uint64_t reverse(uint64_t value);

#endif
