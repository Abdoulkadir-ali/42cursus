/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:10:43 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/27 19:45:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_indices(t_nodes *stack, int len)
{
	int		i;
	t_nodes	*curr;

	i = 0;
	curr = stack;
	while (i < len && curr)
	{
		curr->meta.index = i;
		curr->meta.above_median = (i <= len / 2);
		curr = curr->next;
		i++;
	}
}

static void	process_b_stack(t_push_swap_ctx *ctx, t_stacks *s)
{
	while (s->b)
	{
		ctx->len_a = ft_size(s->a);
		ctx->len_b = ft_size(s->b);
		init_indices(s->a, ctx->len_a);
		init_indices(s->b, ctx->len_b);
		set_b_targets(s);
		ctx->cheap = s->b;
		ctx->size = ctx->len_b;
		while (ctx->size--)
		{
			calculate_cost(s, &ctx->cheap->meta, 0);
			ctx->cheap = ctx->cheap->next;
		}
		set_cheapest_node(s->b);
		ctx->cheap = s->b;
		ctx->size = ctx->len_b;
		while (ctx->size-- && !ctx->cheap->meta.is_cheapest)
			ctx->cheap = ctx->cheap->next;
		if (ctx->cheap)
			execute_moves(s, ctx->cheap);
	}
}

static void	finalize_a_stack(t_push_swap_ctx *ctx, t_stacks *s)
{
	if (!s->a)
		return ;
	init_indices(s->a, ft_size(s->a));
	ctx->min_node = find_extreme(s->a);
	if (!ctx->min_node)
		return ;
	if (ctx->min_node->meta.above_median)
		while (s->a != ctx->min_node)
			ra(s);
	else
		while (s->a != ctx->min_node)
			rra(s);
}

void	push_swap(t_stacks *s)
{
	t_push_swap_ctx	ctx;
	int				size;

	if (is_sorted(s->a))
		return ;
	size = ft_size(s->a);
	if (size == 2)
	{
		if (s->a->v > s->a->next->v)
			sa(s);
		return ;
	}
	if (size == 3)
	{
		sort_three(s);
		return ;
	}
	turk_algorithm(s);
	process_b_stack(&ctx, s);
	finalize_a_stack(&ctx, s);
}
