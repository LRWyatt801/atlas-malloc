#ifndef MALLOC_H
#define MALLOC_H

/***** LIBRARIES *****/

#include <stdio.h>

/***** STRUCTS/TYPEDEFS *****/

/**
 * struct nm_chunk_hdr_s - header for each chunk
 * @size: size of chunk
 */

typedef struct nm_chunk_hdr_s
{
	size_t size;
} nm_chunk_hdr_t;

/***** PROTOTYPES *****/

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void *_free(void *ptr);

#endif /* MALLOC_H */
