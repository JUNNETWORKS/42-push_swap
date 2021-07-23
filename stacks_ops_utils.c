#include "libft/libft.h"
#include "stacks.h"

void	undo_operation(t_stacks *stacks,
	t_dlist *dummy_ops, enum e_operations op)
{
	if (dummy_ops)
		dlist_del_prev(dummy_ops);
	if (op == OP_PA)
		dlist_push(stacks->dummy_b, dlist_pop(stacks->dummy_a));
	if (op == OP_PB)
		dlist_push(stacks->dummy_a, dlist_pop(stacks->dummy_b));
	if (op == OP_SA || op == OP_SS)
		dlist_swap_first2(stacks->dummy_a);
	if (op == OP_SB || op == OP_SS)
		dlist_swap_first2(stacks->dummy_b);
	if (op == OP_RA || op == OP_RR)
		dlist_rrotate(stacks->dummy_a);
	if (op == OP_RB || op == OP_RR)
		dlist_rrotate(stacks->dummy_b);
	if (op == OP_RRA || op == OP_RRR)
		dlist_rotate(stacks->dummy_a);
	if (op == OP_RRB || op == OP_RRR)
		dlist_rotate(stacks->dummy_b);
}

void	do_operation(t_stacks *stacks,
	t_dlist *dummy_ops, enum e_operations op)
{
	if (dummy_ops)
		dlist_add_prev(dummy_ops, op, 0);
	if (op == OP_PA)
		dlist_push(stacks->dummy_a, dlist_pop(stacks->dummy_b));
	if (op == OP_PB)
		dlist_push(stacks->dummy_b, dlist_pop(stacks->dummy_a));
	if (op == OP_SA || op == OP_SS)
		dlist_swap_first2(stacks->dummy_a);
	if (op == OP_SB || op == OP_SS)
		dlist_swap_first2(stacks->dummy_b);
	if (op == OP_RA || op == OP_RR)
		dlist_rotate(stacks->dummy_a);
	if (op == OP_RB || op == OP_RR)
		dlist_rotate(stacks->dummy_b);
	if (op == OP_RRA || op == OP_RRR)
		dlist_rrotate(stacks->dummy_a);
	if (op == OP_RRB || op == OP_RRR)
		dlist_rrotate(stacks->dummy_b);
}

bool	is_valid_operation(t_stacks *stacks,
	t_dlist *dummy_ops, enum e_operations op)
{
	if ((op == OP_SA && dummy_ops->prev->val == OP_SA)
		|| (op == OP_SB && dummy_ops->prev->val == OP_SB)
		|| (op == OP_SS && dummy_ops->prev->val == OP_SS)
		|| (op == OP_SA && dummy_ops->prev->val == OP_SB)
		|| (op == OP_SB && dummy_ops->prev->val == OP_SA)
		|| (op == OP_RA && dummy_ops->prev->val == OP_RRA)
		|| (op == OP_RRA && dummy_ops->prev->val == OP_RA)
		|| (op == OP_RB && dummy_ops->prev->val == OP_RRB)
		|| (op == OP_RRB && dummy_ops->prev->val == OP_RB)
		|| (op == OP_PA && dummy_ops->prev->val == OP_PB)
		|| (op == OP_PB && dummy_ops->prev->val == OP_PA)
		|| (dlist_len(stacks->dummy_b) == 0
			&& (op == OP_PA || op == OP_RB || op == OP_RRB))
		|| (dlist_len(stacks->dummy_a) == 0
			&& (op == OP_PB || op == OP_RB || op == OP_RRA)))
		return (false);
	return (true);
}
