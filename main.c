#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	init_stacks(t_stacks *stacks)
{
	stacks->dummy_a = create_dlist(0);
	stacks->dummy_b = create_dlist(0);
	stacks->dummy_ops = create_dlist(0);
	stacks->sorted_arr = NULL;
	stacks->pivot_count = 0;
	if (!(stacks->dummy_a && stacks->dummy_b && stacks->dummy_ops))
		exit(1);
}

static void	free_stacks(t_stacks *stacks)
{
	free_dlist(stacks->dummy_a);
	free_dlist(stacks->dummy_b);
	free_dlist(stacks->dummy_ops);
	free(stacks->sorted_arr);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	(void)argc;
	init_stacks(&stacks);
	if (!parse_argv(stacks.dummy_a, argv + 1))
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		free_stacks(&stacks);
		return (1);
	}
	stacks.sorted_arr = dlist2arr(stacks.dummy_a);
	stacks.size = dlist_len(stacks.dummy_a);
	stacks.sorted_len = 0;
	sort_stacks(&stacks);
	optimize_operations(&stacks);
	print_all_operations(&stacks);
	free_stacks(&stacks);
}
