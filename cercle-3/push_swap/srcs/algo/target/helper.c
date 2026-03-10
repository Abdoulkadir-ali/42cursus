/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:01:43 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 01:15:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_target_ctx(t_target_ctx *ctx, t_nodes *stack_b)
{
	ctx->stack_b = stack_b;
	ctx->target = NULL;
	ctx->curr_b = stack_b;
	ctx->size = ft_size(stack_b);
	if (ASCENDING)
		ctx->best_match = INT_MIN;
	else
		ctx->best_match = INT_MAX;
}

void	search_best_target(t_target_ctx *ctx, t_nodes *node_a)
{
	while (ctx->size--)
	{
		if (!cmp(node_a->v, ctx->curr_b->v)
			&& cmp(ctx->best_match, ctx->curr_b->v))
		{
			ctx->best_match = ctx->curr_b->v;
			ctx->target = ctx->curr_b;
		}
		ctx->curr_b = ctx->curr_b->next;
	}
}

void	init_b_targets_ctx(t_set_b_targets_ctx *ctx, t_stacks *s)
{
	ctx->stack_a = s->a;
	ctx->stack_b = s->b;
	ctx->size_b = ft_size(ctx->stack_b);
	ctx->curr_b = ctx->stack_b;
}

void	find_target_for_b(t_set_b_targets_ctx *ctx)
{
	ctx->target = NULL;
	if (ASCENDING)
		ctx->best_match = INT_MAX;
	else
		ctx->best_match = INT_MIN;
	ctx->curr_a = ctx->stack_a;
	ctx->size_a = ft_size(ctx->stack_a);
	while (ctx->size_a--)
	{
		if (cmp(ctx->curr_b->v, ctx->curr_a->v) && cmp(ctx->curr_a->v,
				ctx->best_match))
		{
			ctx->best_match = ctx->curr_a->v;
			ctx->target = ctx->curr_a;
		}
		ctx->curr_a = ctx->curr_a->next;
	}
	if (!ctx->target)
		ctx->target = find_extreme(ctx->stack_a);
}
