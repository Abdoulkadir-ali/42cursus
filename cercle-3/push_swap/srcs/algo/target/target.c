/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:33:54 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 01:15:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_nodes	*find_max_node(t_nodes *stack_b)
{
	t_nodes	*max_node;
	t_nodes	*curr;
	int		size;

	if (!stack_b)
		return (NULL);
	max_node = stack_b;
	curr = stack_b;
	size = ft_size(stack_b);
	while (size--)
	{
		if (curr->v > max_node->v)
			max_node = curr;
		curr = curr->next;
	}
	return (max_node);
}

void	find_target(t_stacks *s, t_nodes *node_a)
{
	t_target_ctx	ctx;

	node_a->meta.target = NULL;
	if (!s->b)
		return ;
	init_target_ctx(&ctx, s->b);
	search_best_target(&ctx, node_a);
	if (!ctx.target)
		ctx.target = find_max_node(s->b);
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

void	set_b_targets(t_stacks *s)
{
	t_set_b_targets_ctx	ctx;

	init_b_targets_ctx(&ctx, s);
	while (ctx.size_b--)
	{
		find_target_for_b(&ctx);
		ctx.curr_b->meta.target = ctx.target;
		ctx.curr_b = ctx.curr_b->next;
	}
}
