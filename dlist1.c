#include <limits.h>
#include "libft/libft.h"
#include "dlist.h"

t_dlist	*create_dlist(int val)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->val = val;
	new->group = -1;
	new->next = new;
	new->prev = new;
	return (new);
}

t_dlist	*dlist_add_next(t_dlist *dummy, int val, int group)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		exit(1);
	new->val = val;
	new->group = group;
	dummy->next->prev = new;
	new->next = dummy->next;
	new->prev = dummy;
	dummy->next = new;
	return (new);
}

t_dlist	*dlist_add_prev(t_dlist *dummy, int val, int group)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		exit(1);
	new->val = val;
	new->group = group;
	dummy->prev->next = new;
	new->prev = dummy->prev;
	new->next = dummy;
	dummy->prev = new;
	return (new);
}

int	dlist_len(t_dlist *dummy)
{
	t_dlist	*current;
	int		len;

	current = dummy->next;
	len = 0;
	while (current != dummy)
	{
		current = current->next;
		len++;
	}
	return (len);
}

void	free_dlist(t_dlist *dummy)
{
	t_dlist	*current;
	t_dlist	*tmp;

	current = dummy->next;
	while (current != dummy)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(dummy);
}
