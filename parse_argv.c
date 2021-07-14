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

bool	parse_argv(t_dlist *dummy_a, char **argv)
{
	int	val;
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!my_atoi(argv[i], &val) || !dlist_add_prev(dummy_a, val))
			return (false);
		i++;
	}
	return (true);
}