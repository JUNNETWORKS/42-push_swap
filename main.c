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
	if (argc <= 1 || !parse_argv(stacks.dummy_a, argv + 1))
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		return (1);
	}
	fprintf(stderr, "dummy_a has %d elements\n", dlist_len(stacks.dummy_a));
	print_stacks(&stacks);

	dlist_at(stacks.dummy_a, dlist_get_min_val_idx(stacks.dummy_a), &stacks.next_val);
	stacks.sorted_len = 0;
	sort_stacks(&stacks);
	fprintf(stderr, "before optimization: %d\n", dlist_len(stacks.dummy_ops));
	optimize_operations(&stacks);
	fprintf(stderr, "after optimization: %d\n", dlist_len(stacks.dummy_ops));
	print_all_operations(&stacks);

	fprintf(stderr, "\n---------- stacks has been sorted ----------\n\n");
	print_stacks(&stacks);
	fprintf(stderr, "operations count: %d\n", dlist_len(stacks.dummy_ops));
	free_dlist(stacks.dummy_a);
	free_dlist(stacks.dummy_b);
	free_dlist(stacks.dummy_ops);
}
