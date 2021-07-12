#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_many_elements(t_dlist *dummy_a, t_dlist *dummy_b)
{
	int	*arr;
	(void)dummy_b;

	// pivotを求めるために事前にソートした結果の配列を求めておく
	arr = dlist2arr(dummy_a);
	if (!arr)
		exit(1);
	sort_arr(arr, dlist_len(dummy_a));
	for (int i = 0; i < dlist_len(dummy_a); i++)
		printf("arr[%d]: %d\n", i, arr[i]);
	return ;
}

void	sort_stacks(t_dlist *dummy_a, t_dlist *dummy_b)
{
	if (dlist_len(dummy_a) <= 3)
		sort_le_3_elements(dummy_a);
	else if (dlist_len(dummy_a) <= 6)
		sort_le_6_elements(dummy_a, dummy_b);
	else
		sort_many_elements(dummy_a, dummy_b);
}
