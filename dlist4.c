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
		if (!dlist_add_prev(dummy_new, current->val))
			exit(1);
		current = current->next;
	}
	return (dummy_new);
}
