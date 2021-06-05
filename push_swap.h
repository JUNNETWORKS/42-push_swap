#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

enum e_operations {
	OP_SA = 0x0,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR
};

/* t_dlist is used as stack
 *
 * dummy->next is top of stack
 * dummy->prev is bottom of stack
 */
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
void	dlist_swap_first2(t_dlist *dummy);
void	dlist_rotate(t_dlist *dummy);
void	dlist_rrotate(t_dlist *dummy);

#endif
