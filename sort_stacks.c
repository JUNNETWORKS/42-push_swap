#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_stacks(t_stacks *stacks)
{
	if (dlist_len(stacks->dummy_a) <= 3)
		sort_le_3_elements(stacks, STACK_A);
	else if (dlist_len(stacks->dummy_a) <= 6)
		sort_le_6_elements(stacks, STACK_A);
	else
		sort_many_elements(stacks, STACK_A);
}
