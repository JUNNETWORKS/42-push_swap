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

	i = 0;
	adding_count = 0;
	current = dummy_a->next;
	while (i < len)
	{
		next = current->next;
		if ((!push2b_if_lt && current->val <= pivot)
			|| (push2b_if_lt && current->val > pivot))
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

bool	is_stack_sorted_asc(t_dlist *dummy, int len)
{
	t_dlist *current;
	int max;
	int i;

	current = dummy->next;
	max = current->val;
	i = 0;
	if (len < 0)
		len = dlist_len(dummy);
	while (i < len)
	{
		if (current->val < max)
			return (false);
		max = current->val;
		current = current->next;
		i++;
	}
	return (true);
}

bool	is_stack_sorted_des(t_dlist *dummy, int len)
{
	t_dlist *current;
	int min;
	int i;

	current = dummy->next;
	min = current->val;
	i = 0;
	if (len < 0)
		len = dlist_len(dummy);
	while (i < len)
	{
		if (current->val > min)
			return (false);
		min = current->val;
		current = current->next;
		i++;
	}
	return (true);
}


/*
 * dummy_a: dummy node of stack A
 * dummy_b: dummy node of stack B
 * arr: sorted array for determining pivot.
 * len: the number of unsorted elements.
 *
 * return: the number of elements has been sorted in this call.
 */
int	quick_sort_stack(t_dlist *dummy_a, t_dlist *dummy_b, int *arr, int len)
{
	int sorted_count;

	printf("quick_sort_stack(), len: %d\n", len);
	print_stacks(dummy_a, dummy_b);
	// stackBがソート済みならスタックAの底へ移動させる
	if (dlist_len(dummy_b) <= 3)
		sort_le_3_elements(dummy_b);
	if (dlist_len(dummy_b)
		&& (is_stack_sorted_asc(dummy_b, -1) || is_stack_sorted_des(dummy_b, -1)))
	{
		int i;
		int b_len;
		bool is_sorted_des;

		is_sorted_des = is_stack_sorted_des(dummy_b, -1);
		b_len = dlist_len(dummy_b);
		while (dlist_len(dummy_b))
		{
			if (is_sorted_des)
				dlist_rrotate(dummy_b);
			push_a(dummy_a, dummy_b);
		}
		i = 0;
		while (i++ < b_len)
			dlist_rotate(dummy_a);
		return (b_len);
	}
	// arr[len/2] より小さいのをstackBに移動
	partition_stacks(dummy_a, dummy_b, arr[len / 2], len, false);
	// stackBがソートされた状態になるまでAに要素を移動
	sorted_count = quick_sort_stack(dummy_b, dummy_a, arr, dlist_len(dummy_b));
	quick_sort_stack(dummy_a, dummy_b, arr, dlist_len(dummy_a) - sorted_count);
	return (0);  // TODO: return the number of elements which has been sorted in this call.
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
