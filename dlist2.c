#include <limits.h>
#include "libft/libft.h"
#include "push_swap.h"

bool	dlist_at(t_dlist *dummy, int idx, int *val)
{
	int		i;
	t_dlist	*current;

	i = 0;
	current = dummy->next;
	while (current != dummy)
	{
		if (i == idx)
		{
			*val = current->val;
			return (true);
		}
		current = current->next;
		i++;
	}
	return (false);
}

int	dlist_get_min_val_idx(t_dlist *dummy)
{
	int		i;
	int		min_val;
	int		min_idx;
	t_dlist	*current;

	min_val = INT_MAX;
	min_idx = -1;
	current = dummy->next;
	i = 0;
	while (current != dummy)
	{
		if (current->val < min_val)
		{
			min_val = current->val;
			min_idx = i;
		}
		current = current->next;
		i++;
	}
	return (min_idx);
}

int	*dlist2arr(t_dlist *dummy)
{
	int		*arr;
	int		len;
	int		i;
	t_dlist	*current;

	len = dlist_len(dummy);
	arr = malloc(sizeof(int) * len);
	if (!arr)
		return (NULL);
	i = 0;
	current = dummy->next;
	while (i < len)
	{
		arr[i] = current->val;
		i++;
		current = current->next;
	}
	return (arr);
}

int	dlist_get_mid_value(t_dlist *dummy, int len)
{
	int	*arr;
	int	mid_v;
	int	i;
	t_dlist	*current;

	arr = malloc(sizeof(int) * len);
	if (!arr)
		exit(1);
	i = 0;
	current = dummy->next;
	while (i < len)
	{
		arr[i++] = current->val;
		current = current->next;
	}
	sort_arr(arr, len);
	mid_v = arr[len / 2];
	free(arr);
	return (mid_v);
}
