#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_le_6_elements(t_dlist *dummy_a, t_dlist *dummy_b)
{
	int	min_idx;

	// スタックAのサイズが3になるまで小さい数をスタックBに移動させる
	while (dlist_len(dummy_a) > 3)
	{
		min_idx = dlist_get_min_val_idx(dummy_a);
		while (min_idx)
		{
			dlist_rotate(dummy_a);
			min_idx--;
		}
		push_b(dummy_a, dummy_b);
	}
	print_stacks(dummy_a, dummy_b);
	sort_le_3_elements(dummy_a);
	print_stacks(dummy_a, dummy_b);
	while (dlist_len(dummy_b))
		push_a(dummy_a, dummy_b);
	return ;
}
