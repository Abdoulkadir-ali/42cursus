/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:51:13 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:42:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	cmp(int a, int b)
{
	if (ASCENDING)
		return (a <= b);
	else
		return (a >= b);
}

int	is_sorted(t_nodes *stack)
{
	t_nodes	*curr;
	int		prev_val;
	int		curr_val;
	int		size;

	if (!stack)
		return (1);
	size = ft_size(stack);
	if (size <= 1)
		return (1);
	prev_val = stack->v;
	curr = stack->next;
	while (size)
	{
		curr_val = curr->v;
		if (!cmp(prev_val, curr_val))
			return (0);
		prev_val = curr_val;
		curr = curr->next;
		size--;
	}
	return (1);
}

static void	sort_three(t_stacks *s)
{
	t_sort_three_ctx	ctx;

	ctx.v1 = s->a->v;
	ctx.v2 = s->a->next->v;
	ctx.v3 = s->a->next->next->v;
	if (ctx.v1 > ctx.v2 && ctx.v2 < ctx.v3 && ctx.v1 < ctx.v3)
		sa(s);
	else if (ctx.v1 > ctx.v2 && ctx.v2 > ctx.v3)
	{
		sa(s);
		rra(s);
	}
	else if (ctx.v1 > ctx.v2 && ctx.v2 < ctx.v3 && ctx.v1 > ctx.v3)
		ra(s);
	else if (ctx.v1 < ctx.v2 && ctx.v2 > ctx.v3 && ctx.v1 < ctx.v3)
	{
		sa(s);
		ra(s);
	}
	else if (ctx.v1 < ctx.v2 && ctx.v2 > ctx.v3 && ctx.v1 > ctx.v3)
		rra(s);
}

void	turk_algorithm(t_stacks *s)
{
	while (ft_size(s->a) > 3)
		pb(s);
	sort_three(s);
}
