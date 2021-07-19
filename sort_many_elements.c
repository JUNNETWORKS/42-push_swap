#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

void	sort_many_elements(t_stacks *stacks, enum e_stacks stack_id)
{
	t_dlist	*dummy;

	dummy = get_stack_from_id(stacks, stack_id);
	quick_sort_stack(stacks, dlist_len(dummy), stack_id);
}
