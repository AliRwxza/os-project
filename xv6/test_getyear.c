#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
	int alloc_val = 10240 * sizeof(int);
	// int *temp = 
	if(malloc(alloc_val))
		printf(1, "%d Kilobytes where allocated.\n", alloc_val);
	exit();
}
