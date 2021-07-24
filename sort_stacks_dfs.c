#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

static void	update_dfs_data(t_dfs *dfs_data, int turn)
{
	t_dlist				*dummy_old;

	dfs_data->best_turn = turn;
	dummy_old = dfs_data->dummy_ops;
	dfs_data->dummy_ops = dlist_duplicate(dfs_data->dummy_tmp_ops);
	free_dlist(dummy_old);
}

static void	do_operation4dfs(t_stacks *stacks,
	t_dfs *dfs_data, enum e_stacks stack_id, enum e_operations op)
{
	do_operation(stacks, dfs_data->dummy_tmp_ops, op);
	if ((stack_id == STACK_A && op == OP_PB)
		|| (stack_id == STACK_B && op == OP_PA))
		dfs_data->push2another_count++;
	else if ((stack_id == STACK_A && op == OP_PA)
		|| (stack_id == STACK_B && op == OP_PB))
		dfs_data->push2another_count--;
}

static void	undo_operation4dfs(t_stacks *stacks,
	  t_dfs *dfs_data, enum e_stacks stack_id, enum e_operations op)
{
	undo_operation(stacks, dfs_data->dummy_tmp_ops, op);
	if ((stack_id == STACK_A && op == OP_PB)
		|| (stack_id == STACK_B && op == OP_PA))
		dfs_data->push2another_count--;
	else if ((stack_id == STACK_A && op == OP_PA)
		|| (stack_id == STACK_B && op == OP_PB))
		dfs_data->push2another_count++;
}

/*
 * Not modify data on a stack that is not stack of stack_id.
 */
static bool	is_invalid_operation4dfs(t_stacks *stacks,
	t_dfs *dfs_data, enum e_stacks stack_id, enum e_operations op)
{
	bool	is_stack_a_invalid;
	bool	is_stack_b_invalid;

	is_stack_a_invalid = stack_id == STACK_A
		&& (op == OP_RB || op == OP_RRB || op == OP_SB
			|| (dfs_data->push2another_count == 0 && op == OP_PA));
	is_stack_b_invalid = stack_id == STACK_B
		&& (op == OP_RA || op == OP_RRA || op == OP_SA
			|| (dfs_data->push2another_count == 0 && op == OP_PB));
	return (!is_valid_operation(stacks, dfs_data->dummy_tmp_ops, op)
		|| op == OP_RR || op == OP_RRR || op == OP_SS
		|| is_stack_a_invalid || is_stack_b_invalid);
}

void	sort_stack_dfs(t_stacks *stacks,
	t_dfs *dfs_data, enum e_stacks stack_id, int turn)
{
	enum e_operations	op;
	t_dlist				*dummy_stack;

	if (turn >= dfs_data->best_turn)
		return ;
	dummy_stack = get_stack_from_id(stacks, stack_id);
	if (dlist_len(dummy_stack) == dfs_data->stack_size
		&& is_stack_sorted_asc(dummy_stack, dlist_len(dummy_stack)))
		return (update_dfs_data(dfs_data, turn));
	op = OP_SA - 1;
	while (++op <= OP_RRR)
	{
		if (is_invalid_operation4dfs(stacks, dfs_data, stack_id, op))
			continue ;
		do_operation4dfs(stacks, dfs_data, stack_id, op);
		sort_stack_dfs(stacks, dfs_data, stack_id, turn + 1);
		undo_operation4dfs(stacks, dfs_data, stack_id, op);
	}
}
