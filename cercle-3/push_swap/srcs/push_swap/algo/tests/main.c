/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:59:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_status(t_stacks *stacks, char *title)
{
	ft_putstr_fd(title, 1);
	print_stack(stacks->a, "Stack A");
	print_stack(stacks->b, "Stack B");
	ft_putstr_fd("Sorted: ", 1);
	if (is_sorted(stacks->a))
		ft_putstr_fd("YES\n", 1);
	else
		ft_putstr_fd("NO\n", 1);
}

static void	test_sorting(char **argv)
{
	t_stacks	stacks;

	stacks.a = NULL;
	stacks.b = NULL;
	stacks.verbose = 0;
	init_stacks(&stacks, argv);
	if (!stacks.a)
	{
		ft_putstr_fd("Error: Failed to parse input\n", 2);
		return ;
	}
	print_status(&stacks, "\n=== BEFORE SORTING ===\n");
	push_swap(&stacks);
	print_status(&stacks, "\n=== AFTER SORTING ===\n");
	free_stacks(stacks);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <numbers>\n", 2);
		ft_putstr_fd("Example: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" \"3 2 1 5 4\"\n", 2);
		return (1);
	}
	test_sorting(argv + 1);
	return (0);
}
