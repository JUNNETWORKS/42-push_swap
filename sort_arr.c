#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(int *arr, int p, int r)
{
	int	x;
	int	i;
	int	j;

	x = arr[r];
	i = p - 1;
	j = p;
	while (j <= r)
	{
		if (arr[j] <= x)
		{
			i++;
			swap(arr + i, arr + j);
		}
		j++;
	}
	return (i);
}

static void	quick_sort(int *arr, int p, int r)
{
	int	q;

	if (p < r)
	{
		q = partition(arr, p, r);
		quick_sort(arr, p, q - 1);
		quick_sort(arr, q + 1, r);
	}
}

void	sort_arr(int *arr, int n)
{
	quick_sort(arr, 0, n - 1);
}

