#include "malloc.h"
#include <stddef.h>
#include <unistd.h>

#define HDRSIZE 16
#define CAPOFFSET(mem_size) (HDRSIZE + mem_size)
#define ALIGNSIZE(size) (((size + 7) >> 3) << 3)
#define NHDR_SIZE (sizeof(nm_chunk_hdr_t))

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
	nm_chunk_hdr_t *new_chunk_hdr;

	/* Set new_chunk == to end of allocated mem */
	new_chunk = nxt_chunk;

	new_chunk_hdr = (nm_chunk_hdr_t *)new_chunk;
	size = ALIGNSIZE(size);

	new_chunk_hdr->size = size;

	/* update nxt_chunk to end of allocated mem */
	nxt_chunk = (char *)new_chunk + NHDR_SIZE + size;

	return ((void *)((char *)new_chunk + NHDR_SIZE));
}

