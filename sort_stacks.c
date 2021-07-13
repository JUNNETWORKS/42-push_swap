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
int	quick_sort_stack(t_dlist *dummy_a, t_dlist *dummy_b, int *arr, int len)
{
	int	sorted_count;
	int	pivot;

	printf("quick_sort_stack(), len: %d\n", len);
	print_stacks(dummy_a, dummy_b);
	// stackBがソート済みならスタックAの底へ移動させる
	if (dlist_len(dummy_b) <= 3)
		sort_le_3_elements(dummy_b);
	if (dlist_len(dummy_b)
		&& (is_stack_sorted_asc(dummy_b, -1) || is_stack_sorted_des(dummy_b, -1)))
		return (merge_sorted_b2a(dummy_a, dummy_b));
	// arr[len/2] より小さいのをstackBに移動
	// pivot = arr[len / 2];
	pivot = dummy_a->prev->val;
	printf("pivot: %d\n", pivot);
	partition_stacks(dummy_a, dummy_b, pivot, len, false);
	// ソート状態になるまでスタックBを半分にしていく
	sorted_count = 0;
	while (!(is_stack_sorted_asc(dummy_b, -1) || is_stack_sorted_des(dummy_b, -1)))
	{
		dlist_at(dummy_b, dlist_get_min_val_idx(dummy_b), &pivot);
		printf("pivot: %d\n", pivot); partition_stacks(dummy_b, dummy_a, pivot, dlist_len(dummy_b), true);
		if (dlist_len(dummy_b) <= 3)
			sort_le_3_elements(dummy_b);
		print_stacks(dummy_a, dummy_b);
		sleep(1);
	}
	printf("start merge!\n");
	sorted_count = merge_sorted_b2a(dummy_a, dummy_b);
	// stackBがソートされた状態になるまでAに要素を移動
	sorted_count += quick_sort_stack(dummy_b, dummy_a, arr, dlist_len(dummy_a) - sorted_count);
	return (sorted_count);
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
