#ifndef DEQUE_H
# define DEQUE_H

# include <stdbool.h>
# include "dlist.h"
# define DEFAULT_CAP 1024

/*
 * [_, _, 1,    2,   _,   _, _]
 *       head       tail
 */
typedef struct s_deque {
	long	*arr;
	long	cap;
	long	head_idx;
	long	tail_idx;
}			t_deque;

t_deque	*deque_create(long cap);
void	deque_expand(t_deque *deque);
void	deque_expand_if_needed(t_deque *deque);
void	deque_add_front(t_deque *deque, long value);
void	deque_add_back(t_deque *deque, long value);
bool	deque_pop_front(t_deque *deque, long *value);
bool	deque_pop_back(t_deque *deque, long *value);
long	deque_size(t_deque *deque);
void	deque_free(t_deque **deque);
t_dlist	*deque2dlist(t_deque *deque);

#endif
