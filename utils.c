#include "utils.h"

long	mod(long a, long b)
{
	return ((a % b + b) % b);
}
