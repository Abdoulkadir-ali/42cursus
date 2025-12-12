/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:51:13 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:27:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	cmp(int a, int b)
{
	if (ASCENDING)
		return (a <= b);
	else
		return (a >= b);
}

int	is_sorted(t_nodes *stack)
{
	t_nodes	*curr;
	int		prev_val;
	int		curr_val;
	int		size;

	if (!stack)
		return (1);
	size = ft_size(stack);
	if (size <= 1)
		return (1);
	prev_val = stack->v;
	curr = stack->next;
	while (size > 1)
	{
		curr_val = curr->v;
		if (!cmp(prev_val, curr_val))
			return (0);
		prev_val = curr_val;
		curr = curr->next;
		size--;
	}
	return (1);
}

void	sort_three(t_stacks *s)
{
	t_sort_three_ctx	ctx;

	ctx.v1 = s->a->v;
	ctx.v2 = s->a->next->v;
	ctx.v3 = s->a->next->next->v;
	if (ctx.v1 > ctx.v2 && ctx.v2 < ctx.v3 && ctx.v1 < ctx.v3)
		sa(s);
	else if (ctx.v1 > ctx.v2 && ctx.v2 > ctx.v3)
	{
		sa(s);
		rra(s);
	}
	else if (ctx.v1 > ctx.v2 && ctx.v2 < ctx.v3 && ctx.v1 > ctx.v3)
		ra(s);
	else if (ctx.v1 < ctx.v2 && ctx.v2 > ctx.v3 && ctx.v1 < ctx.v3)
	{
		sa(s);
		ra(s);
	}
	else if (ctx.v1 < ctx.v2 && ctx.v2 > ctx.v3 && ctx.v1 > ctx.v3)
		rra(s);
}

static void	move_a_to_b(t_stacks *s, t_nodes *cheap)
{
	if (!cheap || !cheap->meta.target)
		return ;
	if (cheap->meta.above_median && cheap->meta.target->meta.above_median)
	{
		while (s->a != cheap && s->b != cheap->meta.target)
			rr(s);
	}
	else if (!cheap->meta.above_median && !cheap->meta.target->meta.above_median)
	{
		while (s->a != cheap && s->b != cheap->meta.target)
			rrr(s);
	}
	while (s->a != cheap)
	{
		if (cheap->meta.above_median)
			ra(s);
		else
			rra(s);
	}
	while (s->b != cheap->meta.target)
	{
		if (cheap->meta.target->meta.above_median)
			rb(s);
		else
			rrb(s);
	}
	pb(s);
}

static void	process_a_to_b(t_stacks *s)
{
	t_nodes	*curr;
	t_nodes	*cheapest;
	long	min_cost;
	int		size;

	while (ft_size(s->a) > 3)
	{
		init_indices(s->a, ft_size(s->a));
		init_indices(s->b, ft_size(s->b));
		set_target_nodes(s);
		curr = s->a;
		size = ft_size(s->a);
		while (size--)
		{
			calculate_cost(s, &curr->meta, 1);
			curr = curr->next;
		}
		cheapest = NULL;
		min_cost = LONG_MAX;
		curr = s->a;
		size = ft_size(s->a);
		while (size--)
		{
			if (curr->meta.push_cost < min_cost)
			{
				min_cost = curr->meta.push_cost;
				cheapest = curr;
			}
			curr = curr->next;
		}
		if (cheapest)
			move_a_to_b(s, cheapest);
	}
}

void	turk_algorithm(t_stacks *s)
{
	int	size;

	size = ft_size(s->a);
	if (size <= 3)
		return ;
	if (size > 3)
		pb(s);
	if (size > 4)
	{
		pb(s);
		if (s->b->v < s->b->next->v)
			sb(s);
	}
	process_a_to_b(s);
	if (ft_size(s->a) == 3)
		sort_three(s);
	else if (ft_size(s->a) == 2 && s->a->v > s->a->next->v)
		sa(s);
}
