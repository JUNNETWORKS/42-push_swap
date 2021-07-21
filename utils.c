#include <stdlib.h>
#include "utils.h"

long	mod(long a, long b)
{
	return ((a % b + b) % b);
}

void	exit_if_null(int code, void *ptr)
{
	if (!ptr)
		exit(code);
}
