#include <stdio.h>
#include "libft/libft.h"
#include "stacks.h"

void	rotate_a(t_stacks *stacks)
{
	dlist_rotate(stacks->dummy_a);
	dlist_add_prev(stacks->dummy_ops, OP_RA);
}
void	rotate_b(t_stacks *stacks)
{
	dlist_rotate(stacks->dummy_b);
	dlist_add_prev(stacks->dummy_ops, OP_RB);
}

void	rrotate_a(t_stacks *stacks)
{
	dlist_rrotate(stacks->dummy_a);
	dlist_add_prev(stacks->dummy_ops, OP_RRA);
}

void	rrotate_b(t_stacks *stacks)
{
	dlist_rrotate(stacks->dummy_b);
	dlist_add_prev(stacks->dummy_ops, OP_RRB);
}
