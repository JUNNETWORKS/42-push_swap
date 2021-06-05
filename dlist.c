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

t_dlist	*dlist_pop(t_dlist *dummy)
{
	t_dlist	*element;

	element = dummy->next;
	dummy->next = element->next;
	element->next->prev = dummy;
	return (element);
}

void	dlist_push(t_dlist *dummy, t_dlist *element)
{
	dummy->next->prev = element;
	element->next = dummy->next;
	element->prev = dummy;
	dummy->next = element;
}
