#include "malloc.h"

#define MHDR_SIZE (sizeof(m_chunk_hdr_t))

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

	m_chunk_hdr_t *chunk = (m_chunk_hdr_t *)((char *)ptr - MHDR_SIZE);

}
