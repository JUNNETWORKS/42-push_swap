#ifndef STACKS_H
# define STACKS_H

# include "dlist.h"

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

typedef struct	s_stacks {
	t_dlist	*dummy_a;
	t_dlist	*dummy_b;
	t_dlist	*dummy_ops;
}				t_stacks;

void	push_a(t_stacks *stacks);
void	push_b(t_stacks *stacks);
void	swap_a(t_stacks *stacks);
void	swap_b(t_stacks *stacks);
void	rotate_a(t_stacks *stacks);
void	rotate_b(t_stacks *stacks);
void	rrotate_a(t_stacks *stacks);
void	rrotate_b(t_stacks *stacks);

void	print_stacks(t_stacks *stacks);
void	sort_stacks(t_stacks *stacks);
void	sort_le_3_elements(t_stacks *stacks);
void	sort_le_6_elements(t_stacks *stacks);
void	sort_many_elements(t_stacks *stacks);
bool	is_stack_sorted_asc(t_dlist *dummy, int len);
bool	is_stack_sorted_des(t_dlist *dummy, int len);

#endif
