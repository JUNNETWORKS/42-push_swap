#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	sort_2_elements(t_dlist *dummy_a)
{
	int	value0;
	int	value1;

	dlist_at(dummy_a, 0, &value0);
	dlist_at(dummy_a, 1, &value1);
	if (value0 > value1)
		dlist_swap_first2(dummy_a);
}

static void	sort_3_elements(t_dlist *dummy_a)
{
	int	value0;
	int	value1;
	int	value2;

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

void	sort_le_3_elements(t_dlist *dummy_a)
{
	if (dlist_len(dummy_a) == 2)
		sort_2_elements(dummy_a);
	else if (dlist_len(dummy_a) == 3)
		sort_3_elements(dummy_a);
}

