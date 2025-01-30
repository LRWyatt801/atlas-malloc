#include "malloc.h"
#include <stddef.h>
#include <unistd.h>

#define HDRSIZE 16
#define PAGE_SIZE 4096
#define CAPOFFSET(mem_size) (HDRSIZE + mem_size)
#define ALIGNSIZE(size) (((size + 7) >> 3) << 3)
#define NHDR_SIZE (sizeof(m_chunk_hdr_t))

static void *heap_end = NULL;
m_chunk_hdr_t *free_list = NULL; /* list of free chunks */

/**
 * _malloc - allocates memory
 * @size: size of memory to be allocated
 *
 * Return: pointer to the allocated memory or NULL if allocation fails
 */
void *_malloc(size_t size)
{
    size = ALIGNSIZE(size);

    /* Handle large allocations separately */
    if (size > PAGE_SIZE - NHDR_SIZE)
    {
        return (allocate_large_block(size));
    }

    m_chunk_hdr_t *current = free_list;
    m_chunk_hdr_t *prev = NULL;

    /* Search for a suitable free chunk */
    while (current != NULL && current->size < size)
    {
        prev = current;
        current = current->next;
    }

    /* If no suitable chunk found, extend the heap */
    if (current == NULL)
    {
        current = extend_heap();
        if (current == NULL)
        {
            return (NULL); /* Allocation failed */
        }
    }

    void *result = (void *)((char *)current + NHDR_SIZE);
    size_t remaining_size = current->size - size;

    /* Split the chunk if there's enough remaining space */
    if (remaining_size > HDRSIZE)
    {
        m_chunk_hdr_t *new_chunk = (m_chunk_hdr_t *)((char *)current + NHDR_SIZE + size);
        new_chunk->size = remaining_size;
        new_chunk->next = current->next;
        if (prev != NULL)
        {
            prev->next = new_chunk;
        }
        else
        {
            free_list = new_chunk;
        }
    }
    else
    {
        /* Remove the entire chunk from the free list */
        if (prev != NULL)
        {
            prev->next = current->next;
        }
        else
        {
            free_list = current->next;
        }
    }

    return (result);
}

/**
 * allocate_large_block - allocates a large block of memory
 * @size: size of memory to be allocated
 *
 * Return: pointer to the allocated memory or NULL if allocation fails
 */
void *allocate_large_block(size_t size)
{
    m_chunk_hdr_t *chunk = extend_heap();

    if (chunk == NULL)
    {
        return (NULL); /* Heap extension failed */
    }

    chunk->size = size;
    return ((void *)((char *)chunk + NHDR_SIZE));
}

/**
 * extend_heap - extends the heap by one page
 *
 * Return: pointer to the new chunk or NULL if extension fails
 */
m_chunk_hdr_t *extend_heap(void)
{
    void *new_end = sbrk(PAGE_SIZE);

    if (new_end == (void *)-1)
    {
        return (NULL); /* Heap extension failed */
    }

    m_chunk_hdr_t *chunk = (m_chunk_hdr_t *)heap_end;
    chunk->size = PAGE_SIZE - NHDR_SIZE;
    chunk->next = free_list;
    free_list = chunk;
    heap_end = (char *)heap_end + PAGE_SIZE;

    return (chunk);
}
