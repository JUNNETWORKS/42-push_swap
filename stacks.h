#ifndef STACKS_H
# define STACKS_H

# include <stdbool.h>
# include "dlist.h"

enum e_operations {
	OP_SA = 0x10,
	OP_SB = 0x11,
	OP_SS = 0x12,
	OP_PA = 0x13,
	OP_PB = 0x14,
	OP_RA = 0x15,
	OP_RB = 0x16,
	OP_RR = 0x17,
	OP_RRA = 0x18,
	OP_RRB = 0x19,
	OP_RRR = 0x1a
};

enum e_stacks{
	STACK_A = 0,
	STACK_B = 1,
};

typedef struct s_stacks {
	t_dlist		*dummy_a;
	t_dlist		*dummy_b;
	t_dlist		*dummy_ops;
	int			*sorted_arr;
	int			size;
	int			sorted_len;
	int			pivot_count;
}				t_stacks;

typedef struct s_dfs {
	t_dlist		*dummy_tmp_ops;
	t_dlist		*dummy_ops;
	int			best_turn;
	int			stack_size;
	int			push2another_count;
}				t_dfs;

/* stacks */
t_dlist		*get_stack_from_id(t_stacks *stacks, enum e_stacks stack_id);
void		stacks_push2another(t_stacks *stacks, enum e_stacks src_stack_id);
void		stacks_swap(t_stacks *stacks, enum e_stacks stack_id);
void		stacks_rotate(t_stacks *stacks, enum e_stacks stack_id);
void		stacks_rrotate(t_stacks *stacks, enum e_stacks stack_id);

/* sort */
void		sort_stacks(t_stacks *stacks);
void		sort_2_elements(t_stacks *stacks, enum e_stacks stack_id);
void		sort_3_elements(t_stacks *stacks, enum e_stacks stack_id);
void		sort_le_3_elements(t_stacks *stacks, enum e_stacks stack_id);
void		sort_le_6_elements(t_stacks *stacks, enum e_stacks stack_id);
void		sort_stack_dfs(t_stacks *stacks,
				t_dfs *dfs_data, enum e_stacks stack_id, int turn);
void		sort_many_elements(t_stacks *stacks, enum e_stacks stack_id);
void		partition_stack_a(t_stacks *stacks);
void		partition_stack_b_and_merge2a(t_stacks *stacks);
bool		is_stack_sorted_asc(t_dlist *dummy, int len);
bool		is_stack_sorted_des(t_dlist *dummy, int len);

/* operations */
void		optimize_operations(t_stacks *stacks);
const char	*get_operation_str(enum e_operations op);
void		print_all_operations(t_stacks *stacks);
void		undo_operation(t_stacks *stacks,
				t_dlist *dummy_ops, enum e_operations op);
void		do_operation(t_stacks *stacks,
				t_dlist *dummy_ops, enum e_operations op);
bool		is_valid_operation(t_stacks *stacks,
				t_dlist *dummy_ops, enum e_operations op);

#endif
