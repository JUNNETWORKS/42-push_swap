#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	quick_sort_stacks(t_stacks *stacks)
{
	if (is_stack_sorted_asc(stacks->dummy_a, dlist_len(stacks->dummy_a)))
		return ;
	partition_stack_a(stacks);
	partition_stack_b_and_merge2a(stacks);
	quick_sort_stacks(stacks);
}

void	sort_many_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	(void)stack_id;
	quick_sort_stacks(stacks);
}
