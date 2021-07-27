#include <limits.h>
#include "libft/libft.h"
#include "dlist.h"

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
	if (!dummy || !element)
		return ;
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
