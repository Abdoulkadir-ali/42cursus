/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:35:13 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:32:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_both(t_stacks *s, t_nodes *cheap, int is_above)
{
	while (s->b != cheap && s->a != cheap->meta.target)
	{
		if (is_above)
			rr(s);
		else
			rrr(s);
	}
}

static void	prep_for_push(t_stacks *s, t_nodes *node, t_node_meta *meta,
		char stack)
{
	if (stack == 'a')
	{
		while (s->a != node)
		{
			if (meta->above_median)
				ra(s);
			else
				rra(s);
		}
	}
	else if (stack == 'b')
	{
		while (s->b != node)
		{
			if (meta->above_median)
				rb(s);
			else
				rrb(s);
		}
	}
}

void	execute_moves(t_stacks *s, t_nodes *cheap)
{
	t_moves_ctx	ctx;

	ctx.meta_cheap = &cheap->meta;
	ctx.meta_target = &cheap->meta.target->meta;
	if (ctx.meta_cheap->above_median && ctx.meta_target->above_median)
		rotate_both(s, cheap, 1);
	else if (!ctx.meta_cheap->above_median && !ctx.meta_target->above_median)
		rotate_both(s, cheap, 0);
	prep_for_push(s, cheap, ctx.meta_cheap, 'b');
	prep_for_push(s, cheap->meta.target, ctx.meta_target, 'a');
	pa(s);
}
