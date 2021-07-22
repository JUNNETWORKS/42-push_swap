#include <stdlib.h>
#include "dlist.h"

t_dlist	*dlist_duplicate(t_dlist *dummy_src)
{
	t_dlist	*dummy_new;
	t_dlist	*current;

	dummy_new = create_dlist(0);
	if (!dummy_new)
		exit(1);
	current = dummy_src->next;
	while (current != dummy_src)
	{
		if (!dlist_add_prev(dummy_new, current->val, current->group))
			exit(1);
		current = current->next;
	}
	return (dummy_new);
}

/*
 * The direction of the arrow represents next.
 *
 *    dst    +     src
 *    n     p         n     p
 * d--1->2->3-  +  d->4->5->6-
 * |         |     ^         |
 * |         |     |         |
 * -----------     -----------
 *
 * result dst
 * d->1->2->3->4->5->6-
 * ^                  |
 * |                  |
 * --------------------
 */
t_dlist	*dlist_concat_prev(t_dlist *dummy_dst, t_dlist *dummy_src)
{
	t_dlist	*dummy_src_copy;

	if (dlist_len(dummy_src) == 0)
		return (dummy_dst);
	dummy_src_copy = dlist_duplicate(dummy_src);
	dummy_dst->prev->next = dummy_src_copy->next;
	dummy_src_copy->next->prev = dummy_dst->prev;
	dummy_dst->prev = dummy_src_copy->prev;
	dummy_src_copy->prev->next = dummy_dst;
	free(dummy_src_copy);
	return (dummy_dst);
}
