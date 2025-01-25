#include "malloc.h"
#include <stddef.h>
#include <unistd.h>

#define HDRSIZE 16
#define CAPOFFSET(mem_size) (HDRSIZE + mem_size)
#define ALIGNSIZE(size) (((size + 7) >> 3) << 3)
#define NHDR_SIZE (sizeof(chunk_hdr_t))

/**
 * chunk_hdr_t - header for each chunk
 * @size: size of chunk
 * @data_ptr: pointer to data
 */

typedef struct chunk_hdr_s
{
	size_t size;
} chunk_hdr_t;

/**
* naive_malloc - allocates memory
* @size: size of memory to be allocated
*
* Return: n/a
**/

void *naive_malloc(size_t size)
{
	static void *page_strt;
	static void *nxt_chunk;

	if (!page_strt)
	{
		page_strt = sbrk(4096);
		nxt_chunk = page_strt;
	}
	
	void *new_chunk;
	chunk_hdr_t *new_chunk_hdr;

	new_chunk_hdr = (chunk_hdr_t *)new_chunk;
	size = ALIGNSIZE(size);

	new_chunk_hdr->size = size;

	nxt_chunk = (char *)new_chunk + NHDR_SIZE + size;

	return ((void *)((char *)new_chunk + NHDR_SIZE));
}
