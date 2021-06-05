#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct		s_dlist {
	int				val;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

t_dlist	*create_dlist(int val);
t_dlist	*dlist_add_next(t_dlist *dummy, int val);
t_dlist	*dlist_add_prev(t_dlist *dummy, int val);
int		dlist_len(t_dlist *dummy);
void	free_dlist(t_dlist *dummy);
t_dlist	*dlist_pop(t_dlist *dummy);
void	dlist_push(t_dlist *dummy, t_dlist *element);

#endif
