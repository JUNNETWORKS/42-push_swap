#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	undo_operation(t_stacks *stacks, t_dlist *dummy_ops, enum e_operations op)
{
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

static void	do_operation(t_stacks *stacks, t_dlist *dummy_ops, enum e_operations op)
{
	dlist_add_prev(dummy_ops, op);
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

static bool	is_valid_operation(t_stacks *stacks, t_dlist *dummy_ops, enum e_operations op)
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

void	dfs(t_stacks *stacks, t_dlist *dummy_ops, int *best_turn, int turn)
{
	enum e_operations	op;
	t_dlist				*dummy_old;

	if (turn >= *best_turn)
		return ;
	if (dlist_len(stacks->dummy_b) == 0
		&& is_stack_sorted_asc(stacks->dummy_a, dlist_len(stacks->dummy_a)))
	{
		*best_turn = turn;
		dummy_old = stacks->dummy_ops;
		stacks->dummy_ops = dlist_duplicate(dummy_ops);
		free_dlist(dummy_old);
		fprintf(stderr, "best_turn: %d\n", *best_turn);
		// print_all_operations(stacks);
		return ;
	}
	op = OP_SA - 1;
	while (++op <= OP_RRR)
	{
		if (!is_valid_operation(stacks, dummy_ops, op))
			continue;
		do_operation(stacks, dummy_ops, op);
		dfs(stacks, dummy_ops, best_turn, turn + 1);
		undo_operation(stacks, dummy_ops, op);
	}
}

void	sort_le_6_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	/*
	int		best_turn;
	t_dlist	*dummy_ops_tmp;

	best_turn = 12;
	dummy_ops_tmp = create_dlist(0);
	if (!dummy_ops_tmp)
		exit(1);
	dfs(stacks, dummy_ops_tmp, &best_turn, 0);
	free_dlist(dummy_ops_tmp);
	*/
	int pivot;
	int i;
	int len;
	t_dlist *current;
	t_dlist *next;

	(void)stack_id;
	i = 0;
	len = dlist_len(stacks->dummy_a);
	pivot = dlist_get_mid_value(stacks->dummy_a, len);
	current = stacks->dummy_a->next;
	while (i < len)
	{
		next = current->next;
		if (current->val >= pivot)
			stacks_push2another(stacks, STACK_A);
		else
			stacks_rotate(stacks, STACK_A);
		current = next;
		i++;
	}
	sort_le_3_elements(stacks, STACK_A);
	sort_le_3_elements(stacks, STACK_B);
	print_stacks(stacks);
	while (dlist_len(stacks->dummy_b))
	{
		stacks_push2another(stacks, STACK_B);
		stacks_rotate(stacks, STACK_A);
	}
}
