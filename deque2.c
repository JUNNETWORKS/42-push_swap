#include <stdlib.h>
#include <stdbool.h>
#include "deque.h"
#include "dlist.h"
#include "utils.h"

void	deque_add_front(t_deque *deque, long value)
{
	deque_expand_if_needed(deque);
	deque->head_idx = mod(deque->head_idx - 1, deque->cap);
	deque->arr[deque->head_idx] = value;
}

void	deque_add_back(t_deque *deque, long value)
{
	deque_expand_if_needed(deque);
	deque->arr[deque->tail_idx] = value;
	deque->tail_idx = mod(deque->tail_idx + 1, deque->cap);
}

bool	deque_pop_front(t_deque *deque, long *value)
{
	if (deque_size(deque) == 0)
		return (false);
	*value = deque->arr[deque->head_idx];
	deque->head_idx = mod(deque->head_idx + 1, deque->cap);
	return (true);
}

bool	deque_pop_back(t_deque *deque, long *value)
{
	if (deque_size(deque) == 0)
		return (false);
	deque->tail_idx = mod(deque->tail_idx - 1, deque->cap);
	*value = deque->arr[deque->tail_idx];
	return (true);
}

t_dlist	*deque2dlist(t_deque *deque)
{
	t_dlist	*dummy;
	int		i;

	dummy = create_dlist(0);
	i = deque->head_idx;
	while (i != deque->tail_idx)
	{
		dlist_add_prev(dummy, deque->arr[i], 0);
		i = mod(i + 1, deque->cap);
	}
	return (dummy);
}
