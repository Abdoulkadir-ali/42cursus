/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:57:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	max_val(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	calculate_cost(t_stacks *s, t_node_meta *meta_a)
{
	t_cost_ctx	ctx;
	t_node_meta	*meta_b;
	int			len_a;
	int			len_b;

	if (!meta_a || !meta_a->target)
		return ;
	len_a = ft_size(s->a);
	len_b = ft_size(s->b);
	meta_b = &meta_a->target->meta;
	ctx.meta_a = meta_a;
	ctx.meta_b = meta_b;
	ctx.cost_a = meta_a->index;
	ctx.cost_b = meta_b->index;
	if (ctx.meta_a->above_median && ctx.meta_b->above_median)
		ctx.meta_a->push_cost = max_val(ctx.cost_a, ctx.cost_b);
	else if (!ctx.meta_a->above_median && !ctx.meta_b->above_median)
		ctx.meta_a->push_cost = max_val(len_a - ctx.cost_a, len_b - ctx.cost_b);
	else if (ctx.meta_a->above_median && !ctx.meta_b->above_median)
		ctx.meta_a->push_cost = ctx.cost_a + (len_b - ctx.cost_b);
	else
		ctx.meta_a->push_cost = (len_a - ctx.cost_a) + ctx.cost_b;
}

void	set_cheapest_node(t_stacks *s)
{
	t_set_cheapest_ctx	ctx;

	if (!s->b)
		return ;
	ctx.len_b = ft_size(s->b);
	ctx.curr = s->b;
	ctx.cheapest = s->b;
	ctx.cheapest_cost = INT_MAX;
	ctx.size = ctx.len_b;
	while (ctx.size)
	{
		ctx.curr->meta.is_cheapest = 0;
		if (ctx.curr->meta.push_cost < ctx.cheapest_cost)
		{
			ctx.cheapest_cost = ctx.curr->meta.push_cost;
			ctx.cheapest = ctx.curr;
		}
		ctx.curr = ctx.curr->next;
		ctx.size--;
	}
	if (ctx.cheapest)
		ctx.cheapest->meta.is_cheapest = 1;
}
