#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

void	sort_stack_dfs(t_stacks *stacks, t_dfs *dfs_data, enum e_stacks stack_id, int turn)
{
	enum e_operations	op;
	t_dlist				*dummy_old;
	t_dlist				*dummy_stack;

	if (turn >= dfs_data->best_turn)
		return ;
	dummy_stack = get_stack_from_id(stacks, stack_id);
	if (dlist_len(dummy_stack) == dfs_data->stack_size
		&& is_stack_sorted_asc(dummy_stack, dlist_len(dummy_stack)))
	{
		dfs_data->best_turn = turn;
		dummy_old = dfs_data->dummy_ops;
		dfs_data->dummy_ops = dlist_duplicate(dfs_data->dummy_tmp_ops);
		free_dlist(dummy_old);
		fprintf(stderr, "best_turn: %d\n", dfs_data->best_turn);
		// print_all_operations(dfs_data);
		return ;
	}
	op = OP_SA - 1;
	while (++op <= OP_RRR)
	{
		if (!is_valid_operation(stacks, dfs_data->dummy_tmp_ops, op))
			continue;
		// 自分のスタック(stack_id)ではないスタックのデータは変更しない
		if (op == OP_RR || op == OP_RRR || op == OP_SS
			|| (stack_id == STACK_A && (op == OP_RB || op == OP_RRB || op == OP_SB))
			|| (stack_id == STACK_B && (op == OP_RA || op == OP_RRA || op == OP_SA)))
			continue;
		do_operation(stacks, dfs_data->dummy_tmp_ops, op);
		sort_stack_dfs(stacks, dfs_data, stack_id, turn + 1);
		undo_operation(stacks, dfs_data->dummy_tmp_ops, op);
	}
}

void	sort_le_6_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dfs	dfs_data;

	dfs_data.best_turn = 12;
	dfs_data.dummy_ops = create_dlist(0);
	dfs_data.dummy_tmp_ops = create_dlist(0);
	dfs_data.stack_size = dlist_len(get_stack_from_id(stacks, stack_id));
	if (!dfs_data.dummy_tmp_ops)
		exit(1);
	sort_stack_dfs(stacks, &dfs_data, stack_id, 0);
	dlist_concat_prev(stacks->dummy_ops, dfs_data.dummy_ops);
	free_dlist(dfs_data.dummy_tmp_ops);
	free_dlist(dfs_data.dummy_ops);

	// デバッグ用
	// t_dlist	*current;
	// current = stacks->dummy_ops->next;
	// while (current != stacks->dummy_ops)
	// {
	// 	do_operation(stacks, NULL, current->val);
	// 	const char *str = get_operation_str(current->val);
	// 	fprintf(stderr, "%s\n", str);
	// 	free((void *)str);
	// 	current = current->next;
	// }
}
