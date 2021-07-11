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

t_dlist	*dlist_pop(t_dlist *dummy)
{
	t_dlist	*element;

	if (!dlist_len(dummy))
		return (NULL);
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

/*
 * Swap the first 2 elements at the top of stack
 *
 * Do nothing if dummy has only one or no elements.
 */
void	dlist_swap_first2(t_dlist *dummy)
{
	t_dlist	*first;
	t_dlist	*second;

	if (dlist_len(dummy) < 2)
		return ;
	first = dummy->next;
	second = first->next;

	dummy->next = second;
	second->prev = dummy;
	first->prev = second;
	first->next = second->next;
	second->next->prev = first;
	second->next = first;
}

/*
 * Shift up all elements of the stack by 1.
 * The first element becomes the last one.
 */
void	dlist_rotate(t_dlist *dummy)
{
	t_dlist	*top;

	top = dummy->next;
	dummy->next = top->next;
	dummy->next->prev = dummy;
	dummy->prev->next = top;
	top->prev = dummy->prev;
	top->next = dummy;
	dummy->prev = top;
}

/*
 * Shift down all elements of the stack by 1.
 * The last element becomes the first one.
 */
void	dlist_rrotate(t_dlist *dummy)
{
	t_dlist	*bottom;

	bottom = dummy->prev;
	bottom->prev->next = dummy;
	dummy->prev = bottom->prev;
	bottom->next = dummy->next;
	bottom->prev = dummy;
	dummy->next->prev = bottom;
	dummy->next = bottom;
}
