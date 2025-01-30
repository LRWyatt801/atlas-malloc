#include "malloc.h"
#include <stddef.h>
#include <unistd.h>

#define HDRSIZE 16
#define STD_PGSIZE 4096
#define CAPOFFSET(mem_size) (HDRSIZE + mem_size)
#define ALIGNSIZE(size) (((size + 7) >> 3) << 3)
#define MHDR_SIZE (sizeof(m_chunk_hdr_t))
#define PAGE_SIZE(size) ((size < STD_PGSIZE - MHDR_SIZE) ? STD_PGSIZE : (ALIGNSIZE(size) + MHDR_SIZE))
#define REMAINING_PAGE(heap_end, page_end) ((char *)page_end - (char *)heap_end)

/**
* naive_malloc - allocates memory
* @size: size of memory to be allocated
*
* Return: n/a
**/

void *_malloc(size_t size)
{
	static void *page_strt;
	static void *page_end;
	static void *heap_end;

	if (!page_strt)
	{
		page_strt = sbrk(PAGE_SIZE(size));
		heap_end = page_strt;
		page_end = sbrk(0);
	}
	size = ALIGNSIZE(size);
	if (size > (REMAINING_PAGE(heap_end, page_end) + MHDR_SIZE))
	{
		page_strt = sbrk(PAGE_SIZE(size));
		heap_end = page_strt;
		page_end = sbrk(0);
	}

	m_chunk_hdr_t *new_chunk_hdr = page_strt;

	if (new_chunk_hdr->next != NULL)
		new_chunk_hdr = new_chunk_hdr->next;

	new_chunk_hdr = (m_chunk_hdr_t *)new_chunk_hdr;
	new_chunk_hdr->size = size;

	return ((void *)((char *)new_chunk_hdr + MHDR_SIZE));
}

