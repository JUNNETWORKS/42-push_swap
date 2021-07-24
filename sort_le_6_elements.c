#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

static void	update_dummy_ops(t_dfs *dfs_data, int turn)
{
	t_dlist				*dummy_old;

	dfs_data->best_turn = turn;
	dummy_old = dfs_data->dummy_ops;
	dfs_data->dummy_ops = dlist_duplicate(dfs_data->dummy_tmp_ops);
	free_dlist(dummy_old);
	fprintf(stderr, "best_turn: %d\n", dfs_data->best_turn);
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

/* 自分のスタック(stack_id)ではないスタックのデータは変更しない
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
		return (update_dummy_ops(dfs_data, turn));
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

void	sort_le_6_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dfs	dfs_data;
	t_dlist	*current;

	dfs_data.best_turn = 12;
	dfs_data.dummy_ops = create_dlist(0);
	dfs_data.dummy_tmp_ops = create_dlist(0);
	dfs_data.stack_size = dlist_len(get_stack_from_id(stacks, stack_id));
	dfs_data.push2another_count = 0;
	if (!dfs_data.dummy_tmp_ops)
		exit(1);
	sort_stack_dfs(stacks, &dfs_data, stack_id, 0);
	current = dfs_data.dummy_ops->next;
	while (current != dfs_data.dummy_ops)
	{
		do_operation(stacks, NULL, current->val);
		current = current->next;
	}
	dlist_concat_prev(stacks->dummy_ops, dfs_data.dummy_ops);
	free_dlist(dfs_data.dummy_tmp_ops);
	free_dlist(dfs_data.dummy_ops);
}
