#include <stdio.h>
#include "libft/libft.h"
#include "stacks.h"

/*
 * Take the first element at the top of b and put it at the top of a.
 * Do nothing if b is empty.
 */
void	stacks_push2another(t_stacks *stacks, enum e_stacks src_stack_id)
{
	t_dlist	*dummy_src;
	t_dlist	*dummy_dst;
	t_dlist	*top;

	dummy_src = get_stack_from_id(stacks, src_stack_id);
	dummy_dst = get_stack_from_id(stacks, !src_stack_id);
	top = dlist_pop(dummy_src);
	if (!top)
		return ;
	dlist_push(dummy_dst, top);
	if (src_stack_id == STACK_A)
		dlist_add_prev(stacks->dummy_ops, OP_PB);
	else
		dlist_add_prev(stacks->dummy_ops, OP_PA);
}

void	stacks_swap(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	dlist_swap_first2(dummy);
	if (stack_id == STACK_A)
		dlist_add_prev(stacks->dummy_ops, OP_SA);
	else
		dlist_add_prev(stacks->dummy_ops, OP_SB);
}

void	stacks_rotate(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	dlist_rotate(dummy);
	if (stack_id == STACK_A)
		dlist_add_prev(stacks->dummy_ops, OP_RA);
	else
		dlist_add_prev(stacks->dummy_ops, OP_RB);
}

void	stacks_rrotate(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	dlist_rrotate(dummy);
	if (stack_id == STACK_A)
		dlist_add_prev(stacks->dummy_ops, OP_RRA);
	else
		dlist_add_prev(stacks->dummy_ops, OP_RRB);
}

void	print_stacks(t_stacks *stacks)
{
	int		len_a;
	int		len_b;
	t_dlist	*current_a;
	t_dlist	*current_b;

	len_a = dlist_len(stacks->dummy_a);
	len_b = dlist_len(stacks->dummy_b);
	current_a = stacks->dummy_a->next;
	current_b = stacks->dummy_b->next;
	while (len_a > 0 || len_b > 0)
	{
		if (len_a > 0 && len_a >= len_b)
		{
			printf("|%4d|", current_a->val);
			current_a = current_a->next;
			len_a--;
		}
		else
			printf("|    |");
		printf("  ");
		if (len_b > 0 && len_b > len_a)
		{
			printf("|%4d|", current_b->val);
			current_b = current_b->next;
			len_b--;
		}
		else
			printf("|    |");
		printf("\n");
	}
	printf(" ̄ ̄ ̄ ̄ ̄ ̄   ̄ ̄ ̄ ̄ ̄ ̄\n");
	printf("  a       b   \n");
}
