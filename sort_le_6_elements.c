#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

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
