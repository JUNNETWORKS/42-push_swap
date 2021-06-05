#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "push_swap.h"

/* parse nptr into num.
 *
 * return false if nptr is invalid or overflow.
 * otherwise, return true.
 */
static bool	my_atoi(const char *nptr, int *num)
{
	int				sign;

	*num = 0;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	if (is_overflow(nptr, sign))
		return (false);
	while (*nptr)
	{
		if (ft_isdigit(*nptr))
			*num = *num * 10 + (*nptr++ - '0');
		else
			return (false);
	}
	*num *= sign;
	return (true);
}

static bool	parse_argv(t_dlist *dummy, char **argv)
{
	int	val;
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!my_atoi(argv[i], &val) || !dlist_add_prev(dummy, val))
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_dlist	*dummy_a;
	t_dlist	*dummy_b;

	if (argc <= 1)
	{
		printf("Invalid argc\n");
		return (1);
	}
	dummy_a = create_dlist(0);
	dummy_b = create_dlist(0);
	if (!dummy_a || !dummy_b || !parse_argv(dummy_a, argv + 1))
	{
		printf("nums are invalid or malloc() failed\n");
		free_dlist(dummy_a);
		free_dlist(dummy_b);
		return (1);
	}
	printf("HELLO PUSH_SWAP\n");
	print_stacks(dummy_a, dummy_b);
	printf("dummy_a has %d elements\n", dlist_len(dummy_a));
	printf("---- dlist function tests ----\n");
	char		*buf = NULL;
	size_t		read_len;
	while (getline(&buf, &read_len, stdin) > 0)
	{
		if (!ft_strncmp(buf, "swap", 4))
			dlist_swap_first2(dummy_a);
		else if (!ft_strncmp(buf, "rotate", 6))
			dlist_rotate(dummy_a);
		else if (!ft_strncmp(buf, "rrotate", 7))
			dlist_rrotate(dummy_a);
		else if (!ft_strncmp(buf, "psa", 3))
			push_a(dummy_a, dummy_b);
		else if (!ft_strncmp(buf, "psb", 3))
			push_b(dummy_a, dummy_b);
		else
			printf("invalid command\n");
		free(buf);
		buf = NULL;
		print_stacks(dummy_a, dummy_b);
	}
}
