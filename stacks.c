#include <unistd.h>
#include "libft/libft.h"
#include "stacks.h"

t_dlist	*get_stack_from_id(t_stacks *stacks, enum e_stacks stack_id)
{
	if (stack_id == STACK_A)
		return (stacks->dummy_a);
	else
		return (stacks->dummy_b);
}

const char	*get_operation_str(enum e_operations op)
{
	if (op == OP_SA)
		return (ft_strdup("sa"));
	else if (op == OP_SB)
		return (ft_strdup("sb"));
	else if (op == OP_SS)
		return (ft_strdup("ss"));
	else if (op == OP_PA)
		return (ft_strdup("pa"));
	else if (op == OP_PB)
		return (ft_strdup("pb"));
	else if (op == OP_RA)
		return (ft_strdup("ra"));
	else if (op == OP_RB)
		return (ft_strdup("rb"));
	else if (op == OP_RR)
		return (ft_strdup("rr"));
	else if (op == OP_RRA)
		return (ft_strdup("rra"));
	else if (op == OP_RRB)
		return (ft_strdup("rrb"));
	else if (op == OP_RRR)
		return (ft_strdup("rrr"));
	return ft_strdup("unknown operation");
}
