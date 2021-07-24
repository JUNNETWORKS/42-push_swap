#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

static void	swap_and_rotate_first2(t_stacks *stacks, int group_len)
{
	if (group_len == 2)
		sort_2_elements(stacks, STACK_A);
	while (group_len-- > 0)
		stacks_rotate(stacks, STACK_A);
}

static void	partition_group(t_stacks *stacks, int group_len)
{
	int		pivot;
	int		i;
	t_dlist	*current;
	t_dlist	*tmp;

	pivot = dlist_get_mid_value(stacks->dummy_a, group_len);
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
	i = group_len - dlist_len(stacks->dummy_b);
	if (stacks->sorted_len == 0)
		i = 0;
	while (i-- > 0)
		stacks_rrotate(stacks, STACK_A);
}

void	partition_stack_a(t_stacks *stacks)
{
	int		group_len;

	group_len = get_head_group_len(stacks->dummy_a);
	if (group_len <= 2)
		return (swap_and_rotate_first2(stacks, group_len));
	partition_group(stacks, group_len);
}
