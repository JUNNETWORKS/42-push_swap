#include <stdlib.h>
#include "dlist.h"
#include "stacks.h"

static bool	optimize_swaps(t_dlist **current, t_dlist *new_dummy_ops)
{
	if (((*current)->val == OP_SA && (*current)->next->val == OP_SB)
		|| ((*current)->val == OP_SB && (*current)->next->val == OP_SA))
	{
		if (!dlist_add_prev(new_dummy_ops, OP_SS))
			exit(1);
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}

void	optimize_operations(t_stacks *stacks)
{
	t_dlist	*current;
	t_dlist	*new_dummy_ops;

	new_dummy_ops = create_dlist(0);
	if (!new_dummy_ops)
		exit(1);
	current = stacks->dummy_ops->next;
	while (current != stacks->dummy_ops)
	{
		if (!optimize_swaps(&current, new_dummy_ops))
		{
			dlist_add_prev(new_dummy_ops, current->val);
			current = current->next;
		}
	}
	free_dlist(stacks->dummy_ops);
	stacks->dummy_ops = new_dummy_ops;
}
