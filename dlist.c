#include "libft/libft.h"
#include "push_swap.h"

t_dlist	*create_dlist(int val)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->val = val;
	new->next = new;
	new->prev = new;
	return (new);
}

t_dlist	*dlist_add_next(t_dlist *dummy, int val)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->val = val;
	dummy->next->prev = new;
	new->next = dummy->next;
	new->prev = dummy;
	dummy->next = new;
	return (new);
}

t_dlist	*dlist_add_prev(t_dlist *dummy, int val)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->val = val;
	dummy->prev->next = new;
	new->prev = dummy->prev;
	new->next = dummy;
	dummy->prev = new;
	return (new);
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
