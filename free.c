#include "malloc.h"

#define NHDR_SIZE (sizeof(m_chunk_hdr_t))

/**
 * _free - frees a memory space
 * @ptr: pointer to the memory space to be freed
 *
 * Return: None
 */
void _free(void *ptr)
{
	if (ptr == NULL)
	{
		return; /* Nothing to free */
	}

	m_chunk_hdr_t *chunk = (m_chunk_hdr_t *)((char *)ptr - NHDR_SIZE);

	/* Add the freed chunk to the front of the free list */
	chunk->next = free_list;
	free_list = chunk;
}
