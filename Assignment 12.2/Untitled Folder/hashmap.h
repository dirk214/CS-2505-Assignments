#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bytes.h"


// The structure representing our hashmap type.
struct hashmap_t 
{
	// The members that make our hashmap generic: 

	// The hash function, provided by the user. 
	// This takes a key/value pair, and uses the key to create
	// a size_t, which is then used to determine the index (or bucket) 
	// where the key/value pair will live in the hashmap.
	size_t (*hash)(const uint8_t * const);	

	// The comparison function, compares 2 keys, provided by the user. 
	// If the function returns 0, the keys are identical, otherwise
	// the keys differ.
	int (*cmp)(const uint8_t * const, const uint8_t * const);

	// The print function, prints a single key/value pair, 
	// provided by the user. 
	void (*print)(FILE *, const uint8_t * const);

	// The size, in bytes, of the key/value pair, provided by the user.
	size_t pair_size;

	// The members that make up the actual hashmap:

	// The hash table, an array of bytes_t variables.
	// Each bytes_t holds zero or more key value pairs and 
	// is called a "bucket".  
	bytes_t * table;

	// The number of buckets in table (the array length). 
	size_t buckets;

	// The number of key/value pairs in the hash map. 
	size_t size;

	// The biggest the load factor can be before resizing the table.
	// The load factor is size / buckets, and when the load factor 
	// is >= to the max_load_factor the table should be resized and 
	// its elements rehashed and stored.
	double max_load_factor;
};

typedef struct hashmap_t hashmap_t;
 

// Instructor provided functions:

// Initializes a hashmap_t variable.
// 
// Pre:
// 	hm - Points to a valid hashmap_t variable and is not NULL.
// 
// Post:
//	hm->cmp - Is set to cmp. 
//	hm->hash - Is set to hash. 
//	hm->print - Is set to print.
//
//	hm->table - Points to a buckets sized array representing the table.
//
//	hm->pair_size - Is initialized to pair_size.
//	hm->buckets - Is initialized to buckets.
//
//	hm->size - Is initialized to 0.
//	hm->max_load_factor - Is initialized to 0.75.
//
// Returns:
//	Returns true if the table is properly allocated, false otherwise.
//
bool hashmap_init(hashmap_t * const hm, 
		size_t (*hash) (const uint8_t * const),
                int (*cmp) (const uint8_t * const, const uint8_t * const),
		void (*print)(FILE *, const uint8_t * const),
                size_t pair_size, size_t buckets);


// Every function from this point on assumes *hm has been initialized
// using hashmap_init().

// Deallocates any dynamic memory allocated for *hm.
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Post:
// 	Frees any dynamically allocated memory for the hashmap. This 
//	includes each bucket and the table itself.
//
void hashmap_free(hashmap_t * hm);


// Prints out a hashmap_t in human readable form.
//
// Pre:
// 	out - Points to an already opened file stream.
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Post:
//	A formatted table is printed.
//  
void hashmap_fprintf(FILE * out, const hashmap_t * const hm);


// Status functions, these are one-liners:

// Is *hm empty?
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Returns:
//	Returns true if hm->size is 0, false otherwise.
//
bool hashmap_empty(const hashmap_t * const hm);


// Accessor function, gets the size of the hashmap_t, hm->size.
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Returns:
//	Returns hm->size.
//
size_t hashmap_size(const hashmap_t * const hm);


// Accessor function, gets the number of buckets in the hashmp, hm->buckets.
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Returns:
//	Returns hm->buckets.
//
size_t hashmap_buckets(const hashmap_t * const hm);


// Accessor function, computes the current load factor of the hashmap, *hm. 
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Returns:
//	Returns hm->size / hm->buckets.
//
double hashmap_get_curr_load_factor(const hashmap_t * const hm);


// Accessor function, gets the max load factor of the hashmap, *hm.
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Returns:
//	Returns hm->max_load_factor.
//
double hashmap_get_max_load_factor(const hashmap_t * const hm);


// Functions that manipulate the hashmap:


// Sets the max load factor of the hashmap, *hm, rehashing the table
// if necessary.
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Post:
//	If the current load factor is >= the new max load factor,
//	you'll need to resize and rehash the table. To determine the 
//	number of buckets (the table length) in the newly resized table:
//
//	buckets = 2 * buckets + 1, until size / buckets < new max load factor
//
// Returns:
//	Returns true if the table is not resized, or when it is resized and 
//	dynamic allocation succeeds, false if allocation fails.
//
//	If allocation fails, the table, the number of buckets, 
//	and the max load factor should not be updated.
//
bool hashmap_set_max_load_factor(hashmap_t * const hm, const double new_max);


// Gets a key/value pair from the hashmap.
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//	pair - Points to a key/value pair, which contains a valid key.
//
// Post:
//	If the key/value pair is found in the hashmap, copy the contents
//	of the key/value pair into parameter pair, overwriting its contents.
// 
// Returns:
// 	Returns true if the key is found in the map, false otherwise.
//
bool hashmap_get(const hashmap_t * const hm, uint8_t * const pair);


// Inserts a key/value pair into the hashmap. 
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Post:
// 	If the key/value pair is already in the hashmap, the value should be 
//	updated (overwrite the key and value with pair) but the size should
//	not change. Otherwise, the key/value pair should be added to the
//	hashmap in the correct bucket and the size incremented. 
//
// 	If inserting the element increases the load factor beyond (>=)
// 	max_load_factor, the table should be rehashed.  
//
//	To determine the number of buckets (the table length) in the 
//	newly resized table:
//
//	buckets = 2 * buckets + 1, until size / buckets < max_load_factor
//
// Returns:
//  	Returns true if the key/value pair is successfully updated or inserted 
//	into the hashmap, false otherwise.
//
bool hashmap_put(hashmap_t * const hm,  const uint8_t * const pair);


// Resizes the hash table. 
//
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//
// Post:
// 	Resizing involves creating a new table of length new_buckets, then 
//	rehashing all of the elements of the current table and inserting 
//	them into the new table. Finally, the old table is deallocated, and 
//	the new table becomes hm->table.
//
// Returns:
//	Returns true if resizing the table and inserting the elements  
//	succeeds, false otherwise (if an allocation fails).
//
//	If allocation fails, the table and the number of buckets 
//	should not be updated.
// 
bool hashmap_rehash(hashmap_t * const hm, const size_t new_buckets);


// Erases a key/value pair from the hashmap. 
// 
// Pre:
//	hm - Points to a valid hashmap_t variable and is not NULL.
//	pair - Points to a key/value pair, which contains a valid key.
//
// Post:
//	If the key/value pair is found in the hashmap, it is removed and the 
//	size is decreased. If the key/value pair isn't in the hashmap, 
//	the hashmap should remain unchanged.
//
// Returns:
// 	Returns true if the element is found and erased, false otherwise.   
//
bool hashmap_erase(hashmap_t * const hm, const uint8_t * const pair);


#endif
