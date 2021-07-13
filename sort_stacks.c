#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	partition_stacks(t_dlist *dummy_a, t_dlist *dummy_b, int pivot, int len)
{
	t_dlist *current;
	t_dlist *next;
	int i;

	i = 0;
	current = dummy_a->next;
	while (i < len)
	{
		next = current->next;
		if (current->val <= pivot)
			push_b(dummy_a, dummy_b);
		else
			dlist_rotate(dummy_a);
		current = next;
		i++;
	}
}

void	quick_sort_stack(t_dlist *dummy_a, t_dlist *dummy_b, int *arr, int unsorted_num)
{
	partition_stacks(dummy_a, dummy_b, arr[unsorted_num / 2], unsorted_num);
}

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
	quick_sort_stack(dummy_a, dummy_b, arr, dlist_len(dummy_a));
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
