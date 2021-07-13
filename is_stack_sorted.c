#include <stdbool.h>
#include "push_swap.h"


bool	is_stack_sorted_asc(t_dlist *dummy, int len)
{
	t_dlist *current;
	int max;
	int i;

	current = dummy->next;
	max = current->val;
	i = 0;
	if (len < 0)
		len = dlist_len(dummy);
	while (i < len)
	{
		if (current->val < max)
			return (false);
		max = current->val;
		current = current->next;
		i++;
	}
	return (true);
}

bool	is_stack_sorted_des(t_dlist *dummy, int len)
{
	t_dlist *current;
	int min;
	int i;

	current = dummy->next;
	min = current->val;
	i = 0;
	if (len < 0)
		len = dlist_len(dummy);
	while (i < len)
	{
		if (current->val > min)
			return (false);
		min = current->val;
		current = current->next;
		i++;
	}
	return (true);
}
