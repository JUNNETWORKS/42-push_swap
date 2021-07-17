#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

// static int	partition_stacks(t_stacks *stacks, int pivot, int len, bool push2b_if_lt)
static int	partition_stacks(t_stacks *stacks, enum e_stacks src_stack_id, int pivot, int len)
{
	t_dlist *current;
	t_dlist *next;
	t_dlist *dummy_src;
	int i;
	int adding_count;
	int len_src;

	i = 0;
	adding_count = 0;
	dummy_src = get_stack_from_id(stacks, src_stack_id);
	current = dummy_src->next;
	len_src = dlist_len(dummy_src);
	while (i < len_src)
	{
		next = current->next;
		if (i < len && current->val <= pivot)
		{
			stacks_push2another(stacks, src_stack_id);
			adding_count++;
		}
		else
			stacks_rotate(stacks, src_stack_id);
		current = next;
		i++;
	}
	return (adding_count);
}

static int	partition_stacks_if_lt_or_eq(t_stacks *stacks, enum e_stacks src_stack_id, int pivot, int len)
{
	t_dlist *current;
	t_dlist *next;
	t_dlist *dummy_src;
	int i;
	int adding_count;
	int len_src;

	i = 0;
	adding_count = 0;
	dummy_src = get_stack_from_id(stacks, src_stack_id);
	current = dummy_src->next;
	len_src = dlist_len(dummy_src);
	while (i < len_src)
	{
		next = current->next;
		if (i < len && current->val >= pivot)
		{
			stacks_push2another(stacks, src_stack_id);
			adding_count++;
		}
		else
			stacks_rotate(stacks, src_stack_id);
		current = next;
		i++;
	}
	return (adding_count);
}

/*
 * return: dlist_len(dummy_b)
 */
static int merge_sorted_stacks(t_stacks *stacks, enum e_stacks src_stack_id)
{
	int		len_src;
	bool	is_sorted_des;
	t_dlist	*dummy_src;

	dummy_src = get_stack_from_id(stacks, src_stack_id);
	is_sorted_des = is_stack_sorted_des(dummy_src, -1);
	len_src = dlist_len(dummy_src);
	while (dlist_len(dummy_src))
	{
		if (is_sorted_des)
			stacks_rrotate(stacks, src_stack_id);
		stacks_push2another(stacks, src_stack_id);
		stacks_rotate(stacks, !src_stack_id);
	}
	return (len_src);
}

/*
 * dummy_a: dummy node of stack A
 * dummy_b: dummy node of stack B
 * arr: sorted array for determining pivot.
 * len: the number of unsorted elements.
 *
 * return: the number of elements has been sorted in this call.
 */
static void	quick_sort_stack(t_stacks *stacks, int unsorted_len, enum e_stacks stack_id)
{
	int pivot;
	int sorted_len;
	t_dlist *dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	if (is_stack_sorted_asc(dummy, dlist_len(dummy)))
		return ;
	// pivotを決めてstackBに移動させる
	pivot = dlist_get_mid_value(dummy, unsorted_len);
	fprintf(stderr, "pivot (A to B): %d, unsorted_len: %d\n", pivot, unsorted_len);
	partition_stacks(stacks, STACK_A, pivot, unsorted_len);
	// Bが分割できなくなるまでAに要素を戻す
	while (!(is_stack_sorted_des(stacks->dummy_b, dlist_len(stacks->dummy_b))
			|| is_stack_sorted_asc(stacks->dummy_b, dlist_len(stacks->dummy_b))))
	{
		print_stacks(stacks);
		pivot = dlist_get_mid_value(stacks->dummy_b, dlist_len(stacks->dummy_b));
		fprintf(stderr, "pivot (B to A): %d\n", pivot);
		partition_stacks_if_lt_or_eq(stacks, STACK_B, pivot, dlist_len(stacks->dummy_b));
		if (dlist_len(stacks->dummy_b) <= 3)
			sort_le_3_elements(stacks, STACK_B);
	}
	fprintf(stderr, "finish sorting stack B\n");

	sorted_len = merge_sorted_stacks(stacks, STACK_B);

	fprintf(stderr, "sorted_len: %d\n", sorted_len);
	print_stacks(stacks);
	fprintf(stderr, "next quick_sort_stack() will be started in 1 sec...\n");
	// usleep(0.1 * 1000 * 1000);
	quick_sort_stack(stacks, unsorted_len - sorted_len, STACK_A);
}

void	sort_many_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	quick_sort_stack(stacks, dlist_len(dummy), stack_id);
}
