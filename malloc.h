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


/**
 * struct m_chunk_hdr_s - header for each chunk
 * @size: size of chunk
 * @inuse: size of in use mem
 * @next: pointer to the next chunk
 */

typedef struct m_chunk_hdr_s
{
	size_t size;
	size_t inuse;
	struct m_chunk_hdr_s *next;
} m_chunk_hdr_t;

/***** SHARED VARIABLES *****/

extern m_chunk_hdr_t *free_list;

/***** PROTOTYPES *****/

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);
void *allocate_large_block(size_t size);
m_chunk_hdr_t *extend_heap(void);

#endif /* MALLOC_H */
