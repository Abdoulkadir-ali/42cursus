/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:22:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	max_val(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	calculate_cost(t_stacks *s, t_node_meta *meta_a, int to_b)
{
	t_cost_ctx	ctx;
	t_node_meta	*meta_b;
	int			len_src;
	int			len_tgt;

	if (!meta_a || !meta_a->target)
		return ;
	if (to_b)
	{
		len_src = ft_size(s->a);
		len_tgt = ft_size(s->b);
	}
	else
	{
		len_src = ft_size(s->b);
		len_tgt = ft_size(s->a);
	}
	meta_b = &meta_a->target->meta;
	ctx.meta_a = meta_a;
	ctx.meta_b = meta_b;
	ctx.cost_a = meta_a->index;
	ctx.cost_b = meta_b->index;
	if (ctx.meta_a->above_median && ctx.meta_b->above_median)
		ctx.meta_a->push_cost = max_val(ctx.cost_a, ctx.cost_b);
	else if (!ctx.meta_a->above_median && !ctx.meta_b->above_median)
		ctx.meta_a->push_cost = max_val(len_src - ctx.cost_a, len_tgt - ctx.cost_b);
	else if (ctx.meta_a->above_median && !ctx.meta_b->above_median)
		ctx.meta_a->push_cost = ctx.cost_a + (len_tgt - ctx.cost_b);
	else
		ctx.meta_a->push_cost = (len_src - ctx.cost_a) + ctx.cost_b;
}

void	set_cheapest_node(t_nodes *stack)
{
	t_nodes	*curr;
	t_nodes	*cheapest;
	long	min_cost;
	int		size;

	if (!stack)
		return ;
	curr = stack;
	cheapest = stack;
	min_cost = LONG_MAX;
	size = ft_size(stack);
	while (size--)
	{
		curr->meta.is_cheapest = 0;
		if (curr->meta.push_cost < min_cost)
		{
			min_cost = curr->meta.push_cost;
			cheapest = curr;
		}
		curr = curr->next;
	}
	if (cheapest)
		cheapest->meta.is_cheapest = 1;
}
