#include "malloc.h"
#include <unistd.h>
#include <string.h>

void _write_size(size_t);

void test_malloc() {
    void *ptr, *last_ptr = NULL;
    size_t i;

    for (i = 0; i < 1000; i++) {
        ptr = _malloc(1); // Request 1 byte of memory
	if (last_ptr != NULL)
	{
		if (((char *)ptr - (char *)last_ptr) < 40)
		       write(1, "OOPS!", 5);
	}
        if (ptr == NULL) {
		write(1, "failed", 6);
        } else {
		write(1, "test # ", 7);
		_write_size(i);
		write(1, " success\n", 9);
        }
	last_ptr = ptr;
    }

    printf("Test completed.\n");
}


void _write_size(size_t size)
{
	static char buffer[20];
	snprintf(buffer, sizeof(buffer), "%lu", size);
	write(1, buffer, strlen(buffer));
}

int main() {
    test_malloc();
    return 0;
}

