#include <stdio.h>
#include "libft/libft.h"
#include "push_swap.h"

/*
 * Take the first element at the top of b and put it at the top of a.
 * Do nothing if b is empty.
 */
void	push_a(t_dlist *dummy_a, t_dlist *dummy_b)
{
	t_dlist	*top;

	top = dlist_pop(dummy_b);
	if (!top)
		return ;
	dlist_push(dummy_a, top);
}

/*
 * Take the first element at the top of a and put it at the top of b.
 * Do nothing if b is empty.
 */
void	push_b(t_dlist *dummy_a, t_dlist *dummy_b)
{
	t_dlist	*top;

	top = dlist_pop(dummy_a);
	if (!top)
		return ;
	dlist_push(dummy_b, top);
}

void	print_stacks(t_dlist *dummy_a, t_dlist *dummy_b)
{
	int		len_a;
	int		len_b;
	t_dlist	*current_a;
	t_dlist	*current_b;

	len_a = dlist_len(dummy_a);
	len_b = dlist_len(dummy_b);
	current_a = dummy_a->next;
	current_b = dummy_b->next;
	while (len_a > 0 || len_b > 0)
	{
		if (len_a > 0 && len_a >= len_b)
		{
			printf("|%4d|", current_a->val);
			current_a = current_a->next;
			len_a--;
		}
		else
			printf("|    |");
		printf("  ");
		if (len_b > 0 && len_b > len_a)
		{
			printf("|%4d|", current_b->val);
			current_b = current_b->next;
			len_b--;
		}
		else
			printf("|    |");
		printf("\n");
	}
	printf(" ̄ ̄ ̄ ̄ ̄ ̄   ̄ ̄ ̄ ̄ ̄ ̄\n");
	printf("  a       b   \n");
}
