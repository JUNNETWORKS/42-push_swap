#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_3_le_elements(t_dlist *dummy_a, t_dlist *dummy_b)
{
	int	value0;
	int	value1;
	int	value2;

	(void)dummy_b;
	(void)value2;
	if (dlist_len(dummy_a) == 2)
	{
		dlist_at(dummy_a, 0, &value0);
		dlist_at(dummy_a, 1, &value1);
		if (value0 > value1)
			dlist_swap_first2(dummy_a);
	}
	else if (dlist_len(dummy_a) == 3)
	{
		return ;
	}
}

void	sort_6_le_elements(t_dlist *dummy_a, t_dlist *dummy_b)
{
	(void)dummy_a;
	(void)dummy_b;
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
		sort_3_le_elements(dummy_a, dummy_b);
	else if (dlist_len(dummy_a) <= 3)
		sort_6_le_elements(dummy_a, dummy_b);
	else
		sort_many_elements(dummy_a, dummy_b);
}
