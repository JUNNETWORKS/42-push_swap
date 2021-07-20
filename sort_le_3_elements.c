#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_2_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	int	value0;
	int	value1;
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	dlist_at(dummy, 0, &value0);
	dlist_at(dummy, 1, &value1);
	if (value0 > value1)
	{
		stacks_swap(stacks, stack_id);
	}
}

void	sort_3_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;
	int		value0;
	int		value1;
	int		value2;

	dummy = get_stack_from_id(stacks, stack_id);
	dlist_at(dummy, 0, &value0);
	dlist_at(dummy, 1, &value1);
	dlist_at(dummy, 2, &value2);
	if (value0 > value1)
	{
		if (value1 > value2)
		{
			stacks_swap(stacks, stack_id);
			stacks_rrotate(stacks, stack_id);
		}
		else if (value0 > value2)
			stacks_rotate(stacks, stack_id);
		else
			stacks_swap(stacks, stack_id);
	}
	else if (value0 > value2 || value1 > value2)
	{
		if (value0 < value2)
		{
			stacks_swap(stacks, stack_id);
			stacks_rotate(stacks, stack_id);
		}
		else if (value0 > value2)
			stacks_rrotate(stacks, stack_id);
	}
}

void	sort_le_3_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	if (dlist_len(dummy) == 2)
		sort_2_elements(stacks, stack_id);
	else if (dlist_len(dummy) == 3)
		sort_3_elements(stacks, stack_id);
}
