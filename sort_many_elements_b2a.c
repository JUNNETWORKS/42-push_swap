#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

static void	push_b2a(t_stacks *stacks, int new_group)
{
	stacks->dummy_b->next->group = new_group;
	stacks_push2another(stacks, STACK_B);
}

static void	partition_stack_b(t_stacks *stacks)
{
	int		pivot;
	int		i;
	t_dlist	*current;
	t_dlist	*tmp;

	while (!is_stack_sorted_asc(stacks->dummy_b, dlist_len(stacks->dummy_b))
		&& dlist_len(stacks->dummy_b) > 6)
	{
		pivot = dlist_get_mid_value(stacks->dummy_b,
				dlist_len(stacks->dummy_b));
		stacks->pivot_count++;
		current = stacks->dummy_b->next;
		i = dlist_len(stacks->dummy_b);
		while (i-- > 0)
		{
			tmp = current->next;
			if (current->val > pivot)
				push_b2a(stacks, stacks->pivot_count);
			else
				stacks_rotate(stacks, STACK_B);
			current = tmp;
		}
		print_stacks(stacks);
	}
}

void	partition_stack_b_and_merge2a(t_stacks *stacks)
{
	partition_stack_b(stacks);
	if (dlist_len(stacks->dummy_b) <= 6)
		sort_le_6_elements(stacks, STACK_B);
	stacks->pivot_count++;
	print_stacks(stacks);
	while (dlist_len(stacks->dummy_b))
	{
		push_b2a(stacks, stacks->pivot_count);
		stacks_rotate(stacks, STACK_A);
		stacks->sorted_len++;
	}
}
