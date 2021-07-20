#ifndef DLIST_H
# define DLIST_H

# include <stdbool.h>

/* t_dlist is used as stack
 *
 * dummy->next is top of stack
 * dummy->prev is bottom of stack
 */
typedef struct		s_dlist {
	int				val;
	int				group;  // この値が何回BからAに移動されたかを記録する. (for quick_sort)
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist	*create_dlist(int val);
t_dlist	*dlist_add_next(t_dlist *dummy, int val);
t_dlist	*dlist_add_prev(t_dlist *dummy, int val);
int		dlist_len(t_dlist *dummy);
void	free_dlist(t_dlist *dummy);
bool	dlist_at(t_dlist *dummy, int idx, int *val);
int		dlist_get_min_val_idx(t_dlist *dummy);
int		*dlist2arr(t_dlist *dummy);
int		dlist_get_mid_value(t_dlist *dummy, int len);
t_dlist	*dlist_pop(t_dlist *dummy);
void	dlist_push(t_dlist *dummy, t_dlist *element);
void	dlist_swap_first2(t_dlist *dummy);
void	dlist_rotate(t_dlist *dummy);
void	dlist_rrotate(t_dlist *dummy);
int		get_head_group_len(t_dlist *dummy);

#endif
