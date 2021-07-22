#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	quick_sort_stacks(t_stacks *stacks)
{
	int	old_ops_count;

	if (is_stack_sorted_asc(stacks->dummy_a, dlist_len(stacks->dummy_a)))
		return ;
	old_ops_count = dlist_len(stacks->dummy_ops);
	partition_stack_a(stacks);
	fprintf(stderr, "\n----- partition_stack_a() finished (%+d) -----\n", dlist_len(stacks->dummy_ops) - old_ops_count);
	print_stacks(stacks);
	old_ops_count = dlist_len(stacks->dummy_ops);
	partition_stack_b_and_merge2a(stacks);
	fprintf(stderr, "\n----- partition_stack_b_and_merge2a() finished (%+d) -----\n", dlist_len(stacks->dummy_ops) - old_ops_count);
	print_stacks(stacks);
#if DEBUG
	sleep(1);
#endif
	quick_sort_stacks(stacks);
}

void	sort_many_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	(void)stack_id;
	quick_sort_stacks(stacks);
}
