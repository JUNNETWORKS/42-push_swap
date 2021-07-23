#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

void	partition_stack_a(t_stacks *stacks)
{
	int		pivot;
	int		group_len;
	int		i;
	t_dlist	*current;
	t_dlist	*tmp;

	group_len = get_head_group_len(stacks->dummy_a);
	if (group_len <= 2)
	{
		if (group_len == 2)
			sort_2_elements(stacks, STACK_A);
		while (group_len-- > 0)
			stacks_rotate(stacks, STACK_A);
		return ;
	}
	pivot = dlist_get_mid_value(stacks->dummy_a, group_len);
	fprintf(stderr, "pivot(a2b): %d (group: %d), group_len: %d\n",
		pivot, stacks->dummy_a->next->group, group_len);
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

