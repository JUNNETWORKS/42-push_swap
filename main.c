#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	init_stacks(t_stacks *stacks)
{
	stacks->dummy_a = create_dlist(0);
	stacks->dummy_b = create_dlist(0);
	stacks->dummy_ops = create_dlist(0);
	stacks->pivot_count = 0;
	if (!(stacks->dummy_a && stacks->dummy_b && stacks->dummy_ops))
		exit(1);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	init_stacks(&stacks);
	if (argc <= 1 || argc > 10000 || !parse_argv(stacks.dummy_a, argv + 1))
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		return (1);
	}
	stacks.sorted_arr = dlist2arr(stacks.dummy_a);
	stacks.size = dlist_len(stacks.dummy_a);
	stacks.sorted_len = 0;
	sort_stacks(&stacks);
	optimize_operations(&stacks);
	print_all_operations(&stacks);
	free_dlist(stacks.dummy_a);
	free_dlist(stacks.dummy_b);
	free_dlist(stacks.dummy_ops);
	free(stacks.sorted_arr);
}
