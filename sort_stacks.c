#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_3_le_elements(t_dlist *dummy_a)
{
	int	value0;
	int	value1;
	int	value2;

	if (dlist_len(dummy_a) == 2)
	{
		dlist_at(dummy_a, 0, &value0);
		dlist_at(dummy_a, 1, &value1);
		if (value0 > value1)
			dlist_swap_first2(dummy_a);
	}
	else if (dlist_len(dummy_a) == 3)
	{
		dlist_at(dummy_a, 0, &value0);
		dlist_at(dummy_a, 1, &value1);
		dlist_at(dummy_a, 2, &value2);
		if (value0 > value1)
		{
			if (value1 > value2)
			{
				dlist_swap_first2(dummy_a);
				dlist_rrotate(dummy_a);
			}
			else if (value0 > value2)
				dlist_rotate(dummy_a);
			else
				dlist_swap_first2(dummy_a);
		}
		else if (value0 > value2 || value1 > value2)
		{
			if (value0 < value2)
			{
				dlist_swap_first2(dummy_a);
				dlist_rotate(dummy_a);
			}
			else if (value0 > value2)
				dlist_rrotate(dummy_a);
		}
	}
}

void	sort_6_le_elements(t_dlist *dummy_a, t_dlist *dummy_b)
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
	sort_3_le_elements(dummy_a);
	print_stacks(dummy_a, dummy_b);
	while (dlist_len(dummy_b))
		push_a(dummy_a, dummy_b);
	return ;
}

void	sort_many_elements(t_dlist *dummy_a, t_dlist *dummy_b)
{
	(void)dummy_a;
	(void)dummy_b;
	return ;
}

void	sort_stacks(t_dlist *dummy_a, t_dlist *dummy_b)
{
	if (dlist_len(dummy_a) <= 3)
		sort_3_le_elements(dummy_a);
	else if (dlist_len(dummy_a) <= 6)
		sort_6_le_elements(dummy_a, dummy_b);
	else
		sort_many_elements(dummy_a, dummy_b);
}
