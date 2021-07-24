#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "libft/libft.h"
#include "push_swap.h"

/* parse nptr into num.
 *
 * return false if nptr is invalid or overflow.
 * otherwise, return true.
 *
 * inequality below detects overflow.
 *   10 * ans + (s[i] - '0') > INT_MAX
 *   10 * ans - (s[i] - '0') < INT_MIN
 */
static bool	my_atoi(const char *nptr, int *num)
{
	int				sign;

	*num = 0;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign = -1;
	if (!ft_isdigit(*nptr))
		return (false);
	while (*nptr)
	{
		if (!ft_isdigit(*nptr)
			|| sign * *num > (INT_MAX - (*nptr - '0')) / 10
			|| sign * *num < (INT_MIN + (*nptr - '0')) / 10)
			return (false);
		*num = *num * 10 + (*nptr++ - '0');
	}
	*num *= sign;
	return (true);
}

static bool	is_duplicated(t_dlist *dummy_a, int val)
{
	t_dlist	*current;

	current = dummy_a->next;
	while (current != dummy_a)
	{
		if (current->val == val)
			return (true);
		current = current->next;
	}
	return (false);
}

bool	parse_argv(t_dlist *dummy_a, char **argv)
{
	int	val;
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!my_atoi(argv[i], &val)
			|| is_duplicated(dummy_a, val)
			|| !dlist_add_prev(dummy_a, val, 0))
			return (false);
		i++;
	}
	return (true);
}
