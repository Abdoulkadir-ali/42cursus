/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 00:37:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max_val(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	init_cost_ctx(t_cost_ctx *ctx, t_node_meta *meta_a, int len_src,
		int len_tgt)
{
	t_node_meta	*meta_b;

	meta_b = &meta_a->target->meta;
	ctx->meta_a = meta_a;
	ctx->meta_b = meta_b;
	ctx->cost_a = meta_a->index;
	ctx->cost_b = meta_b->index;
	ctx->len_src = len_src;
	ctx->len_tgt = len_tgt;
}

void	compute_push_cost(t_cost_ctx *ctx)
{
	if (ctx->meta_a->above_median && ctx->meta_b->above_median)
		ctx->meta_a->push_cost = max_val(ctx->cost_a, ctx->cost_b);
	else if (!ctx->meta_a->above_median && !ctx->meta_b->above_median)
		ctx->meta_a->push_cost = max_val(ctx->len_src - ctx->cost_a,
				ctx->len_tgt - ctx->cost_b);
	else if (ctx->meta_a->above_median && !ctx->meta_b->above_median)
		ctx->meta_a->push_cost = ctx->cost_a + (ctx->len_tgt - ctx->cost_b);
	else
		ctx->meta_a->push_cost = (ctx->len_src - ctx->cost_a) + ctx->cost_b;
}
