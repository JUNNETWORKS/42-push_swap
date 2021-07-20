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

static bool	optimize_rotate(t_dlist **current, t_dlist *new_dummy_ops)
{
	if (((*current)->val == OP_RA && (*current)->next->val == OP_RB)
		|| ((*current)->val == OP_RB && (*current)->next->val == OP_RA))
	{
		if (!dlist_add_prev(new_dummy_ops, OP_RR))
			exit(1);
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}

static bool	optimize_rrotate(t_dlist **current, t_dlist *new_dummy_ops)
{
	if (((*current)->val == OP_RRA && (*current)->next->val == OP_RRB)
		|| ((*current)->val == OP_RRB && (*current)->next->val == OP_RRA))
	{
		if (!dlist_add_prev(new_dummy_ops, OP_RRR))
			exit(1);
		*current = (*current)->next->next;
		return (true);
	}
	return (false);
}

static bool	remove_unneeded_operations(t_dlist **current, t_dlist *new_dummy_ops)
{
	(void)new_dummy_ops;
	if (((*current)->val == OP_SA && (*current)->next->val == OP_SA)
		|| ((*current)->val == OP_SB && (*current)->next->val == OP_SB)
		|| ((*current)->val == OP_PA && (*current)->next->val == OP_PB)
		|| ((*current)->val == OP_PB && (*current)->next->val == OP_PA)
		|| ((*current)->val == OP_RA && (*current)->next->val == OP_RRA)
		|| ((*current)->val == OP_RRA && (*current)->next->val == OP_RA)
		|| ((*current)->val == OP_RB && (*current)->next->val == OP_RRB)
		|| ((*current)->val == OP_RRB && (*current)->next->val == OP_RB))
	{
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
		if (!remove_unneeded_operations(&current, new_dummy_ops)
			&& !optimize_swaps(&current, new_dummy_ops)
			&& !optimize_rotate(&current, new_dummy_ops)
			&& !optimize_rrotate(&current, new_dummy_ops))
		{
			dlist_add_prev(new_dummy_ops, current->val);
			current = current->next;
		}
	}
	if (dlist_len(new_dummy_ops) == dlist_len(stacks->dummy_ops))
	{
		free_dlist(new_dummy_ops);
		return ;
	}
	free_dlist(stacks->dummy_ops);
	stacks->dummy_ops = new_dummy_ops;
	optimize_operations(stacks);
}
