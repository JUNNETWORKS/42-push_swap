#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_dlist	*dummy_a;
	t_dlist	*dummy_b;
	t_dlist	*dummy_op;

	if (argc <= 1)
	{
		printf("Invalid argc\n");
		return (1);
	}
	dummy_a = create_dlist(0);
	dummy_b = create_dlist(0);
	dummy_op = create_dlist(0);
	if (!dummy_a || !dummy_b || !dummy_op || !parse_argv(dummy_a, argv + 1))
	{
		printf("nums are invalid or malloc() failed\n");
		return (1);
	}
	printf("dummy_a has %d elements\n", dlist_len(dummy_a));
	print_stacks(dummy_a, dummy_b);
	sort_stacks(dummy_a, dummy_b);
	printf("\n---------- stacks has been sorted ----------\n\n");
	print_stacks(dummy_a, dummy_b);
}
