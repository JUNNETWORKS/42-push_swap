#ifndef STACKS_H
# define STACKS_H

# include <stdbool.h>
# include "dlist.h"

enum e_operations {
	OP_SA = 0x10,
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

enum e_stacks{
	STACK_A = 0,
	STACK_B = 1,
};

typedef struct	s_stacks {
	t_dlist	*dummy_a;
	t_dlist	*dummy_b;
	t_dlist	*dummy_ops;
	int		next_val;
	int		sorted_len;
	int		pivot_count;  // 現在行われたB2Aのpivotの回数
}				t_stacks;

t_dlist	*get_stack_from_id(t_stacks *stacks, enum e_stacks stack_id);
void	stacks_push2another(t_stacks *stacks, enum e_stacks src_stack_id);
void	stacks_swap(t_stacks *stacks, enum e_stacks stack_id);
void	stacks_rotate(t_stacks *stacks, enum e_stacks stack_id);
void	stacks_rrotate(t_stacks *stacks, enum e_stacks stack_id);

void	print_stacks(t_stacks *stacks);
const char	*get_operation_str(enum e_operations op);
void	sort_stacks(t_stacks *stacks);
void	sort_2_elements(t_stacks *stacks, enum e_stacks stack_id);
void	sort_3_elements(t_stacks *stacks, enum e_stacks stack_id);
void	sort_le_3_elements(t_stacks *stacks, enum e_stacks stack_id);
void	sort_le_6_elements(t_stacks *stacks, enum e_stacks stack_id);
void	sort_many_elements(t_stacks *stacks, enum e_stacks stack_id);
bool	is_stack_sorted_asc(t_dlist *dummy, int len);
bool	is_stack_sorted_des(t_dlist *dummy, int len);
void	print_all_operations(t_stacks *stacks);

void	optimize_operations(t_stacks *stacks);

#endif
