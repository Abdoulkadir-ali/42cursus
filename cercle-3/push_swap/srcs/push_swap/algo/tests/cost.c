/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:24:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	display_costs(t_stacks *stacks)
{
	t_nodes	*curr;
	int		size;

	if (!stacks->b)
	{
		ft_putstr_fd("Stack B is empty\n", 1);
		return ;
	}
	ft_putstr_fd("\n=== COSTS FOR STACK B ===\n", 1);
	curr = stacks->b;
	size = ft_size(stacks->b);
	while (size)
	{
		ft_putnbr_fd(curr->v, 1);
		ft_putstr_fd(" [cost: ", 1);
		ft_putnbr_fd(curr->meta.push_cost, 1);
		ft_putstr_fd("]", 1);
		if (curr->meta.is_cheapest)
			ft_putstr_fd(" [CHEAPEST]", 1);
		ft_putstr_fd("\n", 1);
		curr = curr->next;
		size--;
	}
}

static void	prepare_stacks(t_stacks *stacks, char **argv)
{
	stacks->a = NULL;
	stacks->b = NULL;
	stacks->verbose = 0;
	init_stacks(stacks, argv + 1);
	while (ft_size(stacks->a) > 3)
		pb(stacks);
}

static void	calculate_all_costs(t_stacks *stacks, t_cost_test_ctx *ctx)
{
	ctx->len_a = ft_size(stacks->a);
	ctx->len_b = ft_size(stacks->b);
	init_indices(stacks->a, ctx->len_a);
	init_indices(stacks->b, ctx->len_b);
	set_b_targets(stacks);
	ctx->curr = stacks->b;
	ctx->i = 0;
	while (ctx->i < ctx->len_b)
	{
		calculate_cost(stacks, &ctx->curr->meta, 0);
		ctx->curr = ctx->curr->next;
		ctx->i++;
	}
	set_cheapest_node(stacks->b);
}

int	main(int argc, char **argv)
{
	t_stacks		stacks;
	t_cost_test_ctx	ctx;

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <numbers>\n", 2);
		return (1);
	}
	prepare_stacks(&stacks, argv);
	if (!stacks.a)
		return (ft_putstr_fd("Error: Failed to parse input\n", 2), 1);
	ft_putstr_fd("\n=== INITIAL STATE ===\n", 1);
	print_stack(stacks.a, "Stack A");
	print_stack(stacks.b, "Stack B");
	calculate_all_costs(&stacks, &ctx);
	display_costs(&stacks);
	free_stacks(stacks);
	return (0);
}
