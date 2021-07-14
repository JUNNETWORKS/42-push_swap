#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_le_6_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	int	min_idx;
	t_dlist	*dummy;
	t_dlist	*dummy_another;

	dummy = get_stack_from_id(stacks, stack_id);
	dummy_another = get_stack_from_id(stacks, !stack_id);
	// スタックAのサイズが3になるまで小さい数をスタックBに移動させる
	while (dlist_len(dummy) > 3)
	{
		min_idx = dlist_get_min_val_idx(dummy);
		while (min_idx)
		{
			stacks_rotate(stacks, stack_id);
			min_idx--;
		}
		stacks_push2another(stacks, stack_id);
	}
	print_stacks(stacks);
	sort_le_3_elements(stacks, stack_id);
	print_stacks(stacks);
	while (dlist_len(dummy_another))
		stacks_push2another(stacks, !stack_id);
}
