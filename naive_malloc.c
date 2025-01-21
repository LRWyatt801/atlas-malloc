#include "malloc.h"
#include <stddef.h>
#include <unistd.h>

/**
* naive_malloc - allocates memory
* @size: size of memory to be allocated
*
* Return: n/a
**/

void *naive_malloc(size_t size)
{
	void *prev_ptr;

	prev_ptr = sbrk(size);

	return (prev_ptr);
}
