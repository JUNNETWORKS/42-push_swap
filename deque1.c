#include <stdlib.h>
#include "deque.h"
#include "utils.h"

t_deque	*deque_create(long cap)
{
	t_deque	*deque;

	deque = malloc(sizeof(t_deque));
	if (!deque)
		return (NULL);
	deque->cap = cap;
	deque->arr = malloc(sizeof(long) * deque->cap);
	if (!deque->arr)
		return (NULL);
	deque->head_idx = 0;
	deque->tail_idx = 0;
	return (deque);
}

long	deque_size(t_deque *deque)
{
	if (deque->head_idx <= deque->tail_idx)
		return (deque->tail_idx - deque->head_idx);
	return (deque->cap - deque->head_idx + deque->tail_idx);
}

void	deque_expand(t_deque *deque)
{
	long	*new_arr;
	long	*tmp;
	int		i;

	new_arr = malloc(sizeof(long) * (deque->cap * 2));
	if (!new_arr)
		exit(1);
	i = 0;
	while (mod(deque->head_idx + i, deque->cap) != deque->tail_idx)
	{
		new_arr[i] = deque->arr[mod(deque->head_idx + i, deque->cap)];
		i++;
	}
	tmp = deque->arr;
	deque->arr = new_arr;
	deque->cap = deque->cap * 2;
	deque->head_idx = 0;
	deque->tail_idx = i;
	free(tmp);
}

void	deque_expand_if_needed(t_deque *deque)
{
	if (mod(deque->tail_idx + 1, deque->cap) == deque->head_idx)
		deque_expand(deque);
}

void	deque_free(t_deque **deque)
{
	if (!deque || !*deque)
		return ;
	free((*deque)->arr);
	free(*deque);
	*deque = NULL;
}
