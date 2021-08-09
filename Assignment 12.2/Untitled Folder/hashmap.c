#include <string.h>
#include "hashmap.h"


//
//
//
//
bool hashmap_init(hashmap_t * const hm,
		size_t (*hash) (const uint8_t * const),
		int (*cmp) (const uint8_t * const, const uint8_t * const),
		void (*print)(FILE *, const uint8_t * const),
		size_t pair_size, size_t buckets)
{
	bool success = false;

	// Copy all of the function pointers 
	hm->hash = hash;
	hm->cmp = cmp;
	hm->print = print;

	// pair_size is the number of bytes in the key/value pair.
	hm->pair_size = pair_size;
	// The dimension of the table is buckets. 
	hm->buckets = buckets;

	// Table starts out empty, and max load factor is set to .75.
	hm->size = 0;
	hm->max_load_factor = .75;

	// Allocate space for the table. This is an array of bytes_t
	// variables, so each index, table[0], table[1], etc. is a bytes_t
	// structure, not bytes_t *. See the syntax for bytes_init() below.
	hm->table = malloc(hm->buckets * sizeof(bytes_t));

	if (hm->table != NULL)
	{
		// Initialize each bucket, a bytes_t in the array.
		for (size_t b = 0; b < hm->buckets; b++)
		{
			bytes_init(&hm->table[b]);
		}
		success = true;
	}

	return success;
}


//
//
//
//
void hashmap_free(hashmap_t * hm)
{
	// Free each bytes_t or bucket in the table.
	for (size_t b = 0; b < hm->buckets; b++)
	{
		bytes_free(&hm->table[b]);
	}

	// Deallocate the table itself.
	free(hm->table);
}


//
//
//
//
void hashmap_fprintf(FILE * out, const hashmap_t * const hm)
{
	for (size_t b = 0; b < hm->buckets; b++)
	{
		uint8_t *next = NULL;
		range_t pairs = {0, bytes_usage(&hm->table[b]), hm->pair_size};

		fprintf(out, "table[%zu]: \n", b);

		// We can use bytes_range() to iterate through each bucket.
		while ((next = bytes_range(&hm->table[b], &pairs)) != NULL)
		{
			// Use the provided print function:
			fprintf(out, "\t");
			hm->print(out, next);
			fprintf(out, "\n");
		} 
	}
}


//
//
//
//
size_t hashmap_size(const hashmap_t * const hm)
{
	return hm->size;
}


//
//
//
//
bool hashmap_empty(const hashmap_t * const hm)
{
	return (hm->size == 0);
}


//
//
//
//
size_t hashmap_buckets(const hashmap_t * const hm)
{
	return hm->buckets;
}


//
//
//
//
double hashmap_get_curr_load_factor(const hashmap_t * const hm)
{
	return hm->size / hm->buckets;
}


//
//
//
//
double hashmap_get_max_load_factor(const hashmap_t * const hm)
{
	return hm->max_load_factor;
}


//
//
//
//
bool hashmap_set_max_load_factor(hashmap_t * const hm, const double new_max)
{
	if (hashmap_get_curr_load_factor(hm) >= new_max)
	{
		while ((hm->size / hm->buckets) < new_max)
		{
			hm->buckets = 2 * hm->buckets + 1;
		}
	}
	return true;
}


//
//
//
//
bool hashmap_get(const hashmap_t * const hm, uint8_t * const pair)
{
	size_t h = hm->hash((uint8_t *)&pair);
	size_t b = h % hm->buckets;
	if (hm->table[b].data != 0)
	{
		*pair = *hm->table[b].data;
		return true;
	}
	else
	{
		return false;
	}
}


//
//
//
//
bool hashmap_put(hashmap_t * const hm, const uint8_t * const pair)
{
	size_t h = hm->hash((uint8_t *)&pair);
	size_t b = h % hm->buckets;
	if (hm->table[b].data != 0)
	{
		*hm->table[b].data = *pair; 
		return true;
	}
	else
	{
		if (hashmap_get_curr_load_factor(hm) + 1 >= hashmap_get_max_load_factor(hm))
		{
			do
			{
				hm->buckets = 2 * hm->buckets + 1;
			}
			while(hm->size / hm->buckets);
		}
		*hm->table[b].data = *pair;
		return true;
	}
}


//
//
//
//
bool hashmap_rehash(hashmap_t * const hm, const size_t new_buckets)
{
	return false;	
}


//
//
//
//
bool hashmap_erase(hashmap_t * const hm, const uint8_t * const pair)
{
	return false;
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
