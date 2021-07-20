#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	partition_stack_a(t_stacks *stacks)
{
	int pivot;
	int group_len;
	int i;
	t_dlist	*current;
	t_dlist	*tmp;

	group_len = get_head_group_len(stacks->dummy_a);
	if (group_len <= 1)
	{
		stacks_rotate(stacks, STACK_A);
		return ;
	}
	pivot = dlist_get_mid_value(stacks->dummy_a, group_len);
	fprintf(stderr, "pivot(a2b): %d (group: %d), unsorted_len: %d\n", pivot, stacks->dummy_a->next->group, group_len);
	i = 0;
	current = stacks->dummy_a->next;
	while (i < group_len)
	{
		tmp = current->next;
		if (current->val < pivot)
			stacks_push2another(stacks, STACK_A);
		else
			stacks_rotate(stacks, STACK_A);
		current = tmp;
		i++;
	}
	i = group_len - dlist_len(stacks->dummy_b);  // RRAで元に戻す必要のある数
	if (stacks->sorted_len == 0)
		i = 0;
	while (i-- > 0)
		stacks_rrotate(stacks, STACK_A);
}

static void	push_b2a(t_stacks *stacks, int new_group)
{
	stacks->dummy_b->next->group = new_group;
	stacks_push2another(stacks, STACK_B);
}

static void	partition_stack_b_and_merge2a(t_stacks *stacks)
{
	int pivot;
	t_dlist	*current;
	t_dlist	*tmp;

	while (!is_stack_sorted_asc(stacks->dummy_b, dlist_len(stacks->dummy_b))
		&& dlist_len(stacks->dummy_b) > 3)
	{
		pivot = dlist_get_mid_value(stacks->dummy_b, dlist_len(stacks->dummy_b));
		stacks->pivot_count++;
		fprintf(stderr, "pivot(b2a): %d, pivot_count: %d\n", pivot, stacks->pivot_count);
		current = stacks->dummy_b->next;
		int i = dlist_len(stacks->dummy_b);
		while (i-- > 0)
		{
			tmp = current->next;
			if (current->val > pivot)
				push_b2a(stacks, stacks->pivot_count);
			else
				stacks_rotate(stacks, STACK_B);
			current = tmp;
		}
	}
	if (dlist_len(stacks->dummy_b) <= 3)
		sort_le_3_elements(stacks, STACK_B);
	while (dlist_len(stacks->dummy_b))
	{
		push_b2a(stacks, stacks->pivot_count);
		stacks_rotate(stacks, STACK_A);
		stacks->sorted_len++;
	}
}

static void	quick_sort_stacks(t_stacks *stacks)
{
	if (is_stack_sorted_asc(stacks->dummy_a, dlist_len(stacks->dummy_a)))
		return ;
	partition_stack_a(stacks);
	print_stacks(stacks);
	partition_stack_b_and_merge2a(stacks);
	print_stacks(stacks);
	sleep(1);
	quick_sort_stacks(stacks);
}

void	sort_many_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	(void)stack_id;
	quick_sort_stacks(stacks);
}
