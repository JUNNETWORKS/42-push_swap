#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

static void	init_stacks(t_stacks *stacks)
{
	stacks->dummy_a = create_dlist(0);
	stacks->dummy_b = create_dlist(0);
	stacks->dummy_ops = create_dlist(0);
	if (!(stacks->dummy_a && stacks->dummy_b && stacks->dummy_ops))
		exit(1);
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc <= 1)
	{
		printf("Invalid argc\n");
		return (1);
	}
	init_stacks(&stacks);
	if (!parse_argv(stacks.dummy_a, argv + 1))
	{
		printf("nums are invalid or malloc() failed\n");
		return (1);
	}
	printf("dummy_a has %d elements\n", dlist_len(stacks.dummy_a));
	print_stacks(&stacks);
	sort_stacks(&stacks);
	printf("\n---------- stacks has been sorted ----------\n\n");
	print_stacks(&stacks);

	printf("\n---------- operations ----------\n");
	for (t_dlist *current = stacks.dummy_ops->next; current != stacks.dummy_ops; current = current->next)
	{
		const char *op_str = get_operation_str(current->val);
		if (!op_str)
			exit(1);
		printf("%s\n", op_str);
		free((char *)op_str);
	}
	printf("operations count: %d\n", dlist_len(stacks.dummy_ops));
}
