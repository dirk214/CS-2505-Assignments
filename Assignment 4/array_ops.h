#ifndef ARRAY_OPS_H
#define ARRAY_OPS_H

#include <stdlib.h>
#include <stdbool.h>

// Every array used with the functions below must be created with
// dimension = ARRAY_MAX_SIZE.
#define ARRAY_MAX_SIZE 256

// Compares the contents of arrays lhs[] and rhs[]. 
// 
// The two arrays are the equal if they both have the same usage and
// have the same values at every index up to that shared usage. 
//
// Pre:
//	lhs[] - Is an array of integers containing lusage elements.
//	rhs[] - Is an array of integers containing rusage elements.
//
// Returns:
//	true - If contents of the arrays are the same. 
//	false - If the contents of the arrays differ.  
//
bool array_cmp(int lhs[], size_t lusage, int rhs[], size_t rusage);

// Appends the contents of array src[] at the end of array dest[]. 
// 
// Pre:
//	dest[] - Is an array of integers containing dusage elements.
//	src[] - Is an array of integers containing susage elements.
//
// Returns:
//	The new usage of dest[] after the append. If the new usage would 
//	be > ARRAY_MAX_SIZE, no append occurs and function returns the 
//	original usage.
//
size_t array_append(int dest[], size_t dusage, int src[], size_t susage);

// Inserts the contents of array src[] into array dest[], starting at 
// the specified index.
//
// Pre:
//	dest[] - Is an array of integers containing dusage elements.
//	src[] - Is an array of integers containing susage elements.
//	index - The location the values will be inserted into array dest[].
//
// Post:
//	The contents of src[] are inserted into dest[], starting at index. 
//	If index > dusage or the resulting usage would be > ARRAY_MAX_SIZE, 
//	no insertion occurs. 
//
// Returns:
//	The new usage of dest[] after the insertion. If index > dusage
//	or the resulting usage would be > ARRAY_MAX_SIZE, no insertion occurs 
//	and the function returns the original usage.
//
// Other thoughts:
//	You are going to insert "before" index. So if you insert at index = 0 
//	you are inserting before the first value. Further, if you were to 
//	insert at index = dusage, it's like appending at the end.
//
size_t array_insert(int dest[], size_t dusage, 
			int src[], size_t susage, size_t index);

// Erases up to count elements from array[] starting at the specified index.
//
// Pre:
//	array[] - Is an array of integers containing usage elements.
//
// Post:
//      If index < usage, then up to count elements have been erased from
//      array[] starting at index. When index + count > usage less than
//      count elements will be erased.
//
// Returns:
//	The updated usage after erasing up to count elements.
//
//      If index >= usage, then no erasure occurs and the function
//      returns the original usage.
//
size_t array_erase(int array[], size_t usage, size_t index, size_t count);

#endif
