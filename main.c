#include <stdio.h>
#include "libft/libft.h"

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

static int	*parse_argv(char **argv)
{
	int	*num_arr;
	int	i;

	num_arr = malloc(sizeof(int) * ptrarr_len((void **)argv));
	if (!num_arr)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		if (!my_atoi(argv[i], &num_arr[i]))
		{
			free(num_arr);
			return (NULL);
		}
		i++;
	}
	return (num_arr);
}

int	main(int argc, char **argv)
{
	int	*num_arr;

	if (argc <= 1)
	{
		printf("Invalid argc\n");
		return (1);
	}
	num_arr = parse_argv(argv + 1);
	if (!num_arr)
	{
		printf("nums are invalid\n");
		return (1);
	}
	for (int i = 0; i < argc - 1; i++)
		printf("nums[%d]: %d\n", i, num_arr[i]);
	printf("HELLO PUSH_SWAP\n");
}
