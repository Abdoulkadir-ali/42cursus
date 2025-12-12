/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   target.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 22:31:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_nodes	*get_node_by_index(t_nodes *stack, int index)
{
	t_nodes	*curr;
	int		i;

	if (!stack)
		return (NULL);
	curr = stack;
	i = 0;
	while (i < index)
	{
		curr = curr->next;
		i++;
		if (curr == stack)
			return (NULL);
	}
	return (curr);
}

static void	display_specific_target(t_stacks *stacks, int index)
{
	t_nodes	*node;

	node = get_node_by_index(stacks->a, index);
	if (!node)
	{
		ft_putstr_fd("Error: Index out of range\n", 2);
		return ;
	}
	ft_putstr_fd("\n=== TARGET INFO FOR INDEX ", 1);
	ft_putnbr_fd(index, 1);
	ft_putstr_fd(" ===\n", 1);
	ft_putstr_fd("Value: ", 1);
	ft_putnbr_fd(node->v, 1);
	ft_putstr_fd("\nTarget: ", 1);
	if (node->meta.target)
		ft_putnbr_fd(node->meta.target->v, 1);
	else
		ft_putstr_fd("none", 1);
	ft_putstr_fd("\n", 1);
}

static void	display_targets(t_stacks *stacks)
{
	t_nodes	*curr;
	t_nodes	*start;

	if (!stacks->a)
	{
		ft_putstr_fd("Stack A is empty\n", 1);
		return ;
	}
	ft_putstr_fd("\n=== TARGET MAPPING ===\n", 1);
	curr = stacks->a;
	start = stacks->a;
	while (1)
	{
		ft_putstr_fd("A[", 1);
		ft_putnbr_fd(curr->v, 1);
		ft_putstr_fd("] -> B[", 1);
		if (curr->meta.target)
			ft_putnbr_fd(curr->meta.target->v, 1);
		else
			ft_putstr_fd("none", 1);
		ft_putstr_fd("]\n", 1);
		curr = curr->next;
		if (curr == start)
			break ;
	}
}

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			index;
	int			error;
	char		*args[2];

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <numbers> [index]\n", 2);
		ft_putstr_fd("Example: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" \"5 2 8 1\" 1\n", 2);
		return (1);
	}
	stacks.a = NULL;
	stacks.b = NULL;
	stacks.verbose = 0;
	args[0] = argv[1];
	args[1] = NULL;
	init_stacks(&stacks, args);
	if (!stacks.a)
	{
		ft_putstr_fd("Error: Failed to parse input\n", 2);
		return (1);
	}
	pb(&stacks);
	pb(&stacks);
	ft_putstr_fd("\n=== INITIAL STATE ===\n", 1);
	print_stack(stacks.a, "Stack A");
	print_stack(stacks.b, "Stack B");
	set_target_nodes(&stacks);
	if (argc > 2)
	{
		index = (int)parse_int(argv[2], &error);
		if (error)
		{
			ft_putstr_fd("Error: Invalid index\n", 2);
			free_stacks(stacks);
			return (1);
		}
		display_specific_target(&stacks, index);
	}
	else
		display_targets(&stacks);
	free_stacks(stacks);
	return (0);
}
