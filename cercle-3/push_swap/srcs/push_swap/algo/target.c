/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:19:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_target(t_stacks *s, t_nodes *node_a)
{
	t_target_ctx	ctx;
	t_nodes			*max_node;

	ctx.stack_b = s->b;
	node_a->meta.target = NULL;
	if (!ctx.stack_b)
		return ;
	ctx.target = NULL;
	max_node = NULL;
	ctx.curr_b = ctx.stack_b;
	ctx.size = ft_size(ctx.stack_b);
	if (ASCENDING)
		ctx.best_match = INT_MIN;
	else
		ctx.best_match = INT_MAX;
	while (ctx.size--)
	{
		if (!cmp(node_a->v, ctx.curr_b->v) && cmp(ctx.best_match,
				ctx.curr_b->v))
		{
			ctx.best_match = ctx.curr_b->v;
			ctx.target = ctx.curr_b;
		}
		if (!max_node || ctx.curr_b->v > max_node->v)
			max_node = ctx.curr_b;
		ctx.curr_b = ctx.curr_b->next;
	}
	if (!ctx.target)
		ctx.target = max_node;
	node_a->meta.target = ctx.target;
}

void	set_target_nodes(t_stacks *s)
{
	t_nodes	*curr_a;
	int		size;
	t_nodes	*stack_a;

	stack_a = s->a;
	if (!stack_a)
		return ;
	curr_a = stack_a;
	size = ft_size(stack_a);
	while (size)
	{
		find_target(s, curr_a);
		curr_a = curr_a->next;
		size--;
	}
}

t_nodes	*find_extreme(t_nodes *stack)
{
	t_nodes	*extreme_node;
	int		extreme_val;
	int		size;

	if (!stack)
		return (NULL);
	if (ASCENDING)
		extreme_val = INT_MAX;
	else
		extreme_val = INT_MIN;
	extreme_node = stack;
	size = ft_size(stack);
	while (size--)
	{
		if (!cmp(extreme_val, stack->v))
		{
			extreme_val = stack->v;
			extreme_node = stack;
		}
		stack = stack->next;
	}
	return (extreme_node);
}

static void	find_target_for_b(t_set_b_targets_ctx *ctx)
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

void	set_b_targets(t_stacks *s)
{
	t_set_b_targets_ctx	ctx;

	ctx.stack_a = s->a;
	ctx.stack_b = s->b;
	ctx.size_b = ft_size(ctx.stack_b);
	ctx.curr_b = ctx.stack_b;
	while (ctx.size_b--)
	{
		find_target_for_b(&ctx);
		ctx.curr_b->meta.target = ctx.target;
		ctx.curr_b = ctx.curr_b->next;
	}
}
