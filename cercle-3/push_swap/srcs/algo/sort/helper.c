/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:01:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 00:33:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_both(t_stacks *s, t_nodes *cheap)
{
	if (cheap->meta.above_median && cheap->meta.target->meta.above_median)
	{
		while (s->a != cheap && s->b != cheap->meta.target)
			rr(s);
	}
	else if (!cheap->meta.above_median
		&& !cheap->meta.target->meta.above_median)
	{
		while (s->a != cheap && s->b != cheap->meta.target)
			rrr(s);
	}
}

static void	rotate_a(t_stacks *s, t_nodes *cheap)
{
	while (s->a != cheap)
	{
		if (cheap->meta.above_median)
			ra(s);
		else
			rra(s);
	}
}

static void	rotate_b(t_stacks *s, t_nodes *target)
{
	while (s->b != target)
	{
		if (target->meta.above_median)
			rb(s);
		else
			rrb(s);
	}
}

void	move_a_to_b(t_stacks *s, t_nodes *cheap)
{
	if (!cheap || !cheap->meta.target)
		return ;
	rotate_both(s, cheap);
	rotate_a(s, cheap);
	rotate_b(s, cheap->meta.target);
	pb(s);
}

t_nodes	*find_cheapest(t_nodes *stack)
{
	t_nodes	*curr;
	t_nodes	*cheapest;
	long	min_cost;
	int		size;

	cheapest = NULL;
	min_cost = LONG_MAX;
	curr = stack;
	size = ft_size(stack);
	while (size--)
	{
		if (curr->meta.push_cost < min_cost)
		{
			min_cost = curr->meta.push_cost;
			cheapest = curr;
		}
		curr = curr->next;
	}
	return (cheapest);
}
