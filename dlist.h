#ifndef DLIST_H
# define DLIST_H

# include <stdbool.h>

/* t_dlist is used as stack
 *
 * dummy->next is top of stack
 * dummy->prev is bottom of stack
 *
 * group: Record the number of times this value is moved from B to A.
 *   (for quick_sort)
 */
typedef struct s_dlist {
	int				val;
	int				group;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist	*create_dlist(int val);
t_dlist	*dlist_add_next(t_dlist *dummy, int val, int group);
t_dlist	*dlist_add_prev(t_dlist *dummy, int val, int group);
int		dlist_len(t_dlist *dummy);
void	free_dlist(t_dlist *dummy);
void	dlist_del_prev(t_dlist *dummy);
bool	dlist_at(t_dlist *dummy, int idx, int *val);
int		dlist_get_min_val_idx(t_dlist *dummy);
int		*dlist2arr(t_dlist *dummy);
t_dlist	*dlist_duplicate(t_dlist *dummy_src);
t_dlist	*dlist_concat_prev(t_dlist *dummy_dst, t_dlist *dummy_src);
int		dlist_get_mid_value(t_dlist *dummy, int len);
int		dlist_get_min_value(t_dlist *dummy, int len);
t_dlist	*dlist_pop(t_dlist *dummy);
void	dlist_push(t_dlist *dummy, t_dlist *element);
void	dlist_swap_first2(t_dlist *dummy);
void	dlist_rotate(t_dlist *dummy);
void	dlist_rrotate(t_dlist *dummy);
int		get_head_group_len(t_dlist *dummy);

#endif
