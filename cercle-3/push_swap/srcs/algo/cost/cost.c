/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 00:37:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_cost(t_stacks *s, t_node_meta *meta_a, int to_b)
{
	t_cost_ctx	ctx;
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
	init_cost_ctx(&ctx, meta_a, len_src, len_tgt);
	compute_push_cost(&ctx);
}

static void	scan_for_cheapest(t_nodes *stack, t_nodes **cheapest,
		long *min_cost)
{
	t_nodes	*curr;
	int		size;

	curr = stack;
	size = ft_size(stack);
	while (size--)
	{
		curr->meta.is_cheapest = 0;
		if (curr->meta.push_cost < *min_cost)
		{
			*min_cost = curr->meta.push_cost;
			*cheapest = curr;
		}
		curr = curr->next;
	}
}

void	set_cheapest_node(t_nodes *stack)
{
	t_nodes	*cheapest;
	long	min_cost;

	if (!stack)
		return ;
	cheapest = stack;
	min_cost = LONG_MAX;
	scan_for_cheapest(stack, &cheapest, &min_cost);
	if (cheapest)
		cheapest->meta.is_cheapest = 1;
}
