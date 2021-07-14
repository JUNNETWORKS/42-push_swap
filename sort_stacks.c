#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

int	partition_stacks(t_dlist *dummy_a, t_dlist *dummy_b, int pivot, int len, bool push2b_if_lt)
{
	t_dlist *current;
	t_dlist *next;
	int i;
	int adding_count;
	int len_a;

	i = 0;
	adding_count = 0;
	current = dummy_a->next;
	len_a = dlist_len(dummy_a);
	while (i < len_a)
	{
		next = current->next;
		if (i < len && ((!push2b_if_lt && current->val <= pivot)
				|| (push2b_if_lt && current->val > pivot)))
		{
			push_b(dummy_a, dummy_b);
			adding_count++;
		}
		else
			dlist_rotate(dummy_a);
		current = next;
		i++;
	}
	return (adding_count);
}

/*
 * return: dlist_len(dummy_b)
 */
int merge_sorted_b2a(t_dlist *dummy_a, t_dlist *dummy_b)
{
	int		b_len;
	bool	is_sorted_des;

	is_sorted_des = is_stack_sorted_des(dummy_b, -1);
	b_len = dlist_len(dummy_b);
	while (dlist_len(dummy_b))
	{
		if (is_sorted_des)
			dlist_rrotate(dummy_b);
		push_a(dummy_a, dummy_b);
		dlist_rotate(dummy_a);
	}
	return (b_len);
}

/*
 * dummy_a: dummy node of stack A
 * dummy_b: dummy node of stack B
 * arr: sorted array for determining pivot.
 * len: the number of unsorted elements.
 *
 * return: the number of elements has been sorted in this call.
 */
void	quick_sort_stack(t_dlist *dummy_a, t_dlist *dummy_b, int unsorted_len)
{
	int pivot;
	int sorted_len;

	if (is_stack_sorted_asc(dummy_a, dlist_len(dummy_a)))
		return ;
	// pivotを決めてstackBに移動させる
	pivot = dlist_get_mid_value(dummy_a, unsorted_len);
	printf("pivot (A to B): %d, unsorted_len: %d\n", pivot, unsorted_len);
	partition_stacks(dummy_a, dummy_b, pivot, unsorted_len, false);
	// Bが分割できなくなるまでAに要素を戻す
	while (!(is_stack_sorted_des(dummy_b, dlist_len(dummy_b))
			|| is_stack_sorted_asc(dummy_b, dlist_len(dummy_b))))
	{
		pivot = dlist_get_mid_value(dummy_b, dlist_len(dummy_b));
		printf("pivot (B to A): %d\n", pivot);
		partition_stacks(dummy_b, dummy_a, pivot, dlist_len(dummy_b), true);
		// pivotが上手く動いていない時はpivot-1を試す
		if (dlist_get_mid_value(dummy_b, dlist_len(dummy_b)) == pivot)
			partition_stacks(dummy_b, dummy_a, pivot - 1, dlist_len(dummy_b), true);
		if (dlist_len(dummy_b) <= 3)
			sort_le_3_elements(dummy_b);
		print_stacks(dummy_a, dummy_b);
	}
	printf("finish sorting stack B\n");
	sorted_len = merge_sorted_b2a(dummy_a, dummy_b);
	printf("sorted_len: %d\n", sorted_len);
	print_stacks(dummy_a, dummy_b);
	printf("next quick_sort_stack() will be started in 1 sec...\n");
	sleep(1);
	quick_sort_stack(dummy_a, dummy_b, unsorted_len - sorted_len);
}

void	sort_many_elements(t_dlist *dummy_a, t_dlist *dummy_b)
{
	// int	*arr;
	(void)dummy_b;

	// pivotを求めるために事前にソートした結果の配列を求めておく
	/*
	arr = dlist2arr(dummy_a);
	if (!arr)
		exit(1);
	sort_arr(arr, dlist_len(dummy_a));
	for (int i = 0; i < dlist_len(dummy_a); i++)
		printf("arr[%d]: %d\n", i, arr[i]);
	*/
	quick_sort_stack(dummy_a, dummy_b, dlist_len(dummy_a));
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
