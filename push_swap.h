#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "dlist.h"

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

bool	parse_argv(t_dlist *dummy_a, char **argv);
void	push_a(t_dlist *dummy_a, t_dlist *dummy_b);
void	push_b(t_dlist *dummy_a, t_dlist *dummy_b);
void	print_stacks(t_dlist *dummy_a, t_dlist *dummy_b);
void	sort_stacks(t_dlist *dummy_a, t_dlist *dummy_b);
void	sort_le_3_elements(t_dlist *dummy_a);
void	sort_le_6_elements(t_dlist *dummy_a, t_dlist *dummy_b);
void	sort_many_elements(t_dlist *dummy_a, t_dlist *dummy_b);
bool	is_stack_sorted_asc(t_dlist *dummy, int len);
bool	is_stack_sorted_des(t_dlist *dummy, int len);

#endif
