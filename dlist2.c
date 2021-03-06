#include <limits.h>
#include "libft/libft.h"
#include "dlist.h"
#include "utils.h"

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

void	dlist_del_prev(t_dlist *dummy)
{
	t_dlist	*current;

	current = dummy->prev;
	if (current == dummy)
		return ;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	free(current);
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

int	dlist_get_mid_value(t_dlist *dummy, int len)
{
	int		*arr;
	int		mid_v;
	int		i;
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

int	dlist_get_min_value(t_dlist *dummy, int len)
{
	int		min_v;
	int		i;
	t_dlist	*current;

	i = 0;
	min_v = INT_MAX;
	current = dummy->next;
	while (current != dummy && i++ < len)
	{
		if (current->val < min_v)
			min_v = current->val;
		current = current->next;
	}
	return (min_v);
}
