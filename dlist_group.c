#include "dlist.h"

int	get_head_group_len(t_dlist *dummy)
{
	t_dlist *current;
	int group;
	int group_len;

	current = dummy->next;
	group = current->group;
	group_len = 0;
	while (current->group == group)
	{
		current = current->next;
		group_len++;
	}
	return (group_len);
}
