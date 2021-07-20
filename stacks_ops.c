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

void	print_all_operations(t_stacks *stacks)
{
	t_dlist		*current;
	const char	*op_str;

	current = stacks->dummy_ops->next;
	while (current != stacks->dummy_ops)
	{
		op_str = get_operation_str(current->val);
		if (!op_str)
			exit(1);
		ft_putendl_fd((char *)op_str, STDOUT_FILENO);
		free((char *)op_str);
		current = current->next;
	}
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
			fprintf(stderr, "|%4d (%3d)|", current_a->val, current_a->group);
			current_a = current_a->next;
			len_a--;
		}
		else
			fprintf(stderr, "|          |");
		fprintf(stderr, "  ");
		if (len_b > 0 && len_b > len_a)
		{
			fprintf(stderr, "|%4d (%3d)|", current_b->val, current_b->group);
			current_b = current_b->next;
			len_b--;
		}
		else
			fprintf(stderr, "|          |");
		fprintf(stderr, "\n");
	}
	fprintf(stderr, " ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄   ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄ ̄\n");
	fprintf(stderr, "      a           b   \n");
}
